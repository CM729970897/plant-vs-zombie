#include "DerivedEntity.h"
#include "DataConfig.h"

void DerivedEntity::createStaticEntity(char* path,char* name){
	auto cache = SpriteFrameCache::getInstance();
	cache->addSpriteFramesWithFile(path);
	sprintf(path, "%s_1.tiff", name);
	this->initWithSpriteFrameName(path);
}

void DerivedEntity::createDynamicEntity(char* path, char* name){
	auto cacheFrame = SpriteFrameCache::getInstance();
	cacheFrame->addSpriteFramesWithFile(path);
	auto dict = (__Dictionary *)(__Dictionary::createWithContentsOfFile(path)->objectForKey("frames"));
	int num = dict->allKeys()->count();
	sprintf(path, "%s_1.tiff", name);
	this->initWithSpriteFrameName(path);
	Vector<SpriteFrame*> plistArray;
	for (int i = 1; i < num; i++) {
		sprintf(path, "%s_%i.tiff", name, i);
		auto frame = cacheFrame->getSpriteFrameByName(path);
		plistArray.pushBack(frame);
	}
	repeateAction(plistArray);
}

void DerivedEntity::repeateAction(Vector<SpriteFrame*> plistArray){
	auto plitAnimation = Animation::createWithSpriteFrames(plistArray, 0.15f);
	auto plitAnimate = Animate::create(plitAnimation);
	this->runAction(RepeatForever::create(plitAnimate));
}

void DerivedEntity::resetEntity(){
	this->removeFromParent();//从屏幕中消去
	DataConfig::getInstance()->setDerivedEntityAttr(this);//重设属性
	this->setValid(false);
	this->setPlant(NULL);
	this->setScale(1);
}