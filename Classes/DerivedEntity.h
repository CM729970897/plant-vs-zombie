#ifndef __DERIVED_ENTITY_H__
#define __DERIVED_ENTITY_H__

#include "cocos2d.h"
#include "GameEntity.h"
#include "EntityConst.h"

USING_NS_CC;
//派生实体类（子弹、阳光）
//@ hanjie 2017.1.7
class DerivedEntity :public cocos2d::Sprite{
	DerivedEntityType type;//派生实体类型
	GameEntity* plant;//派生实体所属的游戏实体，对于场景内随机出现的阳光，暂设为nullptr
	int power;//子弹的伤害值\阳光的能量值
	bool valid;//实体有效性标记。0：无效实体；1：未发出的实体；2：已发出实体
	Vec2 pos;//实体位置备份

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