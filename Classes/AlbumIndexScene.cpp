#include "AlbumIndexScene.h"
#include "AlbumPlantsScene.h"
#include "AlbumZombiesScene.h"
#include "MainMenuScene.h"
#include "AudioEngine.h"
#include "Volum.h"

USING_NS_CC;
using namespace experimental;

Scene* AlbumIndexScene::createScene()
{
	auto scene = Scene::create();
	auto layer = AlbumIndexScene::create();
	scene->addChild(layer);
	return scene;

}

bool AlbumIndexScene::init(){

	if (!Layer::init())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto origin = Director::getInstance()->getVisibleOrigin();

	auto background = Sprite::create("game/albumlayer/background.png");
	background->setScale(1.0f);
	background->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	this->addChild(background, 0);

	auto plant = MenuItemImage::create("game/albumlayer/plant.png", "game/albumlayer/plant_down.png", CC_CALLBACK_1(AlbumIndexScene::plantIndex, this));
	plant->setScale(1.2f);
	plant->setPosition(Vec2(visibleSize.width / 2 + origin.x - 200, visibleSize.height / 2 + origin.y - 10));
	
	auto zombie = MenuItemImage::create("game/albumlayer/zombie.png", "game/albumlayer/zombie_down.png", CC_CALLBACK_1(AlbumIndexScene::zombieIndex, this));
	zombie->setScale(1.0f);
	zombie->setPosition(Vec2(visibleSize.width / 2 + origin.x + 200, visibleSize.height / 2 + origin.y - 10));

	auto close = MenuItemImage::create("game/interface/Almanac_CloseButton.png", "game/interface/Almanac_CloseButtonHighlight.png", CC_CALLBACK_1(AlbumIndexScene::mainMenu, this));
	close->setScale(1.2f);
	close->setPosition(Vec2(visibleSize.width / 2 + origin.x + 338, origin.y + 20));

	auto menu = Menu::create(plant, zombie, close, NULL);
	menu->setPosition(Point::ZERO);
	this->addChild(menu);

	audioID=AudioEngine::play2d("game/sound/Moongrains.mp3", true,VolumSet::getInstance()->getVolum());
	return true;

}

void AlbumIndexScene::plantIndex(Ref*){
	auto scene = AlbumPlantsScene::createScene();
	Director::getInstance()->pushScene(scene);
}
	
void AlbumIndexScene::zombieIndex(Ref*){
	auto scene = AlbumZombiesScene::createScene();
	Director::getInstance()->pushScene(scene);
}

void AlbumIndexScene::mainMenu(Ref*){
	AudioEngine::stop(audioID);
	AudioEngine::uncache("game/sound/Moongrains.mp3");
	auto scene = MainMenuScene::createScene();
	Director::getInstance()->replaceScene(scene);

}