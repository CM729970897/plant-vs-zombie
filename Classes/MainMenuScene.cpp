#include "MainMenuScene.h"
#include "SimpleAudioEngine.h"
#include "AdventureScene.h"
#include "SurvivalScene.h"
#include "AlbumIndexScene.h"
#include "BagScene.h"
#include "ShopScene.h"
#include "UserListUI.h"
#include "UserManager.h"
#include "UserCreateUI.h"
#include "User.h"
#include "UserHistoryScoreUI.h"
#include "Volum.h"
#include "AudioEngine.h"

USING_NS_CC;
using namespace experimental;

Scene* MainMenuScene::createScene()
{
    auto scene = Scene::create();
	auto layer = MainMenuScene::create();
    scene->addChild(layer,0,333);
    return scene;
}

bool MainMenuScene::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
	this->scheduleUpdate();
	
	wordOk = FlowWord::create();
	this->addChild(wordOk, 5);
	
	//没有用户时进入主界面主动弹出创建用户编辑框
	if (UserManager::getInstance()->getUserList().empty())
	{
		auto usercreate = UserCreateUI::create();
		usercreate->setAnchorPoint(Vec2::ZERO);
		usercreate->setPosition(Vec2::ZERO);
		this->addChild(usercreate, 5);
	}


    auto visibleSize = Director::getInstance()->getVisibleSize();
	auto origin = Director::getInstance()->getVisibleOrigin();
	
    auto background = Sprite::create("game/menulayer/main_background.png");
	background->setScale(0.8f);
    background->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    this->addChild(background, 0);
	
	auto welcome = Sprite::create("game/menulayer/welcome.png");
	welcome->setScale(0.8f);
	/*welcome->setPosition(Vec2(visibleSize.width / 2 - 250 + origin.x, visibleSize.height / 2 + origin.y + 400));*/
	welcome->setPosition(Vec2(visibleSize.width / 2 - 250 + origin.x, visibleSize.height / 2 + origin.y +240));
	this->addChild(welcome);
	/*auto welcomeMoveTo = MoveTo::create(2, Vec2(visibleSize.width / 2 - 250 + origin.x, visibleSize.height / 2 + origin.y + 240));
	auto welcomeSequence = Sequence::create(welcomeMoveTo,NULL);
	welcome->runAction(welcomeSequence);*/


	auto user_selector = MenuItemImage::create("game/menulayer/user_select.png", "game/menulayer/user_select_down.png", CC_CALLBACK_1(MainMenuScene::userList, this));
	user_selector->setScale(0.8f);
	/*user_selector->setPosition(Vec2(visibleSize.width / 2 - 250 + origin.x, visibleSize.height / 2 + origin.y + 400));*/
	user_selector->setPosition(Vec2(visibleSize.width / 2 - 250 + origin.x, visibleSize.height / 2 + origin.y + 160));

	/*auto userSelectorMoveTo = MoveTo::create(2, Vec2(visibleSize.width / 2 - 250 + origin.x, visibleSize.height / 2 + origin.y + 160));
	auto userSelectorMoveSequence = Sequence::create(userSelectorMoveTo, NULL);
	user_selector->runAction(userSelectorMoveSequence);*/
	
	auto adventure = MenuItemImage::create("game/menulayer/adventure.png", "game/menulayer/adventure_down.png", CC_CALLBACK_1(MainMenuScene::adventureMode, this));
	adventure->setScale(0.8f);
	adventure->setPosition(Vec2(visibleSize.width / 2 + origin.x + 180, visibleSize.height / 2 + origin.y + 160));

	auto survival = MenuItemImage::create("game/menulayer/survival.png", "game/menulayer/survival_down.png", CC_CALLBACK_1(MainMenuScene::survivalMode, this));
	survival->setScale(0.9f);
	survival->setPosition(Vec2(visibleSize.width / 2 + origin.x + 160, visibleSize.height / 2 + origin.y));

	auto bag = MenuItemImage::create("game/menulayer/bag.png", "game/menulayer/bag_down.png", CC_CALLBACK_1(MainMenuScene::openBag, this));
	bag->setScale(0.2f);
	bag->setPosition(Vec2(visibleSize.width / 2 + origin.x -20, visibleSize.height / 2 + origin.y - 200));

	auto shop = MenuItemImage::create("game/menulayer/shop.png", "game/menulayer/shop_down.png", CC_CALLBACK_1(MainMenuScene::visitShop, this));
	shop->setPosition(Vec2(visibleSize.width / 2 + origin.x - 170, visibleSize.height / 2 + origin.y - 240));

	auto album = MenuItemImage::create("game/menulayer/album.png", "game/menulayer/album_down.png", CC_CALLBACK_1(MainMenuScene::albumIndex, this));
	album->setPosition(Vec2(visibleSize.width / 2 + origin.x + 120, visibleSize.height / 2 + origin.y - 240));
	
	auto settings = MenuItemImage::create("game/menulayer/settings.png", "game/menulayer/settings_down.png", CC_CALLBACK_1(MainMenuScene::gameset, this));
	settings->setPosition(Vec2(visibleSize.width / 2 + origin.x + 300, visibleSize.height / 2 + origin.y - 220));

	//su 2.25
	auto record = MenuItemImage::create("game/menuLayer/record.png","game/menuLayer/record_down.png",CC_CALLBACK_1(MainMenuScene::recordScore,this));
	record->setPosition(Vec2(103, 90));

	auto menu = Menu::create(bag, adventure, survival, shop, album, user_selector, settings,record, NULL);
	menu->setPosition(Point::ZERO);
	this->addChild(menu);

	audioID = AudioEngine::play2d("game/sound/CrazyDave.mp3", true,VolumSet::getInstance()->getVolum());
	VolumSet::getInstance()->setMode(GameScene::main_menu);

    return true;
}

