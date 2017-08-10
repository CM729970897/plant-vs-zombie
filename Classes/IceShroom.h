#ifndef __ICESHROOM_H__
#define __ICESHROOM_H__

#include "GameEntity.h"

//º®±ù¹½£¨¼õËÙµÀ¾ß£©@hanjie 2017.2.23
class IceShroom : public GameEntity{
public:
	IceShroom(Vec2 pos):GameEntity(GameEntityType::iceshroom,pos){}
	~IceShroom(){};
	virtual void createEntity(){
		char path[] = "game/plants/IceShroom/IceShroom.plist";
		char name[] = "IceShroom";
		baseCreate(path, name);
	}
};

#endif