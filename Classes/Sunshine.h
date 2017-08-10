#ifndef __SUNSHINE_H__
#define __SUNSHINE_H__

#include "DerivedEntity.h"

class Sunshine :public DerivedEntity{
public:
	Sunshine(Vec2 pos):DerivedEntity(DerivedEntityType::sunshine,pos){}
	~Sunshine(){}
	virtual void createEntity(){
		char path[] = "game/plants/PlantsProduct/Sun_default.plist";
		char name[] = "Sun";
		createDynamicEntity(path, name);
	}
	virtual void switchAction(){//阳光的运动轨迹
		Vec2 startPoint, endPoint;
		int delta_x = random() % 20;
		int delta_y = random() % 20;
		if (this->getPlant() != NULL){
			startPoint = this->getPlant()->getPosition();
			if (random() % 2 == 0){
				if (random() % 2 == 0){
					endPoint = Vec2(startPoint.x + 20 - delta_x, startPoint.y - 20 - delta_y);
				}
				else{
					endPoint = Vec2(startPoint.x + 20 - delta_x, startPoint.y - 20 + delta_y);
				}
			}
			else{
				if (random() % 2 == 0){
					endPoint = Vec2(startPoint.x + 20 + delta_x, startPoint.y - 20 - delta_y);
				}
				else{
					endPoint = Vec2(startPoint.x + 20 + delta_x, startPoint.y - 20 + delta_y);
				}
			}
		}
		else{
			startPoint = this->getPos();
			endPoint = Vec2(startPoint.x, startPoint.y - 600);
		}
		float angle = 80;
		float height = 10;
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

		this->runAction(Spawn::create(RotateBy::create(1, 360),easeInOut,NULL));
	}
};

#endif