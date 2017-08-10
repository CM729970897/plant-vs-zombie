#include "SurvivalScene.h"
#include "SimpleAudioEngine.h"
#include "GridManager.h"
#include "OptPropUI.h"
#include "EntityConst.h"
#include "LevelPassScene.h"
#include "LevelFailureScene.h"
#include "EntityInteractManager.h"
#include "AudioEngine.h"
#include "Volum.h"
#include "GameMenuUI.h"
#include "DataConfig.h"
#include "UserManager.h"
#include "GameEntity.h"

USING_NS_CC;
using namespace experimental;


Scene* SurvivalMode::createScene()
{
	auto scene = Scene::create();
	auto layer = SurvivalMode::create();
	scene->addChild(layer, 0, 900);
	return scene;
}

bool SurvivalMode::init()
{
	if (!Layer::init())
	{
		return false;
	}
	VolumSet::getInstance()->setMode(GameScene::survival_mode);

	auto optPropUI = OptPropUI::create();
	optPropUI->setPosition(Vec2(0, -600));
	optPropUI->runAction(MoveTo::create(1.5f, Vec2::ZERO));
	this->addChild(optPropUI, 1, 900);  //选择植物场景  设置tag为900

	//数据成员初始化
	gameEntityManager = GameEntityManager::getInstance();
	derivedEntityManager = DerivedEntityManager::getInstance();
	gridManager = GridManager::getInstance();
	entityInteractManager = EntityInteractManager::getInstance();
	
	sun = FlowWord::create();
	this->addChild(sun, 4);
	gold = FlowWord::create();
	this->addChild(gold, 4);
	torchwoodNum = FlowWord::create();
	this->addChild(torchwoodNum, 4);
	iceshroomNum = FlowWord::create();
	this->addChild(iceshroomNum, 4);


	// 2.26
	pword = FlowWord::create();
	pword->getLableTTF()->setColor(Color3B(0,0,0));
	pword->getLableTTF()->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
	this->addChild(pword, 4);


	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();


	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(SurvivalMode::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(SurvivalMode::onTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(SurvivalMode::onTouchEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	/*无尽模式背景*/
	auto sprite = Sprite::create("game/Gamelayer/MainBattleField.jpg");
	sprite->setPosition(Vec2(visibleSize.width / 2 + origin.x + 100, visibleSize.height / 2 + origin.y));
	this->addChild(sprite, 0);

	auto gold_collector = Sprite::create("game/GameLayer/gold_collector.png");
	gold_collector->setPosition(Vec2(120, 25));
	this->addChild(gold_collector);

	/*菜单*/
	auto choiceItem = MenuItemImage::create(
		"game/interface/menu.jpg",
		"game/interface/menuselected.jpg",
		CC_CALLBACK_1(SurvivalMode::menuCloseCallback, this));
	choiceItem->setPosition(Vec2(origin.x + visibleSize.width - choiceItem->getContentSize().width / 2, origin.y + visibleSize.height - choiceItem->getContentSize().height / 2));
	menu = Menu::create(choiceItem, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 2);
	menu->setVisible(false);

	gameEntityManager->haveEntityForItem(this, GameEntityType::torchwood, Vec2(651, 560));
	gameEntityManager->haveEntityForItem(this, GameEntityType::iceshroom, Vec2(550, 560));

	for (int i = 0; i < 7; i++)
	{
		prop[i].value = 0;
		prop[i].score = 99999;
		prop[i].on = false;
		prop[i].on2 = true;     
	}
	spriteOne = NULL;
	propStart = false;
	scheduleUpdate();

	ValueMapIntKey probList;
	ValueMapIntKey configList;

	DataConfig::getInstance()->setSurvivalModeData(&configList,&probList);

	entityInteractManager->loadZombieConfig(configList, probList);

	this->schedule(schedule_selector(SurvivalMode::constEntitiesInteract), 1.0f);

	this->schedule(schedule_selector(SurvivalMode::collideDetect), 0.1f);

	entityInteractManager->setPoint(0);

	entityInteractManager->setSunScore(200);

	return true;
}

void SurvivalMode::constEntitiesInteract(float dt){
	if (propStart){
		entityInteractManager->plantsAttackZombies(this);
		entityInteractManager->zombiesAttackPlants(this);
		entityInteractManager->produceRandomSunshine(this);
		GameStatus status = entityInteractManager->judgeGameStatus(this, false);
		switch (status){
		case GameStatus::failure:
			gameFailure();
			gridManager->resetStatus();
			propStart = false;
			break;
		default:
			break;
		}
	}
}

void SurvivalMode::collideDetect(float dt){
	if (propStart){
		entityInteractManager->checkHitZombiesAndBullets(this);
		entityInteractManager->checkHitWalkZombiesAndLivePlants();
		entityInteractManager->checkHitAttackZombiesAndDeadPlants();
	}
}


void SurvivalMode::creatProp(int a[], int count)
{
	/*道具栏*/
	auto barSprite = Sprite::create("game/gamelayer/ChosenBar.png");
	barSprite->setAnchorPoint(Vec2::ZERO);
	barSprite->setPosition(Vec2(0, 515));
	this->addChild(barSprite, 2);
	/*阳光和对应的数值板*/
	auto currentSun = Sprite::create("game/gamelayer/sun.png");
	currentSun->setAnchorPoint(Vec2::ZERO);
	currentSun->setPosition(Vec2(25, 540));
	this->addChild(currentSun, 3);
	auto sunSum = Sprite::create("game/gamelayer/sunNum.png");
	sunSum->setAnchorPoint(Vec2::ZERO);
	sunSum->setPosition(Vec2(25, 520));
	this->addChild(sunSum, 3);

	//铲子  su 2.25
	auto shovelback = Sprite::create("game/gameLayer/ShovelBack.png");
	shovelback->setAnchorPoint(Vec2::ZERO);
	shovelback->setPosition(Vec2(725,540));
	this->addChild(shovelback,2);
	auto shovel = Sprite::create("game/gameLayer/Shovel.png");
	shovel->setAnchorPoint(Vec2::ZERO);
	shovel->setPosition(Vec2(725, 540));
	this->addChild(shovel,3);

	for (int i = 0; i < count; i++)
	{
		if (a[i]>0)
		{ 
			/*道具所需的阳光值 */
			if (1 <= a[i] && a[i] <= 2)
				prop[i].score = 50;
			if ((a[i] == 3) || (a[i] == 6))
				prop[i].score = 100;
			if (a[i] == 4)
				prop[i].score = 150;
			if (a[i] == 5)
				prop[i].score = 125;

			prop[i].value = a[i];
			char file[100];
			sprintf(file, "game/card/%02d.png", a[i]);
			auto sprite1 = Sprite::create(file);
			auto sprite2 = Sprite::create(file);
			sprite1->setScale(0.8f);
			sprite2->setScale(0.8f);
			addChild(sprite1, 50, 50 + a[i]);
			sprite1->setPosition(Vec2(70 + i * 55, 520));
			sprite1->setAnchorPoint(Point::ZERO);
			sprite1->setColor(Color3B(80, 80, 80));

			sprite2->setAnchorPoint(Point::ZERO);
			auto left = ProgressTimer::create(sprite2);
			left->setType(ProgressTimer::Type::BAR);
			left->setMidpoint(Point(0, 0));
			left->setBarChangeRate(Point(0, 1));
			addChild(left, 60, 200 + a[i]);
			left->setPosition(Vec2(70 + i * 55, 520));
			left->setAnchorPoint(Point::ZERO);
			left->setPercentage(0);
		}
	}
	propStart = true;      
	audioID = AudioEngine::play2d("game/sound/UltimateBattle.mp3", true, VolumSet::getInstance()->getVolum());
	sun->showWordint(entityInteractManager->getSunScore(), Vec2(25, 518));
	gold->showWordint(UserManager::getInstance()->getUserGold(), Vec2(160, 10));
	torchwoodNum->showWordint(UserManager::getInstance()->getUserPropertyByID(GameEntityType::torchwood), Vec2(680, 530));
	iceshroomNum->showWordint(UserManager::getInstance()->getUserPropertyByID(GameEntityType::iceshroom), Vec2(580, 530));

	auto point = Sprite::create("game/gameLayer/score.png");
	point->setAnchorPoint(Vec2::ZERO);
	point->setPosition(Vec2(660, 0));
	this->addChild(point, 3);
	

	menu->setVisible(true);
}

void SurvivalMode::update(float ft)
{
	if (propStart)
	{
		AudioEngine::setVolume(audioID, VolumSet::getInstance()->getVolum());
		sun->showWordint(entityInteractManager->getSunScore(), Vec2(25, 518));
		gold->showWordint(UserManager::getInstance()->getUserGold(), Vec2(160, 10));
		pword->showWordint(entityInteractManager->getPoint(), Vec2(725, 0));
		torchwoodNum->showWordint(UserManager::getInstance()->getUserPropertyByID(GameEntityType::torchwood), Vec2(680, 530));
		iceshroomNum->showWordint(UserManager::getInstance()->getUserPropertyByID(GameEntityType::iceshroom), Vec2(580, 530));
		for (int i = 0; i<7; i++)
		{
			if (prop[i].value>0)
			{
				if (entityInteractManager->getSunScore() >= prop[i].score)     //当前阳光值大于等于植物需要的阳光值
				{
					if (prop[i].on2)   
					{
						auto sprite = this->getChildByTag(200 + prop[i].value);
						sprite->setScale(0.8f);
						dynamic_cast<ProgressTimer*>(sprite)->setPercentage(100);
						prop[i].on = true;
					}
					else       //卡片恢复过程中
					{
						prop[i].on = false;
					}

				}
				else
				{

					if (prop[i].on2)
					{
						dynamic_cast<ProgressTimer*>(this->getChildByTag(200 + prop[i].value))->setPercentage(0);
						prop[i].on = false;
					}
					else prop[i].on = false;
				}
			}
		}
	}

}

void SurvivalMode::menuCloseCallback(Ref* pSender)
{
	VolumSet::getInstance()->setMode(GameScene::survival_mode);
	GameMenuUI* scene = GameMenuUI::create();
	//((GameMenuUI*)scene)->setMode(GameScene::adventure_mode);
	this->addChild(scene, 2);
}

bool SurvivalMode::onTouchBegan(Touch* touch, Event* event)
{
	auto pos = touch->getLocation();                            
	//点击道具栏
	if (propStart)      //开始后点击上面的道具条才有反应
	{
		entityInteractManager->collectSunshine(pos);
		entityInteractManager->collectGold(pos);

		if (getChildByTag(GameEntityType::torchwood)->getBoundingBox().containsPoint(pos)){
			entityInteractManager->UnleashFireBuff(this);
		}
		if (getChildByTag(GameEntityType::iceshroom)->getBoundingBox().containsPoint(pos)){
			entityInteractManager->UnleashIceBuff(this);
		}

		if (pos.x >= 70 && pos.x <= 445 && pos.y > 520 && pos.y<520 + 70)
		{
			x1 = (pos.x - 70) / 55;
			if (prop[x1]. on)          //on用于判断卡片是否处于激活状态       
			{
				if (prop[x1].value>0)
				{
					char file[100];
					sprintf(file, "game/plants/kinds/%02d.png", prop[x1].value);     
					spriteOne = Sprite::create(file);
					addChild(spriteOne, 200, 100 + prop[x1].value);
					spriteOne->setScale(0.9f);
					spriteOne->setVisible(false);
				}
			}
		}
		else if (pos.x >= 728 && pos.x <= 800 && pos.y >= 540 && pos.y <= 575)
		{
			shovelSprite= Sprite::create("game/gameLayer/Shovel_using.png");
			addChild(shovelSprite, 6);
			isShovel = true;
		}
	}
	return true;
}
void SurvivalMode::onTouchMoved(Touch* touch, Event* event)
{
	if (propStart&&spriteOne)   //开始 并且spriteOne非空，控制在卡片恢复过程中再次点击不反应
	{
		Vec2 pos;
		pos = touch->getLocation();	
		spriteOne->setPosition(pos);
		spriteOne->setScale(0.6f);
		spriteOne->setVisible(true);
	}
	if (isShovel)
	{
		Vec2 pos;
		pos = touch->getLocation();
		shovelSprite->setPosition(pos);
	}
}

void SurvivalMode::onTouchEnded(Touch* touch, Event* event)
{
	if (propStart&&spriteOne)
	{
		int tag = spriteOne->getTag();
		spriteOne->removeFromParentAndCleanup(true);
		spriteOne = NULL;
		Vec2 pos = touch->getLocation();

		// new植物
		GameEntity* plant = NULL;
		if (gridManager->isValidate(pos))
		{
			pos = gridManager->getCoordPosition();
			plant = gameEntityManager->haveEntity(GameEntityType(tag), pos);		
			this->addChild(plant);

			if (plant->getType() == GameEntityType::cherrybomb){
				entityInteractManager->plantCherryBomb(this, plant);
			}
			else if (plant->getType() == GameEntityType::jalapeno){
				entityInteractManager->plantJalapeno(this, plant);
			}

			float time = plant->getSpeed();
			prop[x1].on2 = false;    //on2设置成false后，update函数中进度条将不能再变化
			prop[x1].on = false;
			auto sprite3 = dynamic_cast<ProgressTimer*>(this->getChildByTag(tag + 100));
			auto top = ProgressTo::create(time, 100);
			sprite3->setPercentage(0);
			sprite3->runAction(Sequence::create(top, CallFuncN::create(this, callfuncN_selector(SurvivalMode::offToOn)), NULL));
			entityInteractManager->setSunScore(entityInteractManager->getSunScore() - prop[x1].score);
		}
	}
	else if (isShovel)
	{
		shovelSprite->removeFromParentAndCleanup(true);

		Vec2 pos = touch->getLocation();
		if (gridManager->isCanShovel(pos))
		{
			pos = gridManager->getCoordPosition();
			entityInteractManager->ShovelPlant(pos);
		}

		isShovel = false;

	}
}

/*卡片恢复后，重新设置on,on2*/
void SurvivalMode::offToOn(Node* p)
{
	int tag = p->getTag() - 200;
	for (int i = 0; i<7; i++)
	{
		if (prop[i].value == tag)
		{
			prop[i].on2 = true;
			prop[i].on = true;
		}
	}
}

void SurvivalMode::gamePass(){
	Director::getInstance()->replaceScene(LevelPassScene::createScene());
	AudioEngine::stop(audioID);
	AudioEngine::uncache("game/sound/UltimateBattle.mp3");
}

void SurvivalMode::gameFailure(){
	//su 2.26
	struct tm *tm;
	time_t timep;
	time(&timep);
	tm = localtime(&timep);
	int year = tm->tm_year + 1900;
	int month = tm->tm_mon + 1;
	int day = tm->tm_mday;
	int hour = tm->tm_hour;
	int minute = tm->tm_min;
	int second = tm->tm_sec;
	std::string text;
	CCString* syear = CCString::createWithFormat("%d", year);
	CCString* smonth = CCString::createWithFormat("%02d", month);
	CCString* sday = CCString::createWithFormat("%02d", day);
	CCString* shour = CCString::createWithFormat("%02d", hour);
	CCString* smin = CCString::createWithFormat("%02d", minute);
	CCString* ssec = CCString::createWithFormat("%02d", second);
	text = syear->_string + "-" + smonth->_string + "-" + sday->_string + "    " +
		shour->_string + ":" + smin->_string + ":" + ssec->_string;
	int point = entityInteractManager->getPoint();

	DataConfig::getInstance()->setUserScoreToConfig(text,point);
	auto userManager = UserManager::getInstance();
	userManager->setHistoryPoint(text,point);

	auto scene = LevelFailureScene::createScene();
	Director::getInstance()->replaceScene(scene);
	AudioEngine::stop(audioID);
	AudioEngine::uncache("game/sound/UltimateBattle.mp3");
}
	
SurvivalMode::~SurvivalMode()
{
	AudioEngine::stop(audioID);
	AudioEngine::uncache("game/sound/UltimateBattle.mp3");
}