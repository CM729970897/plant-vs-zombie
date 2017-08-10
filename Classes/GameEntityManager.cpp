#include "GameEntityManager.h"
#include "CherryBomb.h"
#include "Jalapeno.h"
#include "Peashooter.h"
#include "Sunflower.h"
#include "WallNut.h"
#include "BucketheadZombie.h"
#include "ConeheadZombie.h"
#include "FlagZombie.h"
#include "Zombie.h"
#include "SpecialEffect.h"
#include "Torchwood.h"
#include "IceShroom.h"
#include "FlashBamboo.h"

USING_NS_CC;

GameEntityManager* GameEntityManager::instance = NULL;

GameEntityManager* GameEntityManager::getInstance(){
	if (instance == NULL){
		instance = new GameEntityManager();
	}
	return instance;
}

GameEntity* GameEntityManager::haveEntity(GameEntityType entityType, Vec2 pos){
	if ((entityType > GameEntityType::begin_plant) && (entityType < GameEntityType::end_zombie)){//所获取的是一个游戏实体（植物或僵尸）
		for (auto entityObj : gameEntityArray){//在游戏实体池中查找可用的实体
			if ((entityObj->getType() == entityType) && (entityObj->getValid() == GameEntityStatus::invalid)){//当前实体为同类型且无效（可用）的实体
				entityObj->setPos(pos);
				entityObj->setValid(GameEntityStatus::valid);
				entityObj->setPosition(pos);
				if (entityType > GameEntityType::begin_zombie && entityType < GameEntityType::end_zombie){
					entityObj->runAction(entityObj->haveAction());
				}
				return entityObj;//直接返回该实体
			}
		}
		//当前游戏实体池中不存在可用的同类型实体,则创建一个可用的实体返回，并将其放进实体池中
		auto entityObj = createEntity(entityType, pos);
		entityObj->setValid(GameEntityStatus::valid);
		if (entityType > GameEntityType::begin_zombie && entityType < GameEntityType::end_zombie){
			entityObj->runAction(entityObj->haveAction());
		}
		entityObj->setPosition(pos);
		gameEntityArray.pushBack(entityObj);
		return entityObj;
	}
	return NULL;
}

GameEntity* GameEntityManager::createEntity(GameEntityType entityType, Vec2 pos){
	GameEntity* entity = nullptr;
	switch (entityType){
	case GameEntityType::sunflower:
		entity = new Sunflower(pos);
		break;
	case GameEntityType::peashooter:
		entity = new Peashooter(pos);
		break;
	case GameEntityType::cherrybomb:
		entity = new CherryBomb(pos);
		break;
	case GameEntityType::jalapeno:
		entity = new Jalapeno(pos);
		break;
	case GameEntityType::wallnut:
		entity = new WallNut(pos);
		break;
	case GameEntityType::flashbamboo:
		entity = new FlashBamboo(pos);
		break;
	case GameEntityType::zombie:
		entity = new Zombie(pos);
		break;
	case GameEntityType::buckethead_zombie:
		entity = new BucketheadZombie(pos);
		break;
	case GameEntityType::flag_zombie:
		entity = new FlagZombie(pos);
		break;
	case GameEntityType::conehead_zombie:
		entity = new ConeheadZombie(pos);
		break;
	case GameEntityType::torchwood:
		entity = new Torchwood(pos);
		break;
	case GameEntityType::iceshroom:
		entity = new IceShroom(pos);
		break;
	default:
		break;
	}
	if (entity != nullptr){
		dataConfig->setGameEntityAttr(entity);
		entity->createEntity();
	}
	return entity;
}

int GameEntityManager::countValidNobuffPeashooter(){
	int result = 0;
	for (auto plantObj : gameEntityArray){
		if (!((plantObj->getType() == GameEntityType::peashooter) && (plantObj->getValid() == GameEntityStatus::valid) && (plantObj->getBuffType() == BuffType::nobuff))){
			continue;
		}
		result++;
	}
	return result;
}

void GameEntityManager::applyFireBuffToPeashooter(Layer* layer, ValueVector index, BuffType type){
	Vector<GameEntity*>buffList;
	for (auto indexObj : index){
		int num = indexObj.asInt();
		int counter = 0;
		for (auto plantObj : gameEntityArray){
			if (!((plantObj->getType() == GameEntityType::peashooter) && (plantObj->getValid() == GameEntityStatus::valid) && (plantObj->getBuffType() == BuffType::nobuff))){
				continue;
			}
			counter++;
			if (counter == num){//当前实体为索引对应的实体，
				buffList.pushBack(plantObj);
				break;
			}
		}
	}
	if (buffList.size() != 3){
		buffList.clear();
		return;
	}
	for (auto buffplant : buffList){
		SpecialEffect * effect = new SpecialEffect();
		effect->fireBullet();
		layer->addChild(effect);
		auto torchwood = layer->getChildByTag(GameEntityType::torchwood);
		effect->setPosition(Vec2(torchwood->getPosition().x - 20, torchwood->getPosition().y + 20));
		effect->runAction(Sequence::create(MoveTo::create(2.0f, buffplant->getPosition()), CallFunc::create(buffplant, callfunc_selector(GameEntity::fireBuffEffect)), CallFunc::create(effect, callfunc_selector(SpecialEffect::remove)), NULL));
	}
}

