#include "cocos2d.h"
#include "Sunshine.h"
#include "EntityInteractManager.h"
#include "SpecialEffect.h"
#include "FlowWord.h"
#include "UserManager.h"
#include "AudioEngine.h"
#include "Volum.h"
#include "BambooShoot.h"

USING_NS_CC;
using namespace experimental;

EntityInteractManager* EntityInteractManager::instance = NULL;

EntityInteractManager* EntityInteractManager::getInstance(){
	if (instance == NULL){
		instance = new EntityInteractManager();
	}
	return instance;
}

void EntityInteractManager::init(){
	gameEntityManager = GameEntityManager::getInstance();
	derivedEntityManager = DerivedEntityManager::getInstance();
	gridManager = GridManager::getInstance();
	pMap = DataConfig::getInstance()->getZombiePoint();
}

Rect EntityInteractManager::getBoundingBox(Sprite* entity){
if (entity == NULL){
	return Rect(0, 0, 0, 0);
}
auto entitySize = entity->getContentSize();
auto entityPoint = entity->getPosition();

return Rect(entityPoint.x - entitySize.width / 7,
	entityPoint.y - entitySize.height / 7,
	(entitySize.width * 3 / 7), (entitySize.height * 5 / 7));
}

Rect EntityInteractManager::getCherryBombArea(Sprite* entity){
	if (entity == NULL){
		return Rect(0, 0, 0, 0);
	}
	auto entityPoint = entity->getPosition();
	return Rect(entityPoint.x - 60,
		entityPoint.y - 60,
		140, 140);
}


void EntityInteractManager::checkHitZombiesAndBullets(Layer* layer){
	for (auto bulletObj : derivedEntityManager->derivedEntityArray){
		if (!((bulletObj->getType() == DerivedEntityType::peabullet) || (bulletObj->getType() == DerivedEntityType::fire_peabullet) || (bulletObj->getType() == DerivedEntityType::bambooshoot) && (bulletObj->getValid() == true))){
			continue;
		}
		for (auto zombieObj : gameEntityManager->gameEntityArray){
			if (!((zombieObj->getType() > GameEntityType::begin_zombie) && (zombieObj->getType() < GameEntityType::end_zombie) && (zombieObj->getValid() >= GameEntityStatus::valid) && (zombieObj->getValid() != GameEntityStatus::boom))){
				continue;
			}
			if (zombieObj->getBlood() <= 0){

				point += pMap[zombieObj->getType()];   //2.26
				randomDropGold(layer, zombieObj);
				zombieObj->resetEntity();
			}
			if ((bulletObj->getValid() == true) && (bulletObj->getBoundingBox().intersectsRect(getBoundingBox(zombieObj)))){//碰撞检测
				zombieObj->setBlood(zombieObj->getBlood() - bulletObj->getPower());//僵尸血量减低
				if (zombieObj->getBlood() > 0)
				{
					FlowWord* word = FlowWord::create();
					word->showWordint(zombieObj->getBlood(), bulletObj->getPosition());
					layer->addChild(word);
					word->runAction(Sequence::create(DelayTime::create(1.0f), CallFunc::create(word, callfunc_selector(FlowWord::flowEnd)), NULL));
				}
				bulletObj->resetEntity();
				break;
			}
			else
				continue;
		}
		if ((bulletObj->getValid() == true) && (bulletObj->getPosition().x >= Director::getInstance()->getVisibleSize().width)){//若子弹飞出屏幕外时，重置子弹
			bulletObj->resetEntity();
		}
		if ((((BambooShoot*)bulletObj)->getTarget() != NULL) && (bulletObj->getValid() == true) && (bulletObj->getType() == DerivedEntityType::bambooshoot)){
			if (((BambooShoot*)bulletObj)->getTarget()->getValid() == GameEntityStatus::invalid){
				bulletObj->resetEntity();
			}
		}
	}
}

