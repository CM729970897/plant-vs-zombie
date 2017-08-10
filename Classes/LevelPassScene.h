#ifndef __LEVEL_PASS_SCENE_H__
#define __LEVEL_PASS_SCENE_H__

#include "cocos2d.h"
#include "SimpleAudioEngine.h"

//游戏通关场景
//@hanjie 2017.2.14

class LevelPassScene : public cocos2d::Layer{
private:
	void nextLevel(Ref*);
	void mainMenu(Ref*);
	int audioID;
public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	CREATE_FUNC(LevelPassScene);
};

#endif