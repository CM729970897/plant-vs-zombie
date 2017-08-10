#include "GameMenuUI.h"
#include "MainMenuScene.h"
#include "AudioEngine.h"
#include "ui\CocosGUI.h"
#include "Volum.h"
#include "AdventureScene.h"
#include "SurvivalScene.h"

USING_NS_CC;
using namespace experimental;
using namespace ui;

Scene* GameMenuUI::createScene()
{
	auto scene = Scene::create();
	auto layer = GameMenuUI::create();
	scene->addChild(layer, 0);
	return scene;
}

bool GameMenuUI::init(){
	if (!Layer::init())
	{
		return false;
	}

	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(GameMenuUI::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(GameMenuUI::onTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(GameMenuUI::onTouchEnded, this);
	listener->setSwallowTouches(true);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto origin = Director::getInstance()->getVisibleOrigin();

	auto background = Sprite::create("game/gamelayer/GameMenuBack.png");
	background->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	this->addChild(background);

	auto confirm = MenuItemImage::create("game/gamelayer/Confirm.png", "game/gamelayer/Confirm_down.png", CC_CALLBACK_1(GameMenuUI::confirm, this));
	confirm->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y - 190));
	confirm->setScale(1.5f);

	auto restart = MenuItemImage::create("game/gameLayer/restartBtn.png", "game/gameLayer/restartBtn_selected.png", CC_CALLBACK_1(GameMenuUI::restart, this));
	restart->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 -60));

	auto mainmenu = MenuItemImage::create("game/gameLayer/mainMenuBtn.png", "game/gameLayer/mainMenuBtn.png", CC_CALLBACK_1(GameMenuUI::backMainMenu, this));
	mainmenu->setPosition(Vec2(visibleSize.width/2,visibleSize.height/2-105));

	mode = VolumSet::getInstance()->getMode();
	switch (mode){
	case GameScene::adventure_mode:
	case GameScene::survival_mode:
		op_menu = Menu::create(confirm, restart,mainmenu, NULL);
		break;
	default:
		op_menu = Menu::create(confirm, NULL);
		break;
	}

	op_menu->setPosition(Point::ZERO);
	this->addChild(op_menu);
	op_menu->setTouchEnabled(true);

	Slider* slider = Slider::create();
	slider->loadBarTexture("game/menuLayer/sliderTrack.png");
	slider->loadSlidBallTextures("game/menuLayer/sliderThumb.png", "game/menuLayer/sliderThumb.png","");
	slider->loadProgressBarTexture("game/menuLayer/sliderProgress.png");
	slider->setPosition(Vec2(432,385));
	slider->setPercent(VolumSet::getInstance()->getSliderPercent());
	slider->addEventListener([&](Ref* sender, Slider::EventType type)
	{
		auto s = dynamic_cast<Slider*>(sender);
		int sliderPercent = s->getPercent();
		float volum = 1.0f*s->getPercent() / s->getMaxPercent();
		VolumSet::getInstance()->setVolum(volum);
		VolumSet::getInstance()->setSliderPercent(sliderPercent);

	});
	this->addChild(slider);

	Slider* tslider = Slider::create();
	tslider->loadBarTexture("game/menuLayer/sliderTrack.png");
	tslider->loadSlidBallTextures("game/menuLayer/sliderThumb.png", "game/menuLayer/sliderThumb.png", "");
	tslider->loadProgressBarTexture("game/menuLayer/sliderProgress.png");
	tslider->setPosition(Vec2(432, 340));
	tslider->setPercent(VolumSet::getInstance()->getTSliderPercent());
	tslider->addEventListener([&](Ref* sender, Slider::EventType type)
	{
		auto ts = dynamic_cast<Slider*>(sender);
		int tsliderPercent = ts->getPercent();
		float tvolum = 1.0f*ts->getPercent() / ts->getMaxPercent();
		VolumSet::getInstance()->setTVolum(tvolum);
		VolumSet::getInstance()->setTSliderPercent(tsliderPercent);

	});
	this->addChild(tslider);


	return true;
}

void GameMenuUI::confirm(Ref*){
	/*if (mode == GameScene::main_menu)
		((MainMenuScene*)(this->getParent()))->resetMainMenu();*/
	this->removeFromParent();
}

void GameMenuUI::backMainMenu(Ref*)
{
	GameEntityManager::getInstance()->gameEntityArray.clear();
	DerivedEntityManager::getInstance()->derivedEntityArray.clear();
	DerivedEntityManager::getInstance()->goldArray.clear();
	GridManager::getInstance()->resetStatus();
	if (mode == GameScene::adventure_mode )
	{
		Director::getInstance()->replaceScene(MainMenuScene::createScene());
	}
	else if (mode == GameScene::survival_mode)
	{
		Director::getInstance()->replaceScene(MainMenuScene::createScene());
	}
}
void GameMenuUI::restart(Ref*)
{
		GameEntityManager::getInstance()->gameEntityArray.clear();
		DerivedEntityManager::getInstance()->derivedEntityArray.clear();
		DerivedEntityManager::getInstance()->goldArray.clear();
		GridManager::getInstance()->resetStatus();
		if (mode == GameScene::adventure_mode)
		{
			((AdventureMode*)(this->getParent()))->removeFromParent();
			Director::getInstance()->replaceScene(AdventureMode::createScene());
		}
		else if (mode == GameScene::survival_mode)
		{
			((SurvivalMode*)(this->getParent()))->removeFromParent();
			Director::getInstance()->replaceScene(SurvivalMode::createScene());
		}

}


bool GameMenuUI::onTouchBegan(Touch* touch, Event* event)
{
	return true;
}
void GameMenuUI::onTouchMoved(Touch* touch, Event* event)
{
}

void GameMenuUI::onTouchEnded(Touch* touch, Event* event)
{

}