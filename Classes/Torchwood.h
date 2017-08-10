#ifndef __TOECHWOOD_H__
#define __TOECHWOOD_H__

#include "GameEntity.h"

//�����׮���ӳɵ��ߣ� 2017.2.21
class Torchwood : public GameEntity{
public:
	Torchwood(Vec2 pos) :GameEntity(GameEntityType::torchwood, pos){};
	~Torchwood(){};
	virtual void createEntity(){
		char path[] = "game/plants/Torchwood/Torchwood_default.plist";
		char name[] = "Torchwood";
		baseCreate(path, name);
	}
};

#endif