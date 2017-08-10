#include "AlbumZombiesScene.h"
#include "AlbumIndexScene.h"
#include "MainMenuScene.h"
#include "GameEntityManager.h"
#include "AudioEngine.h"
#include "Volum.h"

USING_NS_CC;
using namespace experimental;

Scene* AlbumZombiesScene::createScene()
{
	auto scene = Scene::create();
	auto layer = AlbumZombiesScene::create();
	scene->addChild(layer);
	return scene;
}

bool AlbumZombiesScene::init(){

	if (!Layer::init())
	{
		return false;
	}
	zombieMap = DataConfig::getInstance()->getZombiesMessageFromConfig();
	word = FlowWord::create();
	word->getLableTTF()->setHorizontalAlignment(kCCTextAlignmentLeft);   //×ó¶ÔÆë
	word->getLableTTF()->setAnchorPoint(Vec2::ANCHOR_TOP_LEFT);
	word->getLableTTF()->setColor(Color3B(0, 0, 255));
	this->addChild(word, 2);

	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto origin = Director::getInstance()->getVisibleOrigin();

	auto background = Sprite::create("game/albumlayer/zombie_background.png");
	background->setScale(1.0f);
	background->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	this->addChild(background, 0);

	auto back = MenuItemImage::create("game/commonlayer/IndexButton.png", "game/commonlayer/IndexButton_down.png", CC_CALLBACK_1(AlbumZombiesScene::albumIndex, this));
	back->setScale(1.2f);
	back->setPosition(Vec2(120, origin.y + 20));

	auto close = MenuItemImage::create("game/commonlayer/CloseButton.png", "game/commonlayer/CloseButton_down.png", CC_CALLBACK_1(AlbumZombiesScene::mainMenu, this));
	close->setScale(1.2f);
	close->setPosition(Vec2(visibleSize.width / 2 + origin.x + 338, origin.y + 20));

	auto zombie = MenuItemImage::create("game/card/zombie.png", "game/card/zombie.png", CC_CALLBACK_1(AlbumZombiesScene::display_zombie, this));
	zombie->setScale(0.8f);
	zombie->setPosition(Vec2(origin.x + 70, visibleSize.height / 2 + origin.y + 160));

	auto flagZombie = MenuItemImage::create("game/card/flagZombie.png", "game/card/flagZombie.png", CC_CALLBACK_1(AlbumZombiesScene::display_flagZombie, this));
	flagZombie->setScale(0.8f);
	flagZombie->setPosition(Vec2(origin.x + 180, visibleSize.height / 2 + origin.y + 160));

	auto coneheadZombie = MenuItemImage::create("game/card/coneheadZombie.png", "game/card/coneheadZombie.png", CC_CALLBACK_1(AlbumZombiesScene::display_coneheadZombie, this));
	coneheadZombie->setScale(0.8f);
	coneheadZombie->setPosition(Vec2(origin.x + 290, visibleSize.height / 2 + origin.y + 160));

	auto bucketheadZombie = MenuItemImage::create("game/card/bucketheadZombie.png", "game/card/bucketheadZombie.png", CC_CALLBACK_1(AlbumZombiesScene::display_bucketheadZombie, this));
	bucketheadZombie->setScale(0.8f);
	bucketheadZombie->setPosition(Vec2(origin.x + 400, visibleSize.height / 2 + origin.y + 160));

	auto menu = Menu::create(back, close, zombie, flagZombie, coneheadZombie, bucketheadZombie, NULL);
	menu->setPosition(Point::ZERO);
	this->addChild(menu);

	auto introduce = Sprite::create("game/albumLayer/ZombieCard.png");
	introduce->setScale(0.98f);
	introduce->setPosition(Vec2(visibleSize.width / 2 + origin.x + 220, visibleSize.height / 2 - 20));
	this->addChild(introduce, 0);
	
	//display_zombie(this);

	return true;
}

void AlbumZombiesScene::albumIndex(Ref*){
	AudioEngine::uncache("game/sound/Moongrains.mp3");
	auto scene = AlbumIndexScene::createScene();
	Director::getInstance()->replaceScene(scene);
}

void AlbumZombiesScene::mainMenu(Ref*){
	AudioEngine::uncache("game/sound/Moongrains.mp3");
	auto scene = MainMenuScene::createScene();
	Director::getInstance()->replaceScene(scene);
}

void AlbumZombiesScene::display_zombie(Ref*){
	this->addChild(GameEntityManager::getInstance()->haveEntityForAlbum(GameEntityType::zombie, Vec2(620, 390)));
	word->showWord(zombieMap["zombie"], Vec2(496, 210));
}

void AlbumZombiesScene::display_flagZombie(Ref*){
	this->addChild(GameEntityManager::getInstance()->haveEntityForAlbum(GameEntityType::flag_zombie, Vec2(620, 390)));
	word->showWord(zombieMap["flag_zombie"], Vec2(496, 210));
}

void AlbumZombiesScene::display_coneheadZombie(Ref*){
	this->addChild(GameEntityManager::getInstance()->haveEntityForAlbum(GameEntityType::conehead_zombie, Vec2(620, 390)));
	word->showWord(zombieMap["conehead_zombie"], Vec2(496, 210));
}

void AlbumZombiesScene::display_bucketheadZombie(Ref*){
	this->addChild(GameEntityManager::getInstance()->haveEntityForAlbum(GameEntityType::buckethead_zombie, Vec2(620, 390)));
	word->showWord(zombieMap["buckethead_zombie"], Vec2(496, 210));
}