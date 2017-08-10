#include "SimpleAudioEngine.h"
#include "UserHistoryScoreUI.h"
#include "UserManager.h"
#include "DataConfig.h"


USING_NS_CC;

Scene* UserHistoryScoreUI::createScene()
{
    auto scene = Scene::create();
	auto layer = UserHistoryScoreUI::create();
    scene->addChild(layer);
    return scene;
}

bool UserHistoryScoreUI::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    auto visibleSize = Director::getInstance()->getVisibleSize();
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(UserHistoryScoreUI::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(UserHistoryScoreUI::onTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(UserHistoryScoreUI::onTouchEnded, this);
	listener->setSwallowTouches(true);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	auto historyscore = Sprite::create("game/menuLayer/UserHistoryScore.png");
	historyscore->setPosition(Vec2(visibleSize.width/2,visibleSize.height/2));
	this->addChild(historyscore);
	auto close = MenuItemImage::create("game/commonlayer/IndexButton.png", "game/commonlayer/IndexButton_down.png", CC_CALLBACK_1(UserHistoryScoreUI::onClose, this));
	close->setScaleX(0.5f);
	close->setPosition(Vec2(540,180));
	auto menu = Menu::create(close,NULL);
	menu->setPosition(Point::ZERO);
	this->addChild(menu);
	

	scoreMap = UserManager::getInstance()->getHistoryPoint();
	//scoreMap = DataConfig::getInstance()->getUserHistoryScoreFromConfig(UserManager::getInstance()->getCurrentUser()->getName());

	cellNum = scoreMap.size();

	TableView* tableView = TableView::create(this, CCSizeMake(360, 200));
	tableView->setDirection(ScrollView::Direction::VERTICAL);
	tableView->setPosition(Vec2(240,200));
	tableView->setDelegate(this);
	tableView->setVerticalFillOrder(TableView::VerticalFillOrder::TOP_DOWN);
	this->addChild(tableView);
	tableView->reloadData();

    return true;
}

void UserHistoryScoreUI::onClose(Ref*)
{
	this->removeFromParent();
}


void UserHistoryScoreUI::tableCellTouched(TableView* table, TableViewCell* cell)
{

}

Size UserHistoryScoreUI::tableCellSizeForIndex(TableView* table, ssize_t idx)
{
	return CCSizeMake(320, 25);
}

TableViewCell* UserHistoryScoreUI::tableCellAtIndex(TableView* table, ssize_t idx)
{
	CCString* string = CCString::createWithFormat("%d", idx);
	TableViewCell* cell = table->dequeueCell();
	if (!cell)
	{
		cell = new TableViewCell();
		cell->autorelease();
	}
	cell->removeAllChildrenWithCleanup(true);

	//auto sprite = Sprite::create("game/menuLayer/userbg.png");
	//sprite->setAnchorPoint(Vec2::ZERO);
	//sprite->setPosition(Vec2(0, 0));
	//sprite->setTag(12);
	//cell->addChild(sprite);

	LabelTTF* label = LabelTTF::create(getScoreAtIndex(scoreMap, idx), "Arial", 15);
	label->setColor(Color3B(255,0,0));
	label->setPosition(Vec2::ZERO);
	label->setAnchorPoint(Vec2::ZERO);
	cell->addChild(label,6);

	return cell;
}

ssize_t UserHistoryScoreUI::numberOfCellsInTableView(TableView* table)
{
	return cellNum;

}

void UserHistoryScoreUI::tableCellHighlight(TableView* table, TableViewCell* cell)
{
	//Texture2D *aTexture = TextureCache::sharedTextureCache()->addImage("game/menuLayer/userbg_selected.png");
	//Sprite *pSprite = (Sprite *)cell->getChildByTag(12);
	//pSprite->setTexture(aTexture);
}
void UserHistoryScoreUI::tableCellUnhighlight(TableView* table, TableViewCell* cell)
{
	//Texture2D *aTexture = TextureCache::sharedTextureCache()->addImage("game/menuLayer/userbg.png");
	//Sprite *pSprite = (Sprite *)cell->getChildByTag(12);
	//pSprite->setTexture(aTexture);
}

std::string UserHistoryScoreUI::getScoreAtIndex(std::map<std::string, unsigned int>umap, ssize_t idx)
{
	// su 2.26  пРапее╥е
	std::map<std::string,unsigned int>::iterator iter = umap.end();
	iter--;
	for (ssize_t x = 0; x < idx; x++)
	{
		iter--;
	}

	CCString* s = CCString::createWithFormat("%d", idx+1);
	CCString* sec = CCString::createWithFormat("%d", iter->second);

	std::string text = s->_string+":  " + iter->first + "            "+sec->_string;
	return text;

}

bool UserHistoryScoreUI::onTouchBegan(Touch* touch, Event* event)
{
//	p1 = touch->getLocation();
	return true;
}
void UserHistoryScoreUI::onTouchMoved(Touch* touch, Event* event)
{

	/*p2 = touch->getLocation();
	Vec2 dp = p2 - p1;
	Vec2 pos;
	pos = getPosition() + dp;
	if (pos.x >=200)
	pos.x = 200;
	else if (pos.x <= -200 )
	pos.x = -200 ;
	if (pos.y >= 65)
	pos.y = 65;
	else if (pos.y <= -65)
	pos.y = -65;
	setPosition(pos);
	p1 = p2;*/
}

void UserHistoryScoreUI::onTouchEnded(Touch* touch, Event* event)
{

}
