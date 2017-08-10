#ifndef __SPECIALEFFECT_H__
#define __SPECIALEFFECT_H__

#include "cocos2d.h"
#include "EntityConst.h"

USING_NS_CC;

class SpecialEffect:public Sprite{
public:

	bool fireBullet(){
		this->addChild(ParticleSystemQuad::create("game/gameLayer/light.plist"));
		return true;
	}

	bool jalapenoAttack(){
		this->addChild(ParticleSystemQuad::create("game/plants/Jalapeno/JalapenoAttack.plist"));
		return true;
	}

	bool cherryBombAttack(){
		this->addChild(ParticleSystemQuad::create("game/plants/CherryBomb/CherryBombAttack.plist"));
		return true;
	}

	bool snowStorm(){
		this->addChild(ParticleSystemQuad::create("game/plants/IceShroom/storm.plist"));
		return true;
	}

	bool frozen(){
		this->addChild(ParticleSystemQuad::create("game/plants/IceShroom/frozen.plist"));
		return true;
	}

	void remove(){
		this->removeFromParent();
	}
};

#endif