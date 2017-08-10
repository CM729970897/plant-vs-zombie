#ifndef __FLAG_ZOMBIE_H__
#define __FLAG_ZOMBIE_H__

#include "GameEntity.h"

//ÆìÖÄ½©Ê¬ @hanjie 2017.1.11
class FlagZombie : public GameEntity{
public:
	FlagZombie(Vec2 pos) :GameEntity(GameEntityType::flag_zombie, pos){
		this->setScale(0.8f);
	}
	~FlagZombie(){}
	virtual void createEntity(){
		char path[] = "game/zombies/FlagZombie/FlagZombie_default.plist";
		char name[] = "FlagZombie";
		baseCreate(path,name);
	}
	virtual void switchAction(){
		switch (this->getValid()){
		case GameEntityStatus::attack:
			this->stopAllActions();
			baseCreate("game/zombies/FlagZombie/FlagZombieAttack_default.plist", "FlagZombieAttack");
			break;
		case GameEntityStatus::valid:
			this->stopAllActions();
			baseCreate("game/zombies/FlagZombie/FlagZombie_default.plist", "FlagZombie");
			this->runAction(haveAction());
			break;
		case GameEntityStatus::boom:
			this->stopAllActions();
			baseCreate("game/zombies/boomDie/BoomDie_default.plist", "BoomDie", this->getValid());
			break;
		default:
			break;
		}
	}
};

#endif