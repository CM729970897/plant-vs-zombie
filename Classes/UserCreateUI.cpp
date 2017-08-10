#include"UserCreateUI.h"
#include "UserManager.h"
#include"cocos2d.h"

USING_NS_CC;

Scene* UserCreateUI::createScene()
{
	auto scene = Scene::create();
	auto layer = UserCreateUI::create();
	scene->addChild(layer);
	return scene;
}

bool UserCreateUI::init()
{
	if (!Layer::init())
		return false;

	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(UserCreateUI::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(UserCreateUI::onTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(UserCreateUI::onTouchEnded, this);
	listener->setSwallowTouches(true);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto sprite = Sprite::create("game/menuLayer/user_createbg.png");
	sprite->setPosition(Vec2(visibleSize.width / 2-180, visibleSize.height / 2-10));
	this->addChild(sprite);
	auto ok = MenuItemImage::create("game/menuLayer/ok.png", "game/menuLayer/ok_selected.png", CC_CALLBACK_1(UserCreateUI::onOk, this));
	ok->setPosition(Vec2(166, 253));
	ok->setScaleX(0.5f);
	auto cancel = MenuItemImage::create("game/menuLayer/cancel.png", "game/menuLayer/cancel_selected.png", CC_CALLBACK_1(UserCreateUI::onCancel, this));
	cancel->setPosition(Vec2(275, 253));
	cancel->setScaleX(0.5f);

	auto menu = Menu::create(ok, cancel, NULL);
	menu->setPosition(Point::ZERO);
	this->addChild(menu);

	auto pEditBox_name = EditBox::create(CCSizeMake(200, 36), Scale9Sprite::create("game/menuLayer/inputEdit.png"));
	pEditBox_name->setPosition(ccp(visibleSize.width / 2-180, visibleSize.height * 3 / 4-135));
	pEditBox_name->setFontColor(Color3B(0, 0, 0));//设置字体颜色    
	pEditBox_name->setPlaceHolder("please create a user:");//设置预置文本    
	pEditBox_name->setFontSize(18);
	pEditBox_name->setMaxLength(14);//设置最大长度    
	pEditBox_name->setInputMode(cocos2d::ui::EditBox::InputMode::SINGLE_LINE);//可以输入任何，但是不包括换行   
	pEditBox_name->setInputFlag(cocos2d::ui::EditBox::InputFlag::INITIAL_CAPS_WORD);//设置输入标志位    
	pEditBox_name->setReturnType(cocos2d::ui::EditBox::KeyboardReturnType::DONE);//设置返回类型    
	pEditBox_name->setDelegate(this);//当前类继承CCEditBoxDelegate类    
	pEditBox_name->setTag(101);
	this->addChild(pEditBox_name);


	return true;
}

void UserCreateUI::editBoxEditingDidBegin(EditBox *editBox)
{
	CCLOG("start edit");
}
void UserCreateUI::editBoxEditingDidEnd(EditBox *editBox)
{
	CCLOG("end edit");
}
void UserCreateUI::editBoxReturn(EditBox *editBox)
{
	CCLOG("editbox return");
}
void UserCreateUI::editBoxTextChanged(EditBox *editBox, const std::string &text)
{
	auto editbox = (EditBox*)editBox;
	CCLOG("EditBox_name changed");
	m_name = text;
	
}

void UserCreateUI::onOk(Ref*)
{
	UserManager* usermanager = UserManager::getInstance();
	if(usermanager->createUser(m_name))
		this->removeFromParent();
	else
	{

		FlowWord* fail = FlowWord::create();
		fail->getLableTTF()->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
		fail->showWord("不能重复创建", Vec2(310, 328));
		this->addChild(fail, 3);
		fail->runAction(Sequence::create(DelayTime::create(1.0f), CallFunc::create(fail, callfunc_selector(FlowWord::flowEnd)), NULL));
	}
}

void UserCreateUI::onCancel(Ref*)
{
	this->removeFromParent();
}

bool UserCreateUI::onTouchBegan(Touch* touch, Event* event)
{
	return true;
}
void UserCreateUI::onTouchMoved(Touch* touch, Event* event)
{

}

void UserCreateUI::onTouchEnded(Touch* touch, Event* event)
{

}

