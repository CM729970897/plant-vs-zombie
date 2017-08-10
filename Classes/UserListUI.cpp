#include"UserListUI.h"
#include"UserCreateUI.h"
#include"cocos2d.h"
#include"MainMenuScene.h"
#include "UserManager.h"

USING_NS_CC;

Scene* UserListUI::createScene()
{
	auto scene = Scene::create();
	auto layer = UserListUI::create();
	scene->addChild(layer);
	return scene;
}

bool UserListUI::init()
{
	if (!Layer::init())
		return false;

	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(UserListUI::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(UserListUI::onTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(UserListUI::onTouchEnded, this);
	listener->setSwallowTouches(true);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	visibleSize = Director::getInstance()->getVisibleSize();
	auto sprite = Sprite::create("game/menuLayer/userlist.png");
	sprite->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	sprite->setScaleY(0.85f);
	this->addChild(sprite);

	auto ok = MenuItemImage::create("game/menuLayer/ok.png", "game/menuLayer/ok_selected.png", CC_CALLBACK_1(UserListUI::onOk, this));
	ok->setAnchorPoint(Vec2::ZERO);
	ok->setPosition(Vec2(272, 185));
	ok->setScale(0.7f);
	auto cancel = MenuItemImage::create("game/menuLayer/cancel.png", "game/menuLayer/cancel_selected.png", CC_CALLBACK_1(UserListUI::onCancel, this));
	cancel->setAnchorPoint(Vec2::ZERO);
	cancel->setPosition(Vec2(252 + 170, 185));
	cancel->setScale(0.7f);
	auto create = MenuItemImage::create("game/menuLayer/create.png", "game/menuLayer/create_selected.png", CC_CALLBACK_1(UserListUI::onCreate, this));
	create->setAnchorPoint(Vec2::ZERO);
	create->setPosition(Vec2(272, 145));
	create->setScale(0.7f);

	auto remove = MenuItemImage::create("game/menuLayer/delete.png", "game/menuLayer/delete_selected.png", CC_CALLBACK_1(UserListUI::onDelete, this));
	remove->setAnchorPoint(Vec2::ZERO);
	remove->setPosition(Vec2(252 + 170, 145));
	remove->setScale(0.7f);

	auto menu = Menu::create(ok, cancel, create, remove, NULL);
	menu->setPosition(Point::ZERO);
	this->addChild(menu);

	usermanager = UserManager::getInstance();
	contentList = usermanager->getUserList();
	cellNum = contentList.size();

	TableView* tableView = TableView::create(this, CCSizeMake(200, 200));
	tableView->setDirection(ScrollView::Direction::VERTICAL);
	tableView->setPosition(Vec2(visibleSize.width / 3+40, visibleSize.height / 3+25));
	tableView->setDelegate(this);
	tableView->setVerticalFillOrder(TableView::VerticalFillOrder::TOP_DOWN);
	this->addChild(tableView);
	tableView->reloadData();

	word = FlowWord::create();
	word->getLableTTF()->setFontSize(15);
	word->getLableTTF()->setAnchorPoint(Vec2::ANCHOR_TOP_LEFT);
	this->addChild(word, 5);
	return true;
}

void UserListUI::tableCellTouched(TableView* table, TableViewCell* cell)
{
	tableView = table;
	index = cell->getIdx();
	int size = contentList.size();
	if (0 <= index&&index < size)
	{
		std::string s = getUserAtIndex(contentList,index)->getName();
		word->showWord(s, Vec2(236, 442));
	}

}

Size UserListUI::tableCellSizeForIndex(TableView* table, ssize_t idx)
{
	return CCSizeMake(200, 40);
}

TableViewCell* UserListUI::tableCellAtIndex(TableView* table, ssize_t idx)
{
	CCString* string = CCString::createWithFormat("%d", idx);
	TableViewCell* cell = table->dequeueCell();
	if (!cell)
	{
		cell = new TableViewCell();
		cell->autorelease();
	}
	cell->removeAllChildrenWithCleanup(true);

	auto sprite = Sprite::create("game/menuLayer/userbg.png");
	sprite->setAnchorPoint(Vec2::ZERO);
	sprite->setPosition(Vec2(0, 0));
	sprite->setTag(12);
	cell->addChild(sprite);

	int size = contentList.size();
	if (0<=idx&&idx<size)
	{

		LabelTTF* label = LabelTTF::create(getUserAtIndex(contentList, idx)->getName(), "Arial", 15);
		label->setPosition(Vec2(80,8));
		label->setAnchorPoint(Vec2::ZERO);
		cell->addChild(label);
	}
	return cell;
}

ssize_t UserListUI::numberOfCellsInTableView(TableView* table)
{
	return cellNum;
}

void UserListUI::tableCellHighlight(TableView* table, TableViewCell* cell)
{
	Texture2D *aTexture = TextureCache::sharedTextureCache()->addImage("game/menuLayer/userbg_selected.png");
	Sprite *pSprite = (Sprite *)cell->getChildByTag(12);
	pSprite->setTexture(aTexture);
}
void UserListUI::tableCellUnhighlight(TableView* table, TableViewCell* cell)
{
	Texture2D *aTexture = TextureCache::sharedTextureCache()->addImage("game/menuLayer/userbg.png");
	Sprite *pSprite = (Sprite *)cell->getChildByTag(12);
	pSprite->setTexture(aTexture);
}


void UserListUI::onOk(Ref*)
{
	if (index != -1)
	{
		std::string s = getUserAtIndex(contentList, index)->getName();
		usermanager->switchUser(s);
		this->removeFromParent();
	}
}

void UserListUI::onCancel(Ref*)
{
	this->removeFromParent();
}

void UserListUI::onCreate(Ref*)
{
	if (UserManager::getInstance()->getUserList().size() < 6)
	{
		auto Scene = dynamic_cast<MainMenuScene*>(Director::getInstance()->getRunningScene()->getChildByTag(333));
		auto usercreate = UserCreateUI::create();
		usercreate->setAnchorPoint(Vec2::ZERO);
		usercreate->setPosition(Vec2(150,0));
		Scene->addChild(usercreate, 5);
		this->removeFromParent();
	}
	else
	{
		FlowWord* fail = FlowWord::create();
		fail->getLableTTF()->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
		fail->showWord("最多只允许创建六个用户", Vec2(310, 328));
		this->addChild(fail, 3);
		fail->runAction(Sequence::create(DelayTime::create(1.0f), CallFunc::create(fail, callfunc_selector(FlowWord::flowEnd)), NULL));
	}
	
}

void UserListUI::onDelete(Ref*)
{
	int size = contentList.size(); 
	if (0 <= index&&index <= size)
	{

		User* user = getUserAtIndex(contentList, index);
		if (usermanager->deleteUser(user->getName()))
		{
			contentList.remove(user);
			cellNum = contentList.size();
			tableView->reloadData();
			if (0 < index&&index < size)
				--index;
		}
		word->showWord(getUserAtIndex(contentList, index)->getName(), Vec2(236, 442));
	}
}

User* UserListUI::getUserAtIndex(std::list<User*>ulist,ssize_t idx)
{
	std::list<User*>::iterator iter = ulist.begin();
	for (ssize_t x = 0; x < idx; x++)
	{
		iter++;
	}
	return *iter;

}

bool UserListUI::onTouchBegan(Touch* touch, Event* event)
{
	p1 = touch->getLocation();
	return true;
}
void UserListUI::onTouchMoved(Touch* touch, Event* event)
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

void UserListUI::onTouchEnded(Touch* touch, Event* event)
{
}
