#ifndef __DERIVED_ENTITY_MANAGER_H__
#define __DERIVED_ENTITY_MANAGER_H__

#include "cocos2d.h"
#include "EntityConst.h"
#include "DerivedEntity.h"
#include "DataConfig.h"

USING_NS_CC;
//����ʵ������࣬��������ʵ���ͳһ�����������������˶������յ�
//@ hanjie 2017.1.8
//��Ϊ����ģʽ @hanjie 2017.1.12
class DerivedEntityManager{
private:
	DataConfig* entityDataConfig;
	static DerivedEntityManager* instance;
	DerivedEntityManager(){ entityDataConfig = DataConfig::getInstance(); }
	~DerivedEntityManager(){}
	DerivedEntity* createEntity(int entityType,GameEntity* plant, Vec2 pos);
public:
	Vector<DerivedEntity*>derivedEntityArray;//����ʵ���
	static DerivedEntityManager* getInstance();
	DerivedEntity* haveEntity(int entityType,GameEntity* plant,Vec2 pos);

	//@hanjie 2017.2.21 ���������
	Vector<DerivedEntity*>goldArray;//�������
	DerivedEntity* haveGold(Vec2 pos);//��ȡһ�����

};

#endif