void EntityInteractManager::checkHitWalkZombiesAndLivePlants(){
	for (auto plantObj : gameEntityManager->gameEntityArray){
		if (!((plantObj->getType() > GameEntityType::begin_plant) && (plantObj->getType() < GameEntityType::end_plant) && (plantObj->getValid() == GameEntityStatus::valid))){
			continue;
		}
		for (auto walkZombieObj : gameEntityManager->gameEntityArray){
			if (!((walkZombieObj->getType() > GameEntityType::begin_zombie) && (walkZombieObj->getType() < GameEntityType::end_zombie) && (walkZombieObj->getValid() == GameEntityStatus::valid))){
				continue;
			}
			if (getBoundingBox(plantObj).intersectsRect(getBoundingBox(walkZombieObj))){//僵尸与植物发生碰撞
				walkZombieObj->setValid(GameEntityStatus::attack);//将僵尸切换成在“场上的攻击状态”
				walkZombieObj->switchAction();//僵尸动作切换成攻击动作
			}
		}
	}
}

void EntityInteractManager::zombiesAttackPlants(Layer* layer){
	for (auto plantObj : gameEntityManager->gameEntityArray){
		if (!((plantObj->getType() > GameEntityType::begin_plant) && (plantObj->getType() < GameEntityType::end_plant) && (plantObj->getValid() == GameEntityStatus::valid) && (plantObj->getBlood() > 0))){
			continue;
		}
		for (auto attackZombieObj : gameEntityManager->gameEntityArray){
			if (!((attackZombieObj->getType() > GameEntityType::begin_zombie) && (attackZombieObj->getType() < GameEntityType::end_zombie) && (attackZombieObj->getValid() == GameEntityStatus::attack))){
				continue;
			}
			if (getBoundingBox(plantObj).intersectsRect(getBoundingBox(attackZombieObj))){//僵尸与植物发生碰撞
				plantObj->setBlood(plantObj->getBlood() - attackZombieObj->getAttack());//修改植物血量
				FlowWord* word = FlowWord::create();
				word->getLableTTF()->setColor(Color3B(0, 255, 0));
				word->showWordint(plantObj->getBlood(), plantObj->getPosition());
				layer->addChild(word);
				word->runAction(Sequence::create(DelayTime::create(1.0f), CallFunc::create(word, callfunc_selector(FlowWord::flowEnd)), NULL));
			}
		}
	}
}

void EntityInteractManager::checkHitAttackZombiesAndDeadPlants(){
	for (auto plantObj : gameEntityManager->gameEntityArray){
		if (!((plantObj->getType() > GameEntityType::begin_plant) && (plantObj->getType() < GameEntityType::end_plant) && (plantObj->getValid() == GameEntityStatus::valid) && (plantObj->getBlood() <= 0))){
			//确定已经死亡的植物
			continue;
		}
		//樱桃、辣椒和窝瓜这些一次性植物等价于“已死亡的植物”
		if (!((plantObj->getType() == GameEntityType::cherrybomb) || (plantObj->getType() == GameEntityType::jalapeno))){//如果植物不是一次性的
			for (auto attackZombieObj : gameEntityManager->gameEntityArray){
				if (!((attackZombieObj->getType() > GameEntityType::begin_zombie) && (attackZombieObj->getType() < GameEntityType::end_zombie) && (attackZombieObj->getValid() == GameEntityStatus::attack))){
					//确定处于攻击状态的僵尸
					continue;
				}
				if (getBoundingBox(plantObj).intersectsRect(getBoundingBox(attackZombieObj))){//僵尸与植物发生碰撞
					attackZombieObj->setValid(GameEntityStatus::valid);
					attackZombieObj->switchAction();
				}
			}
			plantObj->resetEntity();
			gridManager->clearPosStatus(plantObj->getPosition());
		}
	}
}


