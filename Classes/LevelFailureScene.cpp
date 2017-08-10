#include "LevelFailureScene.h"
#include "AdventureScene.h"
#include "SurvivalScene.h"
#include "MainMenuScene.h"
#include "AudioEngine.h"
#include "Volum.h"
#include "UserHistoryScoreUI.h"

USING_NS_CC;
using namespace experimental;

Scene* LevelFailureScene::createScene()
{
	auto scene = Scene::create();
	auto layer = LevelFailureScene::create();
	scene->addChild(layer);
	return scene;
}

bool LevelFailureScene::init(){
	if (!Layer::init())
	{
		return false;
	}
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto origin = Director::getInstance()->getVisibleOrigin();

	auto background = Sprite::create("game/GameLayer/GameOverBack.jpg");
	background->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	this->addChild(background);

	auto fail = Sprite::create("game/GameLayer/fail.png");
	fail->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y + 100));
	this->addChild(fail);

	auto back = MenuItemImage::create("game/commonLayer/IndexButton.png", "game/commonLayer/IndexButton_down.png", CC_CALLBACK_1(LevelFailureScene::tryAgain, this));
	back->setScale(1.2f);
	back->setPosition(Vec2(120, origin.y + 20));

	auto close = MenuItemImage::create("game/commonLayer/CloseButton.png", "game/commonLayer/CloseButton_down.png", CC_CALLBACK_1(LevelFailureScene::mainMenu, this));
	close->setScale(1.2f);
	close->setPosition(Vec2(visibleSize.width / 2 + origin.x + 338, origin.y + 20));

	auto menu = Menu::create(back, close, NULL);
	menu->setPosition(Point::ZERO);
	this->addChild(menu);

	audioID = AudioEngine::play2d("game/sound/Fail.mp3", false, VolumSet::getInstance()->getVolum());

	if (VolumSet::getInstance()->getMode() == GameScene::survival_mode)
	{
		auto his = UserHistoryScoreUI::createScene();
		this->addChild(his, 3);
	}

	UserManager::getInstance()->updateUserInfo();

	return true;
}

void LevelFailureScene::tryAgain(Ref*){
	AudioEngine::stop(audioID);
	AudioEngine::uncache("game/sound/Fail.mp3");
	if (VolumSet::getInstance()->getMode() == GameScene::adventure_mode)
	{
		auto scene = AdventureMode::createScene();
		Director::getInstance()->replaceScene(scene);
	}
	else
	{
		auto scene = SurvivalMode::createScene();
		Director::getInstance()->replaceScene(scene);
	}
}

void LevelFailureScene::mainMenu(Ref*){
	auto scene = MainMenuScene::createScene();
	Director::getInstance()->replaceScene(scene);
	AudioEngine::stop(audioID);
	AudioEngine::uncache("game/sound/Fail.mp3");
}

