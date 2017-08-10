#include "LevelPassScene.h"
#include "MainMenuScene.h"
#include "AdventureScene.h"
#include "AudioEngine.h"
#include "Volum.h"

USING_NS_CC;
using namespace experimental;

Scene* LevelPassScene::createScene()
{
	auto scene = Scene::create();
	auto layer = LevelPassScene::create();
	scene->addChild(layer);
	return scene;
}

bool LevelPassScene::init(){
	if (!Layer::init())
	{
		return false;
	}
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto origin = Director::getInstance()->getVisibleOrigin();

	auto background = Sprite::create("game/GameLayer/GameOverBack.jpg");
	background->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	this->addChild(background);

	auto trophy = Sprite::create("game/GameLayer/trophy.png");
	trophy->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y + 100));
	this->addChild(trophy);

	auto back = MenuItemImage::create("game/commonLayer/IndexButton.png", "game/commonLayer/IndexButton_down.png", CC_CALLBACK_1(LevelPassScene::nextLevel, this));
	back->setScale(1.2f);
	back->setPosition(Vec2(120, origin.y + 20));

	auto close = MenuItemImage::create("game/commonLayer/CloseButton.png", "game/commonLayer/CloseButton_down.png", CC_CALLBACK_1(LevelPassScene::mainMenu, this));
	close->setScale(1.2f);
	close->setPosition(Vec2(visibleSize.width / 2 + origin.x + 338, origin.y + 20));

	auto menu = Menu::create(back, close, NULL);
	menu->setPosition(Point::ZERO);
	this->addChild(menu);

	AudioEngine::play2d("game/sound/Pass.mp3",false,VolumSet::getInstance()->getVolum());
	UserManager::getInstance()->updateUserProgress();

	UserManager::getInstance()->updateUserInfo();

	return true;
}

void LevelPassScene::nextLevel(Ref*){
	auto scene = AdventureMode::createScene();
	Director::getInstance()->replaceScene(scene);
	AudioEngine::stop(audioID);
	AudioEngine::uncache("game/sound/Pass.mp3");
}

void LevelPassScene::mainMenu(Ref*){
	auto scene = MainMenuScene::createScene();
	Director::getInstance()->replaceScene(scene);
	AudioEngine::stop(audioID);
	AudioEngine::uncache("game/sound/Pass.mp3");
}