void EntityInteractManager::plantsAttackZombies(Layer* layer){
	for (auto plantObj : gameEntityManager->gameEntityArray){
		if (!((plantObj->getType() == GameEntityType::peashooter) || (plantObj->getType() == GameEntityType::sunflower) || (plantObj->getType() == GameEntityType::flashbamboo) && (plantObj->getValid() == GameEntityStatus::valid))){//当前实体不是在场上的植物
			continue;//直接取下一实体
		}
		if (plantObj->getBlood() < 0){
			gridManager->clearPosStatus(plantObj->getPosition());
			plantObj->resetEntity();
		}
		if ((plantObj->getType() == GameEntityType::sunflower) && (plantObj->getValid() == GameEntityStatus::valid)){
			plantObj->setAttackExtra(plantObj->getAttackExtra() - 1);
			if (plantObj->getAttackExtra() == 0){
				auto sunshine = derivedEntityManager->haveEntity(DerivedEntityType::sunshine, plantObj, plantObj->getPos());
				layer->addChild(sunshine, 8);
				plantObj->setAttackExtra(plantObj->getAttack());
			}
		}//向日葵产生阳光不受僵尸的影响
		else if ((plantObj->getType() == GameEntityType::peashooter) && (plantObj->getValid() == GameEntityStatus::valid)){
			for (auto zombieObj : gameEntityManager->gameEntityArray){
				if (!((zombieObj->getType() > GameEntityType::begin_zombie) && (zombieObj->getType() < GameEntityType::end_zombie) && (zombieObj->getValid() >= GameEntityStatus::valid) && (zombieObj->getValid() != GameEntityStatus::boom))){//当前实体不为场上僵尸
					continue;//直接取下一实体
				}
				if ((zombieObj->getPosition().x <= 750) && (plantObj->getPos().y == zombieObj->getPos().y) && (plantObj->getType() == GameEntityType::peashooter) && (plantObj->getValid() == GameEntityStatus::valid)){//如果豌豆和僵尸在同一行
					plantObj->setAttackExtra(plantObj->getAttackExtra() - 1);
					if (plantObj->getAttackExtra() == 0){
						if (plantObj->getBuffType() == BuffType::fire){
							auto bullet = derivedEntityManager->haveEntity(DerivedEntityType::fire_peabullet, plantObj, plantObj->getPos());
							plantObj->setBlood(plantObj->getBlood() - bullet->getPower() * 0.2);//火焰子弹的自伤作用
							FlowWord* word = FlowWord::create();
							word->getLableTTF()->setColor(Color3B(0, 255, 0));
							word->showWordint(plantObj->getBlood(), plantObj->getPosition());
							layer->addChild(word);
							word->runAction(Sequence::create(DelayTime::create(1.0f), CallFunc::create(word, callfunc_selector(FlowWord::flowEnd)), NULL));
							layer->addChild(bullet);
						}
						else{
							auto bullet = derivedEntityManager->haveEntity(DerivedEntityType::peabullet, plantObj, plantObj->getPos());
							layer->addChild(bullet);
						}
						plantObj->setAttackExtra(plantObj->getAttack());
					}
				}
			}
		}//豌豆产生子弹则是在有僵尸的情况下才会发生
		else if ((plantObj->getType() == GameEntityType::flashbamboo) && (plantObj->getValid() == GameEntityStatus::valid)){
			plantObj->setAttackExtra(plantObj->getAttackExtra() - 1);
			if (plantObj->getAttackExtra() == 0){
				auto target = gameEntityManager->haveNearestZombie();//闪电竹只攻击走在最前面的僵尸
				if (target != NULL){
					auto shoot = derivedEntityManager->haveEntity(DerivedEntityType::bambooshoot, plantObj, plantObj->getPosition());
					((BambooShoot*)shoot)->setTarget(target);
					shoot->switchAction();
					layer->addChild(shoot);
				}
				plantObj->setAttackExtra(plantObj->getAttack());
			}
		}
	}
}



//收集阳光
void EntityInteractManager::collectSunshine(Vec2 pos){
	for (auto sunshineObj : derivedEntityManager->derivedEntityArray){
		if (!((sunshineObj->getType() == DerivedEntityType::sunshine) && (sunshineObj->getValid() == true))){
			continue;
		}
		if (sunshineObj->getBoundingBox().containsPoint(pos)){
			sunshineObj->runAction(Sequence::create(MoveTo::create(2.0f, Vec2(45, 565)), CallFunc::create(sunshineObj, callfunc_selector(Sunshine::resetEntity)), NULL));
			sunshineObj->runAction(ScaleTo::create(2.0f, 0.2f));
			currentScore += 50;
			return;
		}
	}
}

void EntityInteractManager::produceRandomSunshine(Layer* layer){
	auto visibleSize = Director::getInstance()->getVisibleSize();
	int rand_x = random() % (int)(visibleSize.width - 70) + 35;
	int rand_y = visibleSize.height + 20;
	randomSunshineInterval_temp--;
	if (randomSunshineInterval_temp <= 0){
		auto sunshine = derivedEntityManager->haveEntity(DerivedEntityType::sunshine, NULL, Vec2(rand_x, rand_y));
		layer->addChild(sunshine,8);
		randomSunshineInterval_temp = randomSunshineInterval_const;
	}
	return;
}

