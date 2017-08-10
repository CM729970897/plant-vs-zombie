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
			if ((bulletObj->getValid() == true) && (bulletObj->getBoundingBox().intersectsRect(getBoundingBox(zombieObj)))){//��ײ���
				zombieObj->setBlood(zombieObj->getBlood() - bulletObj->getPower());//��ʬѪ������
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
		if ((bulletObj->getValid() == true) && (bulletObj->getPosition().x >= Director::getInstance()->getVisibleSize().width)){//���ӵ��ɳ���Ļ��ʱ�������ӵ�
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
			if (getBoundingBox(plantObj).intersectsRect(getBoundingBox(walkZombieObj))){//��ʬ��ֲ�﷢����ײ
				walkZombieObj->setValid(GameEntityStatus::attack);//����ʬ�л����ڡ����ϵĹ���״̬��
				walkZombieObj->switchAction();//��ʬ�����л��ɹ�������
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
			if (getBoundingBox(plantObj).intersectsRect(getBoundingBox(attackZombieObj))){//��ʬ��ֲ�﷢����ײ
				plantObj->setBlood(plantObj->getBlood() - attackZombieObj->getAttack());//�޸�ֲ��Ѫ��
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
			//ȷ���Ѿ�������ֲ��
			continue;
		}
		//ӣ�ҡ��������ѹ���Щһ����ֲ��ȼ��ڡ���������ֲ�
		if (!((plantObj->getType() == GameEntityType::cherrybomb) || (plantObj->getType() == GameEntityType::jalapeno))){//���ֲ�ﲻ��һ���Ե�
			for (auto attackZombieObj : gameEntityManager->gameEntityArray){
				if (!((attackZombieObj->getType() > GameEntityType::begin_zombie) && (attackZombieObj->getType() < GameEntityType::end_zombie) && (attackZombieObj->getValid() == GameEntityStatus::attack))){
					//ȷ�����ڹ���״̬�Ľ�ʬ
					continue;
				}
				if (getBoundingBox(plantObj).intersectsRect(getBoundingBox(attackZombieObj))){//��ʬ��ֲ�﷢����ײ
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
		if (!((plantObj->getType() == GameEntityType::peashooter) || (plantObj->getType() == GameEntityType::sunflower) || (plantObj->getType() == GameEntityType::flashbamboo) && (plantObj->getValid() == GameEntityStatus::valid))){//��ǰʵ�岻���ڳ��ϵ�ֲ��
			continue;//ֱ��ȡ��һʵ��
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
		}//���տ��������ⲻ�ܽ�ʬ��Ӱ��
		else if ((plantObj->getType() == GameEntityType::peashooter) && (plantObj->getValid() == GameEntityStatus::valid)){
			for (auto zombieObj : gameEntityManager->gameEntityArray){
				if (!((zombieObj->getType() > GameEntityType::begin_zombie) && (zombieObj->getType() < GameEntityType::end_zombie) && (zombieObj->getValid() >= GameEntityStatus::valid) && (zombieObj->getValid() != GameEntityStatus::boom))){//��ǰʵ�岻Ϊ���Ͻ�ʬ
					continue;//ֱ��ȡ��һʵ��
				}
				if ((zombieObj->getPosition().x <= 750) && (plantObj->getPos().y == zombieObj->getPos().y) && (plantObj->getType() == GameEntityType::peashooter) && (plantObj->getValid() == GameEntityStatus::valid)){//����㶹�ͽ�ʬ��ͬһ��
					plantObj->setAttackExtra(plantObj->getAttackExtra() - 1);
					if (plantObj->getAttackExtra() == 0){
						if (plantObj->getBuffType() == BuffType::fire){
							auto bullet = derivedEntityManager->haveEntity(DerivedEntityType::fire_peabullet, plantObj, plantObj->getPos());
							plantObj->setBlood(plantObj->getBlood() - bullet->getPower() * 0.2);//�����ӵ�����������
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
		}//�㶹�����ӵ��������н�ʬ������²Żᷢ��
		else if ((plantObj->getType() == GameEntityType::flashbamboo) && (plantObj->getValid() == GameEntityStatus::valid)){
			plantObj->setAttackExtra(plantObj->getAttackExtra() - 1);
			if (plantObj->getAttackExtra() == 0){
				auto target = gameEntityManager->haveNearestZombie();//������ֻ����������ǰ��Ľ�ʬ
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



//�ռ�����
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
		return false;//ð��ģʽ�б��ؿ��½�ʬ�Ѿ�ȫ������
	}
	if ((mode == false) && (currentZombieInterval_const < 8)){//����ģʽ�µ���������ʬ������
		currentZombieInterval_const = 1;
		zombieNumConfig[currentZombieInterval_const] = INT32_MAX;
		currentZombieInterval_temp = currentZombieInterval_const;
	}
	currentZombieInterval_temp = currentZombieInterval_const;
	int prob = random() % 100;//ȷ��һ��0~99�������
	GameEntityType zombieType = GameEntityType::zombie;
	for (auto probItem : zombieAppearProb){
		int lower = probItem.first / 100;
		int upper = probItem.first % 100;
		if ((prob > lower) && (prob <= upper)){
			zombieType = (GameEntityType)probItem.second.asInt();
		}
	}//ѭ��ȷ��������ڸ����б��е���С�Ͻ磬���Ӧ������Ϊ�ض����ͽ�ʬ�����䣬����ȷ����ʬ���ֵ�����
	if ((currentZombieInterval_const == 10) && (zombieType == GameEntityType::buckethead_zombie)){
		zombieType = GameEntityType::conehead_zombie;//������Ϸ����п��ܳ��ֵĽ�Ϊ���ӵĽ�ʬ���м�
	}
	int row = random() % 5;//���ȷ����ʬ���ֵ��к�
	layer->addChild(gameEntityManager->haveEntity(zombieType,gridManager->getCoordPosition(row)));
	zombieNumConfig[currentZombieInterval_const] = zombieNumConfig[currentZombieInterval_const].asInt()-1;
	if (zombieNumConfig[currentZombieInterval_const].asInt() <= 0){
		currentZombieInterval_const--;
		currentZombieInterval_temp = currentZombieInterval_const;
		layer->addChild(gameEntityManager->haveEntity(GameEntityType::flag_zombie, gridManager->getCoordPosition(random() % 5)));
	}//���һ����ʬ������������ı�ʱ������������һ������
	return true;
}

bool EntityInteractManager::judgeZombieCrossLine(){
	for (auto zombieObj : gameEntityManager->gameEntityArray){
		if (!((zombieObj->getType() > GameEntityType::begin_zombie) && (zombieObj->getType() < GameEntityType::end_zombie) && (zombieObj->getValid() > 0))){
			continue;//����Ϊһ����Ч��ʬ����ֱ��ȡ��һʵ��
		}
		if (getBoundingBox(zombieObj).getMinX() <= 0){//�����һ����ʬ�����������Ϊ0������ζ�Ž�ʬԽ�磬������Ϸ����
			return true;
		}
	}
	return false;
}

bool EntityInteractManager::judgeZombieValidation(){
	for (auto zombieObj : gameEntityManager->gameEntityArray){
		if ((zombieObj->getType() > GameEntityType::begin_zombie) && (zombieObj->getType() < GameEntityType::end_zombie) && (zombieObj->getValid() >= GameEntityStatus::valid) && (zombieObj->getValid() != GameEntityStatus::boom)){
			return true;//������Ч��ʬ
		}
	}
	return false;
}


GameStatus EntityInteractManager::judgeGameStatus(Layer* layer, bool mode){
	if (gameEntityManager->gameEntityArray.empty()){
		zombieAppear(layer, mode);
		return GameStatus::on;
	}
	if (mode){//��ǰΪð��ģʽ
		if (judgeZombieCrossLine()){//�����ʬԽ��
			gameEntityManager->gameEntityArray.clear();
			return GameStatus::failure;//������Ϸ����,ʧ��
		}
		else if ((!zombieAppear(layer, mode)) && (!judgeZombieValidation())){//�����ʬ���ܳ���,�ҳ�����û����Ч��ʬ
			gameEntityManager->gameEntityArray.clear();
			return GameStatus::success;//������Ϸ����,�ɹ�
		}
		else{
			zombieAppear(layer, mode);
			return GameStatus::on;//������Ϸ����
		}
	}
	else{//��ǰΪ����ģʽ
		if (judgeZombieCrossLine()){//�����ʬԽ��
			gameEntityManager->gameEntityArray.clear();
			return GameStatus::failure;//������Ϸ����
		}
		zombieAppear(layer, mode);
		return GameStatus::on;//����ģʽ��ʬ��û���������޵ģ�����ж�����ֻ��һ��
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
			//ȷ����Ч�Ľ�ʬ
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
			//ȷ����Ч�Ľ�ʬ
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
		return;//�û����߲���
	}
	int count = gameEntityManager->countValidNobuffPeashooter();//��ȡ��ǰ���ϵ�������Ч���㶹��������
	if (count < 3){//��ǰ����û���������ϵ���buff��Ч�㶹�������ͷ�buff
		return;
	}
	ValueVector randomResult;
	while (true){
		int num = (random() % count) + 1;//��ȡһ��1~count�������
		bool flag = false;
		for (auto obj : randomResult){
			if (obj.asInt() == num){
				flag = true;//������ͬ������
			}
		}
		if (flag == false){
			randomResult.push_back(Value(num));//����������ͬ������ʱ���������ּ�������
		}
		if (randomResult.size() == 3){
			break;//�����鳤��Ϊ3ʱ���˳�ѭ���������������
		}
	}
	gameEntityManager->applyFireBuffToPeashooter(layer, randomResult, BuffType::fire);//��Ӧ���㶹����ʩ��buff
	UserManager::getInstance()->updateUserProperty(GameEntityType::torchwood, -1);
}

void EntityInteractManager::randomDropGold(Layer* layer, GameEntity* zombie){
	while (true){//����һ���ĸ��ʿ�������������
		auto prob = random() % 100;//��һ��0~99�������
		if (prob <= zombie->getCost()){//������ڸ���������
			auto gold = derivedEntityManager->haveGold(zombie->getPosition());
			layer->addChild(gold);
		}
		else{
			break;//�����������ڣ���ֱ���˳�
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
		return;//�û����߲���
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
			//ȷ�����ڹ���״̬�Ľ�ʬ
			continue;
		}
		if (getBoundingBox(plant).intersectsRect(getBoundingBox(attackZombieObj))){//��ʬ��ֲ�﷢����ײ
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