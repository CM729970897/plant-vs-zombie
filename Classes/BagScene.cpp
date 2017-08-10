#include "BagScene.h"
#include "UserManager.h"
#include "GameEntity.h"
#include "GameEntityManager.h"
#include "MainMenuScene.h"
#include "AudioEngine.h"
#include "Volum.h"


USING_NS_CC;
using namespace experimental;

Scene* BagScene::createScene()
{
	auto scene = Scene::create();
	auto layer = BagScene::create();
	scene->addChild(layer);
	return scene;
}

bool BagScene::init(){
	if (!Layer::init())
	{
		return false;
	}
	propMap = UserManager::getInstance()->getPropList();

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	word = FlowWord::create();
	this->addChild(word,5);

	auto closeItem = MenuItemImage::create(
		"game/interface/Almanac_CloseButton.png",
		"game/interface/Almanac_CloseButtonHighlight.png",
		CC_CALLBACK_1(BagScene::menuCloseCallback, this));

	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width / 2 - 15,
		origin.y + closeItem->getContentSize().height / 2 + 8));

	auto sprite = Sprite::create("game/GameLayer/BagBack.jpg");
	sprite->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	this->addChild(sprite, 0);
	
	auto torchwood = MenuItemImage::create("game/card/Torchwood.png", "game/card/Torchwood.png", CC_CALLBACK_1(BagScene::display_Torchwood, this));
	torchwood->setScale(0.7f);
	torchwood->setPosition(Vec2(origin.x + 50, visibleSize.height / 2 + origin.y + 170));

	auto iceshroom = MenuItemImage::create("game/card/IceShroom.png", "game/card/IceShroom.png", CC_CALLBACK_1(BagScene::display_Iceshroom, this));
	iceshroom->setScale(0.7f);
	iceshroom->setPosition(Vec2(origin.x + 100, visibleSize.height / 2 + origin.y + 170));

	auto shopCard = Sprite::create("game/interface/PropertyNum.png");
	shopCard->setScale(0.98f);
	shopCard->setPosition(Vec2(visibleSize.width / 2 + origin.x + 220, visibleSize.height / 2 - 22));
	this->addChild(shopCard, 0);

	auto menu = Menu::create(closeItem, torchwood,iceshroom, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);

	audioID = AudioEngine::play2d("game/sound/ZenGarden.mp3", true, VolumSet::getInstance()->getVolum());
	return true;
}

void BagScene::menuCloseCallback(Ref* pSender)
{
	auto scene = MainMenuScene::createScene();
	//auto crossFade = TransitionCrossFade::create(1, scene);
	//Director::getInstance()->popScene();
	Director::getInstance()->replaceScene(scene);
	AudioEngine::stop(audioID);
	AudioEngine::uncache("game/sound/ZenGarden.mp3");
}

void BagScene::display_Torchwood(Ref*){
	auto item = this->getChildByTag(GameEntityType::iceshroom);
	if (item != NULL)item->removeFromParent();
	GameEntityManager::getInstance()->haveEntityForItem(this, GameEntityType::torchwood, Vec2(615, 420));
	word->showWordint(propMap[GameEntityType::torchwood],Vec2(585,210));	
}

void BagScene::display_Iceshroom(Ref*){
	auto item = this->getChildByTag(GameEntityType::torchwood);
	if (item != NULL)item->removeFromParent();
	GameEntityManager::getInstance()->haveEntityForItem(this, GameEntityType::iceshroom, Vec2(615, 420));
	word->showWordint(propMap[GameEntityType::iceshroom], Vec2(585, 210));
}