bool EntityInteractManager::loadZombieConfig(ValueMapIntKey numList,ValueMapIntKey probList){
	if ((numList.size() < 0) || (probList.size() < 0))return false;
	zombieNumConfig = numList;
	zombieAppearProb = probList;
	currentZombieInterval_const = 10;
	currentZombieInterval_temp = currentZombieInterval_const;
	return true;
}

bool EntityInteractManager::zombieAppear(Layer* layer,bool mode){
	if (currentZombieInterval_temp > 0){
		currentZombieInterval_temp--;
		return true;
	}
	if ((currentZombieInterval_const < 8) && (mode == true)){
		return false;//冒险模式中本关卡下僵尸已经全部打完
	}
	if ((mode == false) && (currentZombieInterval_const < 8)){//生存模式下当第三波僵尸被打完
		currentZombieInterval_const = 1;
		zombieNumConfig[currentZombieInterval_const] = INT32_MAX;
		currentZombieInterval_temp = currentZombieInterval_const;
	}
	currentZombieInterval_temp = currentZombieInterval_const;
	int prob = random() % 100;//确定一个0~99的随机数
	GameEntityType zombieType = GameEntityType::zombie;
	for (auto probItem : zombieAppearProb){
		int lower = probItem.first / 100;
		int upper = probItem.first % 100;
		if ((prob > lower) && (prob <= upper)){
			zombieType = (GameEntityType)probItem.second.asInt();
		}
	}//循环确定随机数在概率列表中的最小上界，其对应的区间为特定类型僵尸的区间，即可确定僵尸出现的类型
	if ((currentZombieInterval_const == 10) && (zombieType == GameEntityType::buckethead_zombie)){
		zombieType = GameEntityType::conehead_zombie;//对于游戏最初有可能出现的较为复杂的僵尸进行简化
	}
	int row = random() % 5;//随机确定僵尸出现的行号
	layer->addChild(gameEntityManager->haveEntity(zombieType,gridManager->getCoordPosition(row)));
	zombieNumConfig[currentZombieInterval_const] = zombieNumConfig[currentZombieInterval_const].asInt()-1;
	if (zombieNumConfig[currentZombieInterval_const].asInt() <= 0){
		currentZombieInterval_const--;
		currentZombieInterval_temp = currentZombieInterval_const;
		layer->addChild(gameEntityManager->haveEntity(GameEntityType::flag_zombie, gridManager->getCoordPosition(random() % 5)));
	}//如果一波僵尸进攻结束，则改变时间间隔，进行下一波进攻
	return true;
}

bool EntityInteractManager::judgeZombieCrossLine(){
	for (auto zombieObj : gameEntityManager->gameEntityArray){
		if (!((zombieObj->getType() > GameEntityType::begin_zombie) && (zombieObj->getType() < GameEntityType::end_zombie) && (zombieObj->getValid() > 0))){
			continue;//若不为一个有效僵尸，则直接取下一实体
		}
		if (getBoundingBox(zombieObj).getMinX() <= 0){//如果有一个僵尸的最左边坐标为0，则意味着僵尸越界，本关游戏结束
			return true;
		}
	}
	return false;
}

bool EntityInteractManager::judgeZombieValidation(){
	for (auto zombieObj : gameEntityManager->gameEntityArray){
		if ((zombieObj->getType() > GameEntityType::begin_zombie) && (zombieObj->getType() < GameEntityType::end_zombie) && (zombieObj->getValid() >= GameEntityStatus::valid) && (zombieObj->getValid() != GameEntityStatus::boom)){
			return true;//存在有效僵尸
		}
	}
	return false;
}


GameStatus EntityInteractManager::judgeGameStatus(Layer* layer, bool mode){
	if (gameEntityManager->gameEntityArray.empty()){
		zombieAppear(layer, mode);
		return GameStatus::on;
	}
	if (mode){//当前为冒险模式
		if (judgeZombieCrossLine()){//如果僵尸越线
			gameEntityManager->gameEntityArray.clear();
			return GameStatus::failure;//本局游戏结束,失败
		}
		else if ((!zombieAppear(layer, mode)) && (!judgeZombieValidation())){//如果僵尸不能出现,且场面上没有有效僵尸
			gameEntityManager->gameEntityArray.clear();
			return GameStatus::success;//本局游戏结束,成功
		}
		else{
			zombieAppear(layer, mode);
			return GameStatus::on;//本局游戏继续
		}
	}
	else{//当前为生存模式
		if (judgeZombieCrossLine()){//如果僵尸越线
			gameEntityManager->gameEntityArray.clear();
			return GameStatus::failure;//本局游戏结束
		}
		zombieAppear(layer, mode);
		return GameStatus::on;//生存模式僵尸是没有设置上限的，因此判断条件只有一个
	}
}

