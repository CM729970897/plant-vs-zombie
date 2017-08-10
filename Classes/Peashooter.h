#ifndef __PEASHOOTER_H__
#define __PEASHOOTER_H__

#include "EntityConst.h"
#include "GameEntity.h"

//Õ„∂π…‰ ÷ @hanjie 2017.1.7
class Peashooter :public GameEntity{
public:
	Peashooter(Vec2 pos) :GameEntity(GameEntityType::peashooter, pos){}
	~Peashooter(){}
	virtual void createEntity(){
		char path[] = "game/plants/PeaShooter/PeaShooter_default.plist";
		char name[] = "Peashooter";
		baseCreate(path,name);
	}
};

#endif