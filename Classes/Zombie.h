#ifndef __ZOMBIE_H__
#define __ZOMBIE_H__

#include "EntityConst.h"
#include "GameEntity.h"
#include "GridManager.h"

//ÆÕÍ¨½©Ê¬Àà @hanjie 2017.1.9
class Zombie :public GameEntity{
public:
	Zombie(Vec2 pos) :GameEntity(GameEntityType::zombie,pos){
		this->setScale(0.8f);
	}
	~Zombie(){}
	virtual void createEntity(){
		char path[] = "game/zombies/Zombie/Zombie_default.plist";
		char name[] = "Zombie";
		baseCreate(path,name);
	}
	virtual void switchAction(){
		switch (this->getValid()){
		case GameEntityStatus::attack:
			this->stopAllActions();
			baseCreate("game/zombies/Zombie/ZombieAttack_default.plist", "ZombieAttack");
			break;
		case GameEntityStatus::valid:
			this->stopAllActions();
			baseCreate("game/zombies/Zombie/Zombie_default.plist", "Zombie");
			this->runAction(haveAction());
			break;
		case GameEntityStatus::boom:
			this->stopAllActions();
			baseCreate("game/zombies/boomDie/BoomDie_default.plist","BoomDie",this->getValid());
			break;
		default:
			break;
		}
	}
};

#endif