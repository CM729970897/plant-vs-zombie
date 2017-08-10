#ifndef __GAME_MENU_UI_H__
#define __GAME_MENU_UI_H__

#include "cocos2d.h"
#include "EntityConst.h"
USING_NS_CC;

class GameMenuUI :public cocos2d::Layer{
private:
	Menu* op_menu;
	GameScene mode;
public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	void confirm(Ref*);
	void backMainMenu(Ref*);
	void restart(Ref*);
	void setMode(GameScene mode){ this->mode = mode; }

	CREATE_FUNC(GameMenuUI);
	virtual bool onTouchBegan(Touch* touch, Event* event);
	virtual void onTouchMoved(Touch* touch, Event* event);
	virtual void onTouchEnded(Touch* touch, Event* event);

};

#endif