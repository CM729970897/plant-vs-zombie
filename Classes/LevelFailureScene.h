#ifndef __LEVEL_FAILURE_SCENE_H__
#define __LEVEL_FAILURE_SCENE_H__

#include "cocos2d.h"

//”Œœ∑ ß∞‹≥°æ∞
//@hanjie 2017.2.14

class LevelFailureScene : public cocos2d::Layer{
private:
	void tryAgain(Ref*);
	void mainMenu(Ref*);
	int audioID;
public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	CREATE_FUNC(LevelFailureScene);
};

#endif