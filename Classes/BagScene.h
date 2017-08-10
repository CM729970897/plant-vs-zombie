#ifndef __BAG_SCENE_H__
#define __BAG_SCENE_H__
#include "cocos2d.h"
#include "FlowWord.h"
#include "EntityConst.h"
#include "SimpleAudioEngine.h"


//±³°ü³¡¾°
//tangsai 2017.2.14
class BagScene :public cocos2d::Layer{
public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	void menuCloseCallback(cocos2d::Ref* pSender);
	void display_Torchwood(Ref*);

	//@hanjie 2017.2.26
	void display_Iceshroom(Ref*);

	CREATE_FUNC(BagScene);
private:
	FlowWord* word;
	std::map<GameEntityType, int>propMap;
	int audioID;
};

#endif