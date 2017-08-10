#ifndef __USERCREATE_UI_H__
#define __USERCREATE_UI_H__
#include"cocos2d.h"
#include"cocos-ext.h"
#include"FlowWord.h"


USING_NS_CC;
USING_NS_CC_EXT;

class UserCreateUI :public cocos2d::Layer,public EditBoxDelegate
{
public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	void onOk(Ref*);
	void onCancel(Ref*);
	virtual bool onTouchBegan(Touch* touch, Event* event);
	virtual void onTouchMoved(Touch* touch, Event* event);
	virtual void onTouchEnded(Touch* touch, Event* event);
	CREATE_FUNC(UserCreateUI);
	
	virtual void editBoxEditingDidBegin(cocos2d::extension::EditBox* editBox);
	virtual void editBoxEditingDidEnd(cocos2d::extension::EditBox* editBox);
	virtual void editBoxTextChanged(cocos2d::extension::EditBox* editBox, const std::string &text);
	virtual void editBoxReturn(cocos2d::extension::EditBox *editBox);

private:
	std::string m_name;
};
#endif __USERCREATE_UI_H__