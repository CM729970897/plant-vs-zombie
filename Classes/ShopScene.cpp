#include "ShopScene.h"
#include "DataConfig.h"
#include "UserManager.h"
#include "FlowWord.h"
#include "GameEntityManager.h"
#include "AudioEngine.h"
#include "Volum.h"
#include "MainMenuScene.h"
#include "DataConfig.h"

USING_NS_CC;
using namespace experimental;

Scene* ShopScene::createScene()
{
	auto scene = Scene::create();
	auto layer = ShopScene::create();
	scene->addChild(layer);
	return scene;
}

bool ShopScene::init(){
	if (!Layer::init())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	itemList = DataConfig::getInstance()->getShopItemListFromConfig();
	word = FlowWord::create();
	word->getLableTTF()->setHorizontalAlignment(kCCTextAlignmentLeft);
	word->getLableTTF()->setAnchorPoint(Vec2::ANCHOR_TOP_LEFT);
	word->getLableTTF()->setColor(Color3B(0,0,255));
	this->addChild(word, 5);

	gold = FlowWord::create();
	this->addChild(gold, 5);
	gold->showWordint(UserManager::getInstance()->getUserGold(), Vec2(160, 10));

	auto sprite = Sprite::create("game/GameLayer/ShopBack.jpg");
	sprite->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	this->addChild(sprite, 0);

	auto gold_collector = Sprite::create("game/GameLayer/gold_collector.png");
	gold_collector->setPosition(Vec2(120, 25));
	this->addChild(gold_collector);

	auto closeItem = MenuItemImage::create(
		"game/interface/Almanac_CloseButton.png",
		"game/interface/Almanac_CloseButtonHighlight.png",
		CC_CALLBACK_1(ShopScene::menuCloseCallback, this));

	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width / 2 - 15,
		origin.y + closeItem->getContentSize().height / 2 + 8));

	auto torchwood = MenuItemImage::create("game/card/Torchwood.png", "game/card/Torchwood.png", CC_CALLBACK_1(ShopScene::display_Torchwood, this));
	torchwood->setScale(0.7f);
	torchwood->setPosition(Vec2(origin.x + 50, visibleSize.height / 2 + origin.y + 170));

	auto iceshroom = MenuItemImage::create("game/card/IceShroom.png", "game/card/IceShroom.png", CC_CALLBACK_1(ShopScene::display_Iceshroom, this));
	iceshroom->setScale(0.69f);
	iceshroom->setPosition(Vec2(origin.x + 105, visibleSize.height / 2 + origin.y + 170));

	auto shopCard = Sprite::create("game/interface/Almanac_PlantCard.png");
	shopCard->setScale(0.98f);
	shopCard->setPosition(Vec2(visibleSize.width / 2 + origin.x + 220, visibleSize.height / 2 - 22));
	this->addChild(shopCard, 0);

	auto buy = MenuItemImage::create("game/albumLayer/buy.png", "game/albumLayer/buy_down.png", CC_CALLBACK_1(ShopScene::buy, this));
	buy->setScale(1.2f);
	buy->setPosition(Vec2(617, 318));

	auto menu = Menu::create(closeItem, torchwood,iceshroom, buy, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);

	itemList = DataConfig::getInstance()->getShopItemListFromConfig();


	audioID = AudioEngine::play2d("game/sound/Cerebrawl.mp3",true,VolumSet::getInstance()->getVolum());

	return true;
}

void ShopScene::menuCloseCallback(Ref* pSender)
{
	auto scene = MainMenuScene::createScene();
	Director::getInstance()->replaceScene(scene);
	AudioEngine::stop(audioID);
	AudioEngine::uncache("game/sound/Cerebrawl.mp3");
}

void ShopScene::display_Torchwood(Ref*){
	auto item = this->getChildByTag(GameEntityType::iceshroom);
	if (item != NULL)item->removeFromParent();
	GameEntityManager::getInstance()->haveEntityForItem(this, GameEntityType::torchwood, Vec2(615, 420));
	showCurrentShopItem((int)GameEntityType::torchwood);
}

void ShopScene::display_Iceshroom(Ref*){
	auto item = this->getChildByTag(GameEntityType::torchwood);
	if (item != NULL)item->removeFromParent();
	GameEntityManager::getInstance()->haveEntityForItem(this, GameEntityType::iceshroom, Vec2(615, 420));
	showCurrentShopItem((int)GameEntityType::iceshroom);
}

void ShopScene::buy(Ref*){
	if (currentItem == NULL){
		return;
	}
	auto goldNum = UserManager::getInstance()->getUserGold();
	if (goldNum < currentItem->getCost()){//若用户当前的金币数少于商品售价，则购买失败
		FlowWord* fail = FlowWord::create();
		fail->getLableTTF()->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
		fail->showWord("购买失败!", Vec2(505,78));
		//fail->getLableTTF()->setHorizontalAlignment(TextHAlignment::CENTER);
		this->addChild(fail, 2);
		fail->runAction(Sequence::create(DelayTime::create(1.0f), CallFunc::create(fail, callfunc_selector(FlowWord::flowEnd)), NULL));
	}
	else{
		UserManager::getInstance()->updateUserGold(-1 * currentItem->getCost());
		UserManager::getInstance()->updateUserProperty(currentItem->getID(), currentItem->getNum());
		UserManager::getInstance()->updateUserInfo();

		FlowWord* success = FlowWord::create();
		success->getLableTTF()->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
		success->getLableTTF()->setColor(Color3B(0,255,0));
		success->showWord("购买成功!", Vec2(505, 78));
		success->getLableTTF()->setHorizontalAlignment(TextHAlignment::CENTER);
		this->addChild(success, 2);
		success->runAction(Sequence::create(DelayTime::create(1.0f), CallFunc::create(success, callfunc_selector(FlowWord::flowEnd)), NULL));

		gold->showWordint(UserManager::getInstance()->getUserGold(), Vec2(160, 10));
	}
}

// su 2.25  显示当前选中的商品信息
void ShopScene::showCurrentShopItem(int id)
{
	for (auto item : itemList){
		if (item->getID() == id){
			currentItem = item;
			break;
		}
	}
	std::string des = currentItem->getDescription();
	word->showWord(des, Vec2(505, 280));
}