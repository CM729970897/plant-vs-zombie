#ifndef __SUNFLOWER_H__
#define __SUNFLOWER_H__

#include "EntityConst.h"
#include "GameEntity.h"

//ÏòÈÕ¿û @hanjie 2017.1.8
class Sunflower :public GameEntity{
public:
	Sunflower(Vec2 pos):GameEntity(GameEntityType::sunflower, pos){}
	~Sunflower(){}
	virtual void createEntity(){
		char path[] = "game/plants/SunFlower/SunFlower_default.plist";
		char name[] = "SunFlower";
		baseCreate(path,name);
	}
};

#endif