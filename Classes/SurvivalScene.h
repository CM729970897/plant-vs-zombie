#ifndef __SURVIVAL_SCENE_H__
#define __SURVIVAL_SCENE_H__

#include "cocos2d.h"
#include "EntityConst.h"
#include "GameEntityManager.h"
#include "GameEntity.h"
#include "DerivedEntityManager.h"
#include "DerivedEntity.h"
#include "GridManager.h"
#include "EntityInteractManager.h"
#include "FlowWord.h"
#include "SimpleAudioEngine.h"
using namespace std;
USING_NS_CC;


class SurvivalMode : public cocos2d::Layer
{
private:
	Size visibleSize;
	Vec2 origin;
	ONOFF prop[7];
	bool propStart;
	Sprite* spriteOne;
	int x1;
	FlowWord* sun;
	FlowWord* gold;
	int audioID;
	Menu* menu;
	//2.25 
	Sprite* shovelSprite;
	bool isShovel = false;
	// su 2.26
	FlowWord *pword;
	Sprite* pointBg;

	GameEntityManager* gameEntityManager;//��Ϸʵ�����
	DerivedEntityManager* derivedEntityManager;//����ʵ�����
	GridManager* gridManager;//�����������
	EntityInteractManager* entityInteractManager;//��ײ������

	void gamePass();
	void gameFailure();
	void constEntitiesInteract(float dt);//�־���ʵ�彻�������ֽ�ʬ���㶹���֣����տ������ǽ�����컨��
	void collideDetect(float dt);//ʵ����ײ���

public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	CREATE_FUNC(SurvivalMode);
	void attack(float a);
	void menuCloseCallback(cocos2d::Ref* pSender);

	bool onTouchBegan(Touch* touch,Event* event);
	void onTouchMoved(Touch* touch, Event* event);
	void onTouchEnded(Touch* touch, Event* event);


	virtual void update(float ft);
	void creatProp(int a[], int count);
	void offToOn(Node* p);

	~SurvivalMode();

	//hanjie 2017.2.27
private:
	FlowWord* torchwoodNum;
	FlowWord* iceshroomNum;
};

#endif // __SURVIVAL_GAMESCENE_H__