GameEntity* GameEntityManager::haveEntityForAlbum(GameEntityType entityType, Vec2 pos){
	for (auto entityObj : gameEntityArray){
		if (entityObj->getValid() == GameEntityStatus::album){//若存在已经处于图鉴状态的实体，则对实体进行重置，以确保整个实体池中只存在一个处于图鉴状态的实体
			resetAlbumEntity();
			break;
		}
	}
	if ((entityType > GameEntityType::begin_plant) && (entityType < GameEntityType::end_zombie)){//所获取的是一个游戏实体（植物或僵尸）
		for (auto entityObj : gameEntityArray){//在游戏实体池中查找可用的实体
			if ((entityObj->getType() == entityType) && (entityObj->getValid() == GameEntityStatus::invalid)){//当前实体为同类型且无效（可用）的实体
				entityObj->setPos(pos);
				entityObj->setValid(GameEntityStatus::album);//将其设置为图鉴状态，则不再参与实体交互
				entityObj->setPosition(pos);
				return entityObj;//直接返回该实体
			}
		}
		//当前游戏实体池中不存在可用的同类型实体,则创建一个可用的实体返回，并将其放进实体池中
		auto entityObj = createEntity(entityType, pos);
		entityObj->setValid(GameEntityStatus::album);
		entityObj->setPosition(pos);
		gameEntityArray.pushBack(entityObj);
		return entityObj;
	}
	return NULL;
}

void GameEntityManager::resetAlbumEntity(){
	for (auto entityObj : gameEntityArray){
		if (!(entityObj->getValid() == GameEntityStatus::album)){
			continue;
		}
		entityObj->resetEntity();
	}
}

void GameEntityManager::haveEntityForItem(Layer* layer, GameEntityType type, Vec2 pos){
	GameEntity* entity = NULL;
	if (layer->getChildByTag(type) == NULL){//如果当前层上没有火炬实体
		for (auto entityObj : GameEntityManager::getInstance()->gameEntityArray){
			if (entityObj->getType() == type){
				entity = entityObj;
				entityObj->setPosition(pos);
				entityObj->createEntity();
				layer->addChild(entityObj);
				entityObj->setTag(type);
				break;
			}
		}//在现有实体池中查找火炬实体
		if (entity == NULL){
			entity = GameEntityManager::getInstance()->haveEntity(type, pos);
			layer->addChild(entity);
			entity->setTag(type);
		}
	}
}

void GameEntityManager::applyIceBuffToZombie(Layer* layer){
	auto pos = Vec2(Director::getInstance()->getVisibleSize().width / 2, Director::getInstance()->getVisibleSize().height / 2);
	auto effect = new SpecialEffect();
	auto iceshroom = layer->getChildByTag(GameEntityType::iceshroom);
	effect->snowStorm();
	effect->setPosition(pos);
	layer->addChild(effect);

	effect->runAction(Sequence::create(DelayTime::create(4.0f), CallFunc::create(effect, callfunc_selector(SpecialEffect::remove)), NULL));

	for (auto zombieObj : gameEntityArray){
		if (!((zombieObj->getType() > GameEntityType::begin_zombie) && (zombieObj->getType() < GameEntityType::end_zombie) && (zombieObj->getValid() >= GameEntityStatus::valid) && (zombieObj->getValid() != GameEntityStatus::boom) && (zombieObj->getBoundingBox().getMaxX() < 800))){
			continue;
		}
		zombieObj->stopAllActions();
	}
}

GameEntity* GameEntityManager::haveNearestZombie(){
	float distance = Director::getInstance()->getVisibleSize().width;
	GameEntity* zombieRequired = NULL;
	for (auto zombieObj : gameEntityArray){
		if (!((zombieObj->getType() > GameEntityType::begin_zombie) && (zombieObj->getType() < GameEntityType::end_zombie) && (zombieObj->getValid() >= GameEntityStatus::valid) && (zombieObj->getValid() != GameEntityStatus::boom))){
			continue;
		}
		if (zombieObj->getPosition().x < distance){
			distance = zombieObj->getPosition().x;
			zombieRequired = zombieObj;
		}
	}//循环遍历寻找最近的僵尸
	return zombieRequired;
}