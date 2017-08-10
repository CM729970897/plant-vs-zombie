#ifndef __START_SCENE_H__
#define __START_SCENE_H__

#include "cocos2d.h"
//定义初始化场景 @hanjie 2016.12.27
class StartScene : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
	void removeScrollGrass(cocos2d::Node* sprite);
	void replaceScene(float a);
	bool flag = false;
	CREATE_FUNC(StartScene);
};

#endif
