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
	if ((entityType > begin_derived_entity_type) && (entityType < end_derived_entity_type)){//����ȡ����һ����Ϸʵ�壨ֲ���ʬ��
		for (auto entityObj : derivedEntityArray){//����Ϸʵ����в��ҿ��õ�ʵ��
			if ((entityObj->getType() == entityType) && (entityObj->getValid() == false)){//��ǰʵ��Ϊͬ��������Ч�����ã���ʵ��
				entityObj->setPlant(plant);
				entityObj->createEntity();
				entityObj->setPos(Vec2(pos.x + 20,pos.y +  20));
				entityObj->setValid(true);
				entityObj->setPosition(Vec2(pos.x + 20, pos.y + 20));
				if (entityObj->getType() != DerivedEntityType::bambooshoot){
					entityObj->switchAction();
				}
				return entityObj;//ֱ�ӷ��ظ�ʵ��
			}
		}
		//��ǰ��Ϸʵ����в����ڿ��õ�ͬ����ʵ��,�򴴽�һ�����õ�ʵ�巵�أ�������Ž�ʵ�����
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
	for (auto entityObj : goldArray){//����Ϸʵ����в��ҿ��õ�ʵ��
		if (entityObj->getValid() == false){//��ǰʵ��Ϊͬ��������Ч�����ã���ʵ��
			entityObj->createEntity();
			entityObj->setPos(Vec2(pos.x + 20, pos.y + 20));
			entityObj->setValid(true);
			entityObj->setPosition(Vec2(pos.x + 20, pos.y + 20));
			entityObj->switchAction();
			return entityObj;//ֱ�ӷ��ظ�ʵ��
		}
	}
	//��ǰ��Ϸʵ����в����ڿ��õ�ͬ����ʵ��,�򴴽�һ�����õ�ʵ�巵�أ�������Ž�ʵ�����
	auto entityObj = new Gold(pos);
	entityObj->createEntity();
	entityObj->setValid(true);
	entityObj->setPosition(Vec2(pos.x + 20, pos.y + 20));
	entityObj->switchAction();
	goldArray.pushBack(entityObj);
	return entityObj;
}
