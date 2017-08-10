#ifndef __ADVENTURE_SCENE_H__
#define __ADVENTURE_SCENE_H__
#include "cocos2d.h"
#include "EntityConst.h"
#include "GameEntityManager.h"
#include "GameEntity.h"
#include "DerivedEntityManager.h"
#include "DerivedEntity.h"
#include "GridManager.h"
#include "EntityInteractManager.h"
#include "FlowWord.h"

//游戏冒险模式场景 @hanjie 2017.1.12
class AdventureMode :public cocos2d::Layer{
private:
	unsigned short currentLevel;//游戏当前关卡
	GameEntityManager* gameEntityManager;//游戏实体管理
	DerivedEntityManager* derivedEntityManager;//派生实体管理
	GridManager* gridManager;//网格坐标管理
	EntityInteractManager* entityInteractManager;//碰撞检测管理
	
	void constEntitiesInteract(float dt);//持久性实体交互（各种僵尸，豌豆射手，向日葵，坚果墙，大嘴花）
	void collideDetect(float dt);//实体碰撞检测
	bool onTouchBegan(Touch* a, Event* b);
	void onTouchMoved(Touch* a, Event* b);
    void onTouchEnded(Touch* a, Event* b);

	//@hanjie 2017.2.4
	void gamePass();
	void gameFailure();
	
	//suzhe 2017.2.14
	void menuCloseCallback(cocos2d::Ref* pSender);
	virtual void update(float dt);
	void offToOn(Node* p);
	ONOFF prop[7];
	int currentScore;
	bool propStart;
	Sprite* spriteOne;
	int x1;
	FlowWord* sun;
	FlowWord* gold;
	int audioID;
	Menu* menu;

	Sprite* shovelSprite;
	bool isShovel = false;

public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	bool loadLevel(unsigned short level);//根据当前玩家信息加载游戏关卡
	
	//suzhe 2017.2.14
	void creatProp(int a[], int count);
	CREATE_FUNC(AdventureMode);
	
	//suzhe 2.25
	~AdventureMode();

	//hanjie 2017.2.27
private:
	FlowWord* torchwoodNum;
	FlowWord* iceshroomNum;
	int torchleft;
	int iceleft;
};
#endif