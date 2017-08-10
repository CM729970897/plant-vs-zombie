#ifndef __CONEHEAD_ZOMBIE_H__
#define __CONEHEAD_ZOMBIE_H__

#include "EntityConst.h"
#include "GameEntity.h"

//Â·ÕÏ½©Ê¬Àà @hanjie 2017.1.11
class ConeheadZombie : public GameEntity{
public:
	ConeheadZombie(Vec2 pos) :GameEntity(GameEntityType::conehead_zombie, pos){
		this->setScale(0.8f);
	}
	virtual void createEntity(){
		char path[] = "game/zombies/ConeheadZombie/ConeheadZombie_default.plist";
		char name[] = "ConeheadZombie";
		baseCreate(path,name);
	}
	virtual void switchAction(){
		switch (this->getValid()){
		case GameEntityStatus::attack:
			this->stopAllActions();
			baseCreate("game/zombies/ConeheadZombie/ConeheadZombieAttack_default.plist", "ConeheadZombieAttack");
			break;
		case GameEntityStatus::valid:
			this->stopAllActions();
			baseCreate("game/zombies/ConeheadZombie/ConeheadZombie_default.plist", "ConeheadZombie");
			this->runAction(haveAction());
			break;
		case GameEntityStatus::boom:
			this->stopAllActions();
			baseCreate("game/zombies/boomDie/BoomDie_default.plist", "BoomDie",this->getValid());
			break;
		default:
			break;
		}
	}
};

#endif