void EntityInteractManager::plantCherryBomb(Layer* layer, GameEntity* plantObj){
	SpecialEffect* effect = new SpecialEffect();
	effect->cherryBombAttack();
	effect->setPosition(Vec2(plantObj->getPosition().x, plantObj->getPosition().y - 30));
	layer->addChild(effect);
	gridManager->clearPosStatus(plantObj->getPosition());
	plantObj->resetEntity();
	for (auto zombieObj : gameEntityManager->gameEntityArray){
		if (!((zombieObj->getType() > GameEntityType::begin_zombie) && (zombieObj->getType() < GameEntityType::end_zombie) && (zombieObj->getValid() >= GameEntityStatus::valid) && (zombieObj->getValid() != GameEntityStatus::boom))){
			//确定有效的僵尸
			continue;
		}
		if (getCherryBombArea(plantObj).intersectsRect(getBoundingBox(zombieObj))){
			zombieObj->setValid(GameEntityStatus::boom);
			zombieObj->switchAction();
			randomDropGold(layer, zombieObj);
			point += pMap[zombieObj->getType()];  // 2.26  
			zombieObj->runAction(Sequence::create(DelayTime::create(2.7f), CallFunc::create(zombieObj, callfunc_selector(GameEntity::resetEntity)), NULL));
		}
	}
	AudioEngine::play2d("game/sound/CherryBomb.mp3", false, VolumSet::getInstance()->getTVolum());

	effect->runAction(Sequence::create(DelayTime::create(2.7f), CallFunc::create(effect, callfunc_selector(SpecialEffect::remove)), NULL));

}

void EntityInteractManager::plantJalapeno(Layer* layer, GameEntity* plantObj){
	SpecialEffect* effect = new SpecialEffect();
	effect->jalapenoAttack();
	effect->setPosition(Vec2(plantObj->getPosition().x, plantObj->getPosition().y - 30));
	layer->addChild(effect);
	gridManager->clearPosStatus(plantObj->getPosition());
	plantObj->resetEntity();
	for (auto zombieObj : gameEntityManager->gameEntityArray){
		if (!((zombieObj->getType() > GameEntityType::begin_zombie) && (zombieObj->getType() < GameEntityType::end_zombie) && (zombieObj->getValid() >= GameEntityStatus::valid) && (zombieObj->getValid() != GameEntityStatus::boom))){
			//确定有效的僵尸
			continue;
		}
		if ((zombieObj->getPosition().y == plantObj->getPosition().y) && (zombieObj->getPosition().x < Director::getInstance()->getVisibleSize().width)){
			zombieObj->setValid(GameEntityStatus::boom);
			zombieObj->switchAction();
			randomDropGold(layer, zombieObj);
			point += pMap[zombieObj->getType()];
			zombieObj->runAction(Sequence::create(DelayTime::create(2.7f), CallFunc::create(zombieObj, callfunc_selector(GameEntity::resetEntity)), NULL));
		}
	}

	AudioEngine::play2d("game/sound/CherryBomb.mp3", false, VolumSet::getInstance()->getTVolum());
	effect->runAction(Sequence::create(DelayTime::create(2.7f), CallFunc::create(effect, callfunc_selector(SpecialEffect::remove)), NULL));
}

