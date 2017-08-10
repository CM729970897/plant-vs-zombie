#include "OptPropUI.h"
#include "SurvivalScene.h"
#include "AdventureScene.h"
#include "cocos2d.h"
#include "AudioEngine.h"
#include "Volum.h"

USING_NS_CC;
using namespace experimental;

Scene* OptPropUI::createScene()
{
	auto scene = Scene::create();
	auto layer = OptPropUI::create();
	scene->addChild(layer,0,800);
	return scene;
}

bool OptPropUI::init()
{
	if(!Layer::init())
		return false;

		//监听事件
	auto listener=EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(OptPropUI::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(OptPropUI::onTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(OptPropUI::onTouchEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
	
	auto panelSprite = Sprite::create("game/gamelayer/ChoosingPanel.png");  //植物面板
	panelSprite->setAnchorPoint(Vec2(0,0));
	panelSprite->setPosition(Vec2(0,0));
	this->addChild(panelSprite,2);
	panelSprite->setScaleY(0.93f);
	panelSprite->setScaleX(0.83f);
	
	menuItem=MenuItemImage::create("game/gamelayer/btnOk2.png","game/gamelayer/btnOk3.png",
		"game/gamelayer/btnOk1.png",CC_CALLBACK_1(OptPropUI::menuCloseCallback,this));
	menuItem->setEnabled(false);
	auto menu = Menu::create(menuItem, NULL);
	this->addChild(menu, 3);
	menu->setAnchorPoint(Vec2::ZERO);
	menu->setPosition(Vec2(220, 30));

	sumPlant = 6;
	propCount = 0;
	propSum = 7;
	int count = 0;
	memset(optValue, 0, sizeof(optValue));
	memset(prop, 0, sizeof(prop));
	for (int i = 0; i<7; i++)
	{
		start[i].start = Point::ZERO;
		start[i].x = -1;
		start[i].y = -1;
		start[i].value = 0;
	}

	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			if (count < sumPlant)
			{
				char file[100];
				sprintf(file, "game/card/%02d.png", count + 1);
				Sprite* sprite1 = Sprite::create(file);
				Sprite* sprite2 = Sprite::create(file);
				sprite1->setScale(0.8f);
				sprite2->setScale(0.8f);
				addChild(sprite1, 4, 50 + count+1);

				addChild(sprite2, 3);
				sprite2->setAnchorPoint(Vec2::ZERO);
				sprite2->setPosition(Vec2(30 + j * 65, 400 - i * 80));
				sprite2->setColor(Color3B(80,80,80));
				sprite1->setAnchorPoint(Vec2::ZERO);
				sprite1->setPosition(Vec2(30 + j * 65, 400 - i * 80));
				count++;
				optValue[i][j] = 50 + count;
			}
			else
			{
				auto sprite = Sprite::create("game/gamelayer/smallBatch.png");
				addChild(sprite, 2);
				sprite->setAnchorPoint(Point::ZERO);
				sprite->setPosition(30 + j * 65, 400 - i * 80);
				sprite->setScaleX(0.78f);
				sprite->setScaleY(0.71f);
			}
		}
	}

	/*道具栏*/
	auto barSprite = Sprite::create("game/gamelayer/ChosenBar.png");   //道具条
	barSprite->setAnchorPoint(Vec2::ZERO);
	barSprite->setPosition(Vec2(0,515));
	barSprite->setScaleX(1.0f);
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

//	CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("game/sound/ChooseYourSeeds.wav", true);
	audioID = AudioEngine::play2d("game/sound/ChooseYourSeeds.mp3",true,VolumSet::getInstance()->getVolum());

	return true;
}

bool OptPropUI::onTouchBegan(Touch* a,Event* b)
{
	Vec2 pox = a->getLocation();
	if (pox.x>=30&&pox.x<=340&&pox.y>=80&&pox.y<=472)  // 选择面板
	{
		int x = (pox.x - 30) / 65;
		int y = (472 - pox.y) / 80;
		if (propCount < propSum)
		{
			if (optValue[y][x]>0)
			{
			auto sprite = this->getChildByTag(optValue[y][x]);
			start[propCount].start = sprite->getPosition();   //在面板中的位置
			start[propCount].x = x;   //记下原来道具栏中道具原来的位置
			start[propCount].y = y;
			start[propCount].value = optValue[y][x];         //道具栏   Tag
			optValue[y][x] = 0;
			sprite->setAnchorPoint(Vec2::ZERO);
			sprite->setScale(0.8f);
			sprite->runAction(MoveTo::create(0.2f,Vec2(70+propCount*55,520)));
			
			propCount++;
			if (propCount >= 6)
				menuItem->setEnabled(true);
			}
		}
	}

	else if (pox.x >= 70 && pox.x <= propSum*55+70&&pox.y>=520&&pox.y<=595)     //点击上面的已选择道具条
	{
		int k = (pox.x - 70) / 55;
		if (start[k].value > 0)
		{
			auto sprite = this->getChildByTag(start[k].value);
			sprite->runAction(MoveTo::create(0.1f,Vec2(start[k].start)));
			optValue[start[k].y][start[k].x] = start[k].value;
			for (int i = k + 1; i < propCount; i++)   //后面的往前移动
			{
				auto sprite1 = this->getChildByTag(start[i].value);
				sprite1->runAction(MoveTo::create(0.2f,Vec2(70+(i-1)*55,515)));
				start[i - 1] = start[i];
				if (i == propCount - 1)
					start[i].value = 0;
			}
			propCount--;
			if (propCount < 6){
				menuItem->setEnabled(false);
			}
		}
	}

	return true;
}
void OptPropUI::onTouchMoved(Touch* a,Event* b)
{
	
}
void OptPropUI::onTouchEnded(Touch* a,Event* b)
{

}

void OptPropUI::menuCloseCallback(cocos2d::Ref* pSender)   //点击确认
{
	/**************/
	int Count = 0;
	int prop[7];
	for (int i = 0; i<7; i++)
	{
		if (start[i].value != 0)
		{
			prop[Count] = start[Count].value - 50;
			Count++;
		}
	}

	if (VolumSet::getInstance()->getMode() == GameScene::adventure_mode)
	{
		auto Scene = dynamic_cast<AdventureMode*>(Director::getInstance()->getRunningScene()->getChildByTag(900));
		Scene->creatProp(prop, Count);
	}
	else if (VolumSet::getInstance()->getMode() == GameScene::survival_mode)
	{
		auto Scene = dynamic_cast<SurvivalMode*>(Director::getInstance()->getRunningScene()->getChildByTag(900));
		Scene->creatProp(prop, Count);
	}
	AudioEngine::stop(audioID);
	AudioEngine::uncache("game/sound/ChooseYourSeeds.mp3");
	this->removeFromParentAndCleanup(true);
}
void OptPropUI::remove()
{
	this->removeFromParentAndCleanup(true);
}



OptPropUI::OptPropUI()
{

}
OptPropUI::~OptPropUI()
{

}