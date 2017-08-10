#include "DerivedEntityManager.h"
#include "Sunshine.h"
#include "Peabullet.h"
#include "Gold.h"
#include "BambooShoot.h"

DerivedEntityManager* DerivedEntityManager::instance = NULL;

DerivedEntityManager* DerivedEntityManager::getInstance(){
	if (instance == NULL){
		instance = new DerivedEntityManager();
	}
	return instance;
}

DerivedEntity* DerivedEntityManager::haveEntity(int entityType, GameEntity* plant, Vec2 pos){
	if ((entityType > begin_derived_entity_type) && (entityType < end_derived_entity_type)){//所获取的是一个游戏实体（植物或僵尸）
		for (auto entityObj : derivedEntityArray){//在游戏实体池中查找可用的实体
			if ((entityObj->getType() == entityType) && (entityObj->getValid() == false)){//当前实体为同类型且无效（可用）的实体
				entityObj->setPlant(plant);
				entityObj->createEntity();
				entityObj->setPos(Vec2(pos.x + 20,pos.y +  20));
				entityObj->setValid(true);
				entityObj->setPosition(Vec2(pos.x + 20, pos.y + 20));
				if (entityObj->getType() != DerivedEntityType::bambooshoot){
					entityObj->switchAction();
				}
				return entityObj;//直接返回该实体
			}
		}
		//当前游戏实体池中不存在可用的同类型实体,则创建一个可用的实体返回，并将其放进实体池中
		auto entityObj = createEntity(entityType,plant,pos);
		entityObj->setValid(true);
		entityObj->setPosition(Vec2(pos.x + 20, pos.y + 20));
		if (entityObj->getType() != DerivedEntityType::bambooshoot){
			entityObj->switchAction();
		}
		derivedEntityArray.pushBack(entityObj);
		return entityObj;
	}
	return NULL;
}

DerivedEntity* DerivedEntityManager::createEntity(int entityType,GameEntity* plant,Vec2 pos){
	DerivedEntity* entity = nullptr;
	switch (entityType){
	case DerivedEntityType::peabullet:
	case DerivedEntityType::fire_peabullet:
		entity = new Peabullet(pos);
		break;
	case DerivedEntityType::sunshine:
		entity = new Sunshine(pos);
		break;
	case DerivedEntityType::bambooshoot:
		entity = new BambooShoot(pos);
		break;
	default:
		break;
	}
	if (entity != nullptr){
		entity->setPlant(plant);
		entity->createEntity();
		entityDataConfig->setDerivedEntityAttr(entity);
	}
	return entity;
}

DerivedEntity* DerivedEntityManager::haveGold(Vec2 pos){
	for (auto entityObj : goldArray){//在游戏实体池中查找可用的实体
		if (entityObj->getValid() == false){//当前实体为同类型且无效（可用）的实体
			entityObj->createEntity();
			entityObj->setPos(Vec2(pos.x + 20, pos.y + 20));
			entityObj->setValid(true);
			entityObj->setPosition(Vec2(pos.x + 20, pos.y + 20));
			entityObj->switchAction();
			return entityObj;//直接返回该实体
		}
	}
	//当前游戏实体池中不存在可用的同类型实体,则创建一个可用的实体返回，并将其放进实体池中
	auto entityObj = new Gold(pos);
	entityObj->createEntity();
	entityObj->setValid(true);
	entityObj->setPosition(Vec2(pos.x + 20, pos.y + 20));
	entityObj->switchAction();
	goldArray.pushBack(entityObj);
	return entityObj;
}