void EntityInteractManager::UnleashFireBuff(Layer* layer){
	if (UserManager::getInstance()->getUserPropertyByID(GameEntityType::torchwood) < 1){
		return;//用户道具不足
	}
	int count = gameEntityManager->countValidNobuffPeashooter();//获取当前场上的所有有效的豌豆射手数量
	if (count < 3){//当前场上没有两个以上的无buff有效豌豆，则不能释放buff
		return;
	}
	ValueVector randomResult;
	while (true){
		int num = (random() % count) + 1;//获取一个1~count的随机数
		bool flag = false;
		for (auto obj : randomResult){
			if (obj.asInt() == num){
				flag = true;//已有相同的数字
			}
		}
		if (flag == false){
			randomResult.push_back(Value(num));//当不存在相同的数字时，将该数字加入其中
		}
		if (randomResult.size() == 3){
			break;//当数组长度为3时，退出循环，不再求随机数
		}
	}
	gameEntityManager->applyFireBuffToPeashooter(layer, randomResult, BuffType::fire);//对应的豌豆射手施加buff
	UserManager::getInstance()->updateUserProperty(GameEntityType::torchwood, -1);
}

void EntityInteractManager::randomDropGold(Layer* layer, GameEntity* zombie){
	while (true){//按照一定的概率可以连续掉落金币
		auto prob = random() % 100;//求一个0~99的随机数
		if (prob <= zombie->getCost()){//随机数在概率区间内
			auto gold = derivedEntityManager->haveGold(zombie->getPosition());
			layer->addChild(gold);
		}
		else{
			break;//若不在区间内，则直接退出
		}
	}
}

void EntityInteractManager::collectGold(Vec2 pos){
	for (auto goldObj : derivedEntityManager->goldArray){
		if (!(goldObj->getValid() == true)){
			continue;
		}
		if (goldObj->getBoundingBox().containsPoint(pos)){
			goldObj->runAction(Sequence::create(MoveTo::create(2.0f, Vec2(0, 0)), CallFunc::create(goldObj, callfunc_selector(Sunshine::resetEntity)), NULL));
			goldObj->runAction(ScaleTo::create(2.0f, 0.2f));
			UserManager::getInstance()->updateUserGold(10);
			return;
		}
	}
}

void EntityInteractManager::collectAllGolds(){
	for (auto goldObj : derivedEntityManager->goldArray){
		if (!(goldObj->getValid() == true)){
			continue;
		}
		goldObj->runAction(Sequence::create(MoveTo::create(2.0f, Vec2(0, 0)), CallFunc::create(goldObj, callfunc_selector(Sunshine::resetEntity)), NULL));
		goldObj->runAction(ScaleTo::create(2.0f, 0.2f));
		UserManager::getInstance()->updateUserGold(10);
	}
}

void EntityInteractManager::UnleashIceBuff(Layer* layer){

	if (UserManager::getInstance()->getUserPropertyByID(GameEntityType::iceshroom) < 1){
		return;//用户道具不足
	}
	gameEntityManager->applyIceBuffToZombie(layer);
	UserManager::getInstance()->updateUserProperty(GameEntityType::iceshroom, -1);
}

EntityInteractManager::~EntityInteractManager()
{
	AudioEngine::uncache("game/sound/CherryBomb.mp3");
}

void EntityInteractManager::ShovelPlant(Vec2 pos)
{
	GameEntity* plant = NULL;
	for (auto plantObj : gameEntityManager->gameEntityArray)
	{
		if (!((plantObj->getType() > GameEntityType::begin_plant) && (plantObj->getType() < GameEntityType::end_plant) && (plantObj->getValid() == GameEntityStatus::valid) && (plantObj->getPosition() == pos)))
		{
			continue;
		}
		plant = plantObj;
		plantObj->resetEntity();
		gridManager->clearPosStatus(plant->getPosition());
		break;
	}
	if (plant == NULL)return;
	for (auto attackZombieObj : gameEntityManager->gameEntityArray){
		if (!((attackZombieObj->getType() > GameEntityType::begin_zombie) && (attackZombieObj->getType() < GameEntityType::end_zombie) && (attackZombieObj->getValid() == GameEntityStatus::attack))){
			//确定处于攻击状态的僵尸
			continue;
		}
		if (getBoundingBox(plant).intersectsRect(getBoundingBox(attackZombieObj))){//僵尸与植物发生碰撞
			attackZombieObj->setValid(GameEntityStatus::valid);
			attackZombieObj->switchAction();
		}
	}
	for (auto bullet : derivedEntityManager->derivedEntityArray)
	{
		if (!((bullet->getType() > DerivedEntityType::begin_derived_entity_type) && (bullet->getType() < DerivedEntityType::end_derived_entity_type) && (bullet->getPlant() == plant))){
			bullet->resetEntity();
		}

	}
	
}