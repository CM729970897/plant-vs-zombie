#include "GameEntity.h"
#include "GridManager.h"
#include "DataConfig.h"

void GameEntity::baseCreate(char* path, char* name, GameEntityStatus status){
	char local_path[80];
	char local_name[80];
	strcpy(local_path, path);
	strcpy(local_name, name);
	auto cacheFrame = SpriteFrameCache::getInstance();
	cacheFrame->addSpriteFramesWithFile(local_path);
	auto dict = (__Dictionary *)(__Dictionary::createWithContentsOfFile(local_path)->objectForKey("frames"));
	int num = dict->allKeys()->count();
	sprintf(local_path, "%s_1.tiff", local_name);
	this->initWithSpriteFrameName(local_path);
	Vector<SpriteFrame*> plistArray;
	for (int i = 1; i < num; i++) {
		sprintf(local_path, "%s_%i.tiff", local_name, i);
		auto frame = cacheFrame->getSpriteFrameByName(local_path);
		plistArray.pushBack(frame);
	}
	auto plitAnimation = Animation::createWithSpriteFrames(plistArray, 0.15f);
	auto plitAnimate = Animate::create(plitAnimation);
	if (status != GameEntityStatus::boom){
		this->runAction(RepeatForever::create(plitAnimate));
	}
	else{
		this->runAction(plitAnimate);
	}
}



Sequence* GameEntity::haveAction(){
	GridManager* grid = GridManager::getInstance();
	float distance = Director::getInstance()->getVisibleSize().width;
	float time = distance / this->getSpeed();
	MoveTo* moveTo = MoveTo::create(time, Vec2((grid->getCoordPosition(0, 0)).x, this->getPos().y));
	Sequence* move = Sequence::create(moveTo, NULL);
	return move;
}

void GameEntity::resetEntity(){
	this->removeFromParent();
	this->removeAllChildren();
	this->setBuffType(BuffType::nobuff);
	DataConfig::getInstance()->setGameEntityAttr(this);
	this->setValid(GameEntityStatus::invalid);
	createEntity();
}

void GameEntity::fireBuffEffect(){
	auto effect = ParticleSystemQuad::create("game/gameLayer/buff.plist");
	this->addChild(effect);
	this->setBuffType(BuffType::fire);
}