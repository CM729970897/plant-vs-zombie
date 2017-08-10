#ifndef __VOLUM_SET_H__
#define __VOLUM_SET_H__

#include "cocos2d.h"
#include "EntityConst.h"

USING_NS_CC;

//��������+��Ϸģʽ��  suzhe

class VolumSet {
public:
	static VolumSet* getInstance();
	void setVolum(float volum) { this->volum = volum; }
	float getVolum() { return volum; }
	void setSliderPercent(int sliderPercent) { this->sliderPercent = sliderPercent; }
	int getSliderPercent() { return sliderPercent; }

	void setTVolum(float tvolum) { this->tvolum = tvolum; }
	float getTVolum() { return tvolum; }
	void setTSliderPercent(int tsliderPercent) { this->tsliderPercent = tsliderPercent; }
	int getTSliderPercent() { return tsliderPercent; }

	//2.26 ��Ϸģʽ
	void setMode(GameScene mode) { this->mode = mode; }
	GameScene getMode() { return mode; }

private:
	VolumSet(){}
	//����
	int  sliderPercent = 20;
    float volum=0.2f;
	//��Ч
	int tsliderPercent = 20;
	float tvolum = 0.2f;
	static VolumSet* instance;

	//��Ϸģʽ
	GameScene mode;
};



#endif