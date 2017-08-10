#ifndef __PEABULLET_H__
#define __PEABULLET_H__

#include "EntityConst.h"
#include "GameEntity.h"
#include "DerivedEntity.h"
#include "GridManager.h"

class Peabullet :public DerivedEntity{
public:
	Peabullet(Vec2 pos) :DerivedEntity(DerivedEntityType::peabullet,Vec2(pos.x+20,pos.y+20)){}
	~Peabullet(){}
	virtual void createEntity(){
		if (this->getPlant() != NULL){
			if (this->getPlant()->getBuffType() == BuffType::fire){
				char path[] = "game/plants/PlantsProduct/FiredBullet_default.plist";
				char name[] = "firedbullet";
				this->setType(DerivedEntityType::fire_peabullet);
				this->setScale(0.8f);
				createDynamicEntity(path, name);
			}
			else{
				char path[] = "game/plants/PlantsProduct/PeashooterBullet_default.plist";
				char name[] = "PeashooterBullet";
				createStaticEntity(path, name);
			}
		}
	}
	virtual void switchAction(){
		GridManager* gridManager = GridManager::getInstance();
		int row = gridManager->onJudgePos(this->getPlant()->getPosition());
		MoveTo* moveTo = MoveTo::create(3,Vec2(gridManager->getCoordPosition(row).x,this->getPos().y));
		Sequence* move = Sequence::create(moveTo,NULL);
		this->runAction(move);
	}
};

#endif