void MainMenuScene::adventureMode(Ref*){
	if (UserManager::getInstance()->getCurrentUser())
	{
		auto scene = AdventureMode::createScene();
	//	auto crossFade = TransitionCrossFade::create(1, scene);
		Director::getInstance()->replaceScene(scene);
		/*AudioEngine::stop(audioID);
		AudioEngine::uncache("game/sound/Zombotany.mp3");*/
	}
}

void MainMenuScene::survivalMode(Ref*){
	if (UserManager::getInstance()->getCurrentUser())
	{
		auto scene = SurvivalMode::createScene();
	//	auto crossFade = TransitionCrossFade::create(1, scene);
		Director::getInstance()->replaceScene(scene);
		/*AudioEngine::stop(audioID);
		AudioEngine::uncache("game/sound/Zombotany.mp3");*/
	}
}

void MainMenuScene::albumIndex(Ref*){
	if (UserManager::getInstance()->getCurrentUser())
	{
		/*AudioEngine::stop(audioID);
		AudioEngine::uncache("game/sound/Zombotany.mp3");*/
		auto scene = AlbumIndexScene::createScene();
	//	auto crossFade = TransitionCrossFade::create(1, scene);
	//	Director::getInstance()->pushScene(scene);
		Director::getInstance()->replaceScene(scene);
		
	}
}

void MainMenuScene::openBag(Ref*){
	if (UserManager::getInstance()->getCurrentUser())
	{
		auto scene = BagScene::createScene();
		//auto crossFade = TransitionCrossFade::create(1, scene);
		//Director::getInstance()->pushScene(scene);
		Director::getInstance()->replaceScene(scene);
		/*AudioEngine::stop(audioID);
		AudioEngine::uncache("game/sound/Zombotany.mp3");*/
	}
}

void MainMenuScene::visitShop(Ref*){
	if (UserManager::getInstance()->getCurrentUser())
	{
		auto scene = ShopScene::createScene();
	//	auto crossFade = TransitionCrossFade::create(1, scene);
	//	Director::getInstance()->pushScene(scene);
		Director::getInstance()->replaceScene(scene);
		/*AudioEngine::stop(audioID);
		AudioEngine::uncache("game/sound/Zombotany.mp3");*/
	}
}

void MainMenuScene::gameset(Ref*)
{
	if (UserManager::getInstance()->getCurrentUser())
	{
		auto scene = GameMenuUI::createScene();
		this->addChild(scene,8);
	}
}
void MainMenuScene::userList(Ref*)
{
	userlist = UserListUI::create();
	auto visibleSize = Director::getInstance()->getVisibleSize();
	userlist->setAnchorPoint(Vec2::ZERO);
	userlist->setPosition(Vec2::ZERO);
	this->addChild(userlist, 5);
}

void MainMenuScene::update(float dt)
{
	AudioEngine::setVolume(audioID, VolumSet::getInstance()->getVolum());
	User* user = UserManager::getInstance()->getCurrentUser();
	if (user)
		wordOk->showWord(user->getName(), Vec2(125, 507));
}

void MainMenuScene::recordScore(Ref*)
{
	auto scene = UserHistoryScoreUI::createScene();
	this->addChild(scene,5);
}

MainMenuScene::~MainMenuScene()
{
	AudioEngine::stop(audioID);
	AudioEngine::uncache("game/sound/CrazyDave.mp3");
}