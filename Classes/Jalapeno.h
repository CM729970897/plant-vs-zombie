#ifndef __JALAPENO_H__
#define __JALAPENO_H__

#include "EntityConst.h"
#include "GameEntity.h"

//»ð±¬À±½·
class Jalapeno : public GameEntity{
public:
	Jalapeno(Vec2 pos) :GameEntity(GameEntityType::jalapeno, pos){}
	~Jalapeno(){}
	virtual void createEntity(){
		char path[] = "game/plants/Jalapeno/Jalapeno_default.plist";
		char name[] = "Jalapeno";
		baseCreate(path, name);
	}
};

#endif