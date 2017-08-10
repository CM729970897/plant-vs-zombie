#ifndef __DERIVED_ENTITY_MANAGER_H__
#define __DERIVED_ENTITY_MANAGER_H__

#include "cocos2d.h"
#include "EntityConst.h"
#include "DerivedEntity.h"
#include "DataConfig.h"

USING_NS_CC;
//派生实体管理类，用于派生实体的统一化管理，包括创建，运动、回收等
//@ hanjie 2017.1.8
//改为单例模式 @hanjie 2017.1.12
class DerivedEntityManager{
private:
	DataConfig* entityDataConfig;
	static DerivedEntityManager* instance;
	DerivedEntityManager(){ entityDataConfig = DataConfig::getInstance(); }
	~DerivedEntityManager(){}
	DerivedEntity* createEntity(int entityType,GameEntity* plant, Vec2 pos);
public:
	Vector<DerivedEntity*>derivedEntityArray;//派生实体池
	static DerivedEntityManager* getInstance();
	DerivedEntity* haveEntity(int entityType,GameEntity* plant,Vec2 pos);

	//@hanjie 2017.2.21 随机掉落金币
	Vector<DerivedEntity*>goldArray;//金币数组
	DerivedEntity* haveGold(Vec2 pos);//获取一个金币

};

#endif