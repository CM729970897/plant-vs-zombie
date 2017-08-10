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

//��Ϸð��ģʽ���� @hanjie 2017.1.12
class AdventureMode :public cocos2d::Layer{
private:
	unsigned short currentLevel;//��Ϸ��ǰ�ؿ�
	GameEntityManager* gameEntityManager;//��Ϸʵ�����
	DerivedEntityManager* derivedEntityManager;//����ʵ�����
	GridManager* gridManager;//�����������
	EntityInteractManager* entityInteractManager;//��ײ������
	
	void constEntitiesInteract(float dt);//�־���ʵ�彻�������ֽ�ʬ���㶹���֣����տ������ǽ�����컨��
	void collideDetect(float dt);//ʵ����ײ���
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
	bool loadLevel(unsigned short level);//���ݵ�ǰ�����Ϣ������Ϸ�ؿ�
	
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