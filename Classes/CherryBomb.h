#ifndef __CHERRYBOMB_H__
#define __CHERRYBOMB_H__

#include "EntityConst.h"
#include "GameEntity.h"

//”£Ã“’®µØ @hanjie 2017.1.13
class CherryBomb : public GameEntity{
public:
	CherryBomb(Vec2 pos) :GameEntity(GameEntityType::cherrybomb, pos){}
	~CherryBomb(){}
	virtual void createEntity(){
		char path[] = "game/plants/CherryBomb/CherryBomb_default.plist";
		char name[] = "CherryBomb";
		baseCreate(path, name);
	}
};

#endif