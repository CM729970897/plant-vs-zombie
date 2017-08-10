#ifndef __BAMBOOSHOOT_H__
#define __BAMBOOSHOOT_H__

#include "GameEntity.h"
#include "DerivedEntity.h"
#include "EntityConst.h"

//hanjie 2017.2.28
class BambooShoot : public DerivedEntity{
private:
	GameEntity* target;
public:
	void setTarget(GameEntity* target){ this->target = target; }
	GameEntity* getTarget(){ return target; }
	BambooShoot(Vec2 pos) :DerivedEntity(DerivedEntityType::bambooshoot, pos){}
	~BambooShoot(){}
	virtual void createEntity(){
		char path[] = "game/plants/PlantsProduct/BambooShoots.plist";
		char name[] = "BambooShoots";
		createStaticEntity(path, name);
	}
	virtual void switchAction(){
		Vec2 startPoint = Vec2(this->getPlant()->getPosition().x, this->getPlant()->getPosition().y + 20);
		if (target == NULL)return;
		Vec2 endPoint = target->getPosition();
		float angle = 60;
		float height = 20;
		float radian = angle*3.14159 / 180.0;
		float q1x = startPoint.x + (endPoint.x - startPoint.x) / 4.0;
		Vec2 q1 = Vec2(q1x, height + startPoint.y + cos(radian)*q1x);
		float q2x = startPoint.x + (endPoint.x - startPoint.x) / 2.0;
		Vec2 q2 = Vec2(q2x, height + startPoint.y + cos(radian)*q2x);

		ccBezierConfig cfg;
		cfg.controlPoint_1 = q1;
		cfg.controlPoint_2 = q2;
		cfg.endPosition = endPoint;
		EaseInOut* easeInOut = EaseInOut::create(BezierTo::create(1, cfg), 2);

		this->runAction(Spawn::create(RotateBy::create(1, 360), easeInOut, NULL));
	}
};

#endif