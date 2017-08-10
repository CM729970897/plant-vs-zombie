#ifndef __WALLNUT_H__
#define __WALLNUT_H__

#include "EntityConst.h"
#include "GameEntity.h"

//¼á¹ûÇ½ @hanjie 2017.1.12
class WallNut :public GameEntity{
public:
	WallNut(Vec2 pos) :GameEntity(GameEntityType::wallnut, pos){}
	~WallNut(){}
	virtual void createEntity(){
		char path[] = "game/plants/Wall_Nut/WallNut_default.plist";
		char name[] = "WallNut";
		baseCreate(path, name);
	}
};

#endif