#ifndef __MAINMENU_SCENE_H__
#define __MAINMENU_SCENE_H__

#include "cocos2d.h"
#include "UserListUI.h"
#include "FlowWord.h"
#include "GameMenuUI.h"

USING_NS_CC;

//定义主菜单场景
//@hanjie 2016.12.28
class MainMenuScene : public cocos2d::Layer
{

public:
	cocos2d::Menu* main_menu;
    static cocos2d::Scene* createScene();

    virtual bool init();
	void adventureMode(Ref*);

	//lishi 2017.2.13
	void albumIndex(Ref*);
	
	//@hanjie 2017.2.14
	void survivalMode(Ref*);
	void openBag(Ref*);
	void visitShop(Ref*);
    
	//@suzhe 2017.2.15
	void userList(Ref*);
	void gameset(Ref*);
	void resetMainMenu(){ main_menu->setEnabled(true); }

	CREATE_FUNC(MainMenuScene);
	virtual void update(float dt);
	//su 2.25
	void recordScore(Ref*);

	~MainMenuScene();

private:
	UserListUI* userlist = NULL;
	FlowWord* wordOk;
	int audioID;
};

#endif  __MAINMENU_SCENE_H__
