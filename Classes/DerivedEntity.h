#ifndef __DERIVED_ENTITY_H__
#define __DERIVED_ENTITY_H__

#include "cocos2d.h"
#include "GameEntity.h"
#include "EntityConst.h"

USING_NS_CC;
//����ʵ���ࣨ�ӵ������⣩
//@ hanjie 2017.1.7
class DerivedEntity :public cocos2d::Sprite{
	DerivedEntityType type;//����ʵ������
	GameEntity* plant;//����ʵ����������Ϸʵ�壬���ڳ�����������ֵ����⣬����Ϊnullptr
	int power;//�ӵ����˺�ֵ\���������ֵ
	bool valid;//ʵ����Ч�Ա�ǡ�0����Чʵ�壻1��δ������ʵ�壻2���ѷ���ʵ��
	Vec2 pos;//ʵ��λ�ñ���

	//@hanjie 2017.2.16
	BuffType buff_type;
public:
	DerivedEntity(DerivedEntityType type, Vec2 pos) : type(type), plant(NULL), power(0), valid(false), pos(pos), buff_type(BuffType::nobuff){}
	~DerivedEntity(){}
	DerivedEntityType getType(){ return type; }
	void setType(DerivedEntityType type){ this->type = type; }
	GameEntity* getPlant(){ return plant; }
	void setPlant(GameEntity* plant){ this->plant = plant; }
	int getPower(){ return power; }
	void setPower(int power){ this->power = power; }
	bool getValid(){ return valid; }
	void setValid(bool valid){ this->valid = valid; }
	Vec2 getPos(){ return pos; }
	void setPos(Vec2 pos){ this->pos = pos; }
	void createStaticEntity(char* path,char* name);
	void createDynamicEntity(char* path,char* name);
	void repeateAction(Vector<SpriteFrame*> plistArray);
	virtual void createEntity() = 0;
	virtual void switchAction() = 0;
    void resetEntity();

	//@hanjie 2017.2.16
	void setBuff(BuffType type){ this->buff_type = type; };
	void resetBuff(){ this->buff_type = BuffType::nobuff; }
};


#endif