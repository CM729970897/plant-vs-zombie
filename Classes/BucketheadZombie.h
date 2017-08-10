#ifndef __BUCKETHEAD_ZOMBIE_H__
#define __BUCKETHEAD_ZOMBIE_H__

#include "EntityConst.h"
#include "GameEntity.h"
#include "GridManager.h"

//ÌúÍ°½©Ê¬Àà @hanjie 2017.1.9
class BucketheadZombie : public GameEntity{
public:
	BucketheadZombie(Vec2 pos) :GameEntity(GameEntityType::buckethead_zombie,pos){
		this->setScale(0.8f);
	}
	~BucketheadZombie(){}
	virtual void createEntity(){
		char path[] = "game/zombies/BucketheadZombie/BucketheadZombie_default.plist";
		char name[] = "BucketheadZombie";
		baseCreate(path,name);
	}
	virtual void switchAction(){
		switch (this->getValid()){
		case GameEntityStatus::attack:
			this->stopAllActions();
			baseCreate("game/zombies/BucketheadZombie/BucketheadZombieAttack_default.plist", "BucketheadZombieAttack");
			break;
		case GameEntityStatus::valid:
			this->stopAllActions();
			baseCreate("game/zombies/BucketheadZombie/BucketheadZombie_default.plist", "BucketheadZombie");
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