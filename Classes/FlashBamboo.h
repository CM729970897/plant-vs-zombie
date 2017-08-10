#ifndef __FLASHBAMBOO_H__
#define __FLASHBAMBOO_H__

#include "GameEntity.h"

//ÉÁµçÖñ @hanjie 2017.2.27
class FlashBamboo : public GameEntity{
public:
	FlashBamboo(Vec2 pos) :GameEntity(GameEntityType::flashbamboo, pos){}
	~FlashBamboo(){}
	virtual void createEntity(){
		char path[] = "game/plants/FlashBamboo/FlashBamboo.plist";
		char name[] = "FlashBamboo";
		baseCreate(path, name);
		//this->setScale(0.5);
	}
};

#endif