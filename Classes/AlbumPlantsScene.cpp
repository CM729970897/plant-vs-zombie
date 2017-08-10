#include "AlbumPlantsScene.h"
#include "AlbumIndexScene.h"
#include "MainMenuScene.h"
#include "GameEntityManager.h"
#include "DataConfig.h"
#include "AudioEngine.h"
#include "Volum.h"

USING_NS_CC;
using namespace experimental;

Scene* AlbumPlantsScene::createScene()
{
	auto scene = Scene::create();
	auto layer = AlbumPlantsScene::create();
	scene->addChild(layer);
	return scene;
}

bool AlbumPlantsScene::init(){
	if (!Layer::init())
	{
		return false;
	}                      

	plantMap = DataConfig::getInstance()->getPlantsMessageFromConfig();
	word = FlowWord::create();
	word->getLableTTF()->setHorizontalAlignment(kCCTextAlignmentLeft);   //左对齐
	word->getLableTTF()->setColor(Color3B(0,0,255));
	word->getLableTTF()->setAnchorPoint(Vec2::ANCHOR_TOP_LEFT);
	this->addChild(word, 2);
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto origin = Director::getInstance()->getVisibleOrigin();

	auto background = Sprite::create("game/albumlayer/plant_background.png");
	background->setScale(1.0f);
	background->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	this->addChild(background, 0);

	auto back = MenuItemImage::create("game/commonlayer/IndexButton.png", "game/commonlayer/IndexButton_down.png", CC_CALLBACK_1(AlbumPlantsScene::albumIndex, this));
	back->setScale(1.2f);
	back->setPosition(Vec2(120, origin.y + 20));

	auto close = MenuItemImage::create("game/commonlayer/CloseButton.png", "game/commonlayer/CloseButton_down.png", CC_CALLBACK_1(AlbumPlantsScene::mainMenu, this));
	close->setScale(1.2f);
	close->setPosition(Vec2(visibleSize.width / 2 + origin.x + 338, origin.y + 20));

	auto sunFlower = MenuItemImage::create("game/card/01.png", "game/card/01.png", CC_CALLBACK_1(AlbumPlantsScene::display_sunFlower, this));
	sunFlower->setScale(0.8f);
	sunFlower->setPosition(Vec2(origin.x + 50, visibleSize.height / 2 + origin.y + 170));

	auto wallNut = MenuItemImage::create("game/card/02.png", "game/card/02.png", CC_CALLBACK_1(AlbumPlantsScene::display_wallNut, this));
	wallNut->setScale(0.8f);
	wallNut->setPosition(Vec2(origin.x + 105, visibleSize.height / 2 + origin.y + 170));

	auto peaShooter = MenuItemImage::create("game/card/03.png", "game/card/03.png", CC_CALLBACK_1(AlbumPlantsScene::display_peaShooter, this));
	peaShooter->setScale(0.8f);
	peaShooter->setPosition(Vec2(origin.x + 160, visibleSize.height / 2 + origin.y + 170));

	auto introduce = Sprite::create("game/albumLayer/PlantCard.png");
	introduce->setScale(0.98f);
	introduce->setPosition(Vec2(visibleSize.width / 2 + origin.x + 220, visibleSize.height / 2 - 18));
	this->addChild(introduce, 0);

	//su 2.26
	auto cherryBomb = MenuItemImage::create("game/card/04.png", "game/card/04.png", CC_CALLBACK_1(AlbumPlantsScene::display_cherryBomb, this));
	cherryBomb->setScale(0.8f);
	cherryBomb->setPosition(Vec2(origin.x+205,visibleSize.height/2+origin.y+170));
	auto jalapeno = MenuItemImage::create("game/card/05.png", "game/card/05.png", CC_CALLBACK_1(AlbumPlantsScene::display_jalapeno, this));
	jalapeno->setScale(0.8f);
	jalapeno->setPosition(Vec2(origin.x + 260, visibleSize.height / 2 + origin.y + 170));

	//su 2.28
	auto bamBoo = MenuItemImage::create("game/card/06.png", "game/card/06.png", CC_CALLBACK_1(AlbumPlantsScene::display_bamBoo, this));
	bamBoo->setScale(0.8f);
	bamBoo->setPosition(Vec2(origin.x + 315, visibleSize.height / 2 + origin.y + 170));

	auto menu = Menu::create(back, close, sunFlower, peaShooter, wallNut,cherryBomb,jalapeno,bamBoo,NULL);
	menu->setPosition(Point::ZERO);
	this->addChild(menu);

//	display_sunFlower(this);

	return true;
}

void AlbumPlantsScene::albumIndex(Ref*){
	AudioEngine::uncache("game/sound/Moongrains.mp3");
	auto scene = AlbumIndexScene::createScene();
	Director::getInstance()->replaceScene(scene);
}

void AlbumPlantsScene::mainMenu(Ref*){
	AudioEngine::uncache("game/sound/Moongrains.mp3");
	auto scene = MainMenuScene::createScene();
	Director::getInstance()->replaceScene(scene);
}

void AlbumPlantsScene::display_sunFlower(Ref*){
	this->addChild(GameEntityManager::getInstance()->haveEntityForAlbum(GameEntityType::sunflower, Vec2(620, 430)));
	word->showWord(plantMap["sunflower"], Vec2(495, 280));
}

void AlbumPlantsScene::display_peaShooter(Ref*){
	this->addChild(GameEntityManager::getInstance()->haveEntityForAlbum(GameEntityType::peashooter, Vec2(620, 430)));
	word->showWord(plantMap["peashooter"], Vec2(495, 280));
}

void AlbumPlantsScene::display_wallNut(Ref*){
	this->addChild(GameEntityManager::getInstance()->haveEntityForAlbum(GameEntityType::wallnut, Vec2(620, 430)));
	word->showWord(plantMap["wallnut"], Vec2(495, 280));
}
void AlbumPlantsScene::display_cherryBomb(Ref*){
	this->addChild(GameEntityManager::getInstance()->haveEntityForAlbum(GameEntityType::cherrybomb, Vec2(620, 430)));
	word->showWord(plantMap["cherrybomb"], Vec2(495, 280));
}
void AlbumPlantsScene::display_jalapeno(Ref*){
	this->addChild(GameEntityManager::getInstance()->haveEntityForAlbum(GameEntityType::jalapeno, Vec2(620, 430)));
	word->showWord(plantMap["jalapeno"], Vec2(495, 280));
}

void AlbumPlantsScene::display_bamBoo(Ref*)
{
	this->addChild(GameEntityManager::getInstance()->haveEntityForAlbum(GameEntityType::flashbamboo, Vec2(620, 430)));
	word->showWord(plantMap["bamboo"], Vec2(495, 280));
}