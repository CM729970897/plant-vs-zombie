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
	if ((entityType > GameEntityType::begin_plant) && (entityType < GameEntityType::end_zombie)){//����ȡ����һ����Ϸʵ�壨ֲ���ʬ��
		for (auto entityObj : gameEntityArray){//����Ϸʵ����в��ҿ��õ�ʵ��
			if ((entityObj->getType() == entityType) && (entityObj->getValid() == GameEntityStatus::invalid)){//��ǰʵ��Ϊͬ��������Ч�����ã���ʵ��
				entityObj->setPos(pos);
				entityObj->setValid(GameEntityStatus::valid);
				entityObj->setPosition(pos);
				if (entityType > GameEntityType::begin_zombie && entityType < GameEntityType::end_zombie){
					entityObj->runAction(entityObj->haveAction());
				}
				return entityObj;//ֱ�ӷ��ظ�ʵ��
			}
		}
		//��ǰ��Ϸʵ����в����ڿ��õ�ͬ����ʵ��,�򴴽�һ�����õ�ʵ�巵�أ�������Ž�ʵ�����
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
			if (counter == num){//��ǰʵ��Ϊ������Ӧ��ʵ�壬
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
		if (entityObj->getValid() == GameEntityStatus::album){//�������Ѿ�����ͼ��״̬��ʵ�壬���ʵ��������ã���ȷ������ʵ�����ֻ����һ������ͼ��״̬��ʵ��
			resetAlbumEntity();
			break;
		}
	}
	if ((entityType > GameEntityType::begin_plant) && (entityType < GameEntityType::end_zombie)){//����ȡ����һ����Ϸʵ�壨ֲ���ʬ��
		for (auto entityObj : gameEntityArray){//����Ϸʵ����в��ҿ��õ�ʵ��
			if ((entityObj->getType() == entityType) && (entityObj->getValid() == GameEntityStatus::invalid)){//��ǰʵ��Ϊͬ��������Ч�����ã���ʵ��
				entityObj->setPos(pos);
				entityObj->setValid(GameEntityStatus::album);//��������Ϊͼ��״̬�����ٲ���ʵ�彻��
				entityObj->setPosition(pos);
				return entityObj;//ֱ�ӷ��ظ�ʵ��
			}
		}
		//��ǰ��Ϸʵ����в����ڿ��õ�ͬ����ʵ��,�򴴽�һ�����õ�ʵ�巵�أ�������Ž�ʵ�����
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
	if (layer->getChildByTag(type) == NULL){//�����ǰ����û�л��ʵ��
		for (auto entityObj : GameEntityManager::getInstance()->gameEntityArray){
			if (entityObj->getType() == type){
				entity = entityObj;
				entityObj->setPosition(pos);
				entityObj->createEntity();
				layer->addChild(entityObj);
				entityObj->setTag(type);
				break;
			}
		}//������ʵ����в��һ��ʵ��
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
	}//ѭ������Ѱ������Ľ�ʬ
	return zombieRequired;
}