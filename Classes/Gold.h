#ifndef __GOLD_H__
#define __GOLD_H__

#include "DerivedEntity.h"

//½©Ê¬ÕóÍöÊ±Ëæ»úµôÂäµÄ½ð±Ò
class Gold : public DerivedEntity{
public :
	Gold(Vec2 pos) :DerivedEntity(DerivedEntityType::gold, pos){};
	~Gold(){};
	virtual void createEntity(){
		char path[] = "game/plants/PlantsProduct/Gold_default.plist";
		char name[] = "gold";
		createDynamicEntity(path, name);
	}
	virtual void switchAction(){
		Vec2 startPoint, endPoint;
	    startPoint = this->getPosition();
		int delta_x = random() % 20;
		int delta_y = random() % 20;
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
		if (endPoint.x > Director::getInstance()->getVisibleSize().width){
			endPoint.x -= 35;
		}
		if (endPoint.x < 0){
			endPoint.x += 35;
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

		this->runAction(Spawn::create(RotateBy::create(1, 360), easeInOut, NULL));
	}
};

#endif