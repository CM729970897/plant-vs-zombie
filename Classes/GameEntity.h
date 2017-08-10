#ifndef __GAME_ENTITY_H__
#define __GAME_ENTITY_H__
#include "cocos2d.h"
#include "EntityConst.h"

USING_NS_CC;
//游戏实体基类（植物、僵尸）
//@hanjie 2017.1.7
class GameEntity : public cocos2d::Sprite{
	GameEntityType type;//实体名称（植物、僵尸名称）
	int blood;//生命值
	int attack;//植物子弹发射频率\僵尸进攻伤害值
	int speed;//植物再次部署的冷却时间\僵尸行进速度
	int cost;//部署植物需要的阳光值\僵尸奖励金币数
	int point;//备份植物冷却时间\僵尸奖励的分数
	int attack_extra;//备份植物子弹发射频率\僵尸设为-1
	GameEntityStatus valid;//实体状态标志，用于创建实体和碰撞检测
	Vec2 pos;//实体初始位置备份

	//@hanjie 2017.2.15
	BuffType buff;//豌豆射手的攻击加成道具

public:
	//实体初始化函数（属性值由EntityDataConfig类进行设置，此处全部缺省为0）
	GameEntity(GameEntityType type,Vec2 pos) :
		type(type), blood(0), attack(0), speed(0), cost(0), valid(GameEntityStatus::invalid), pos(pos), attack_extra(0), point(0),buff(BuffType::nobuff){}
	/*基本属性设置*/
	GameEntityType getType(){ return type; }
	void setType(GameEntityType type){ this->type = type; }
	int getBlood(){ return blood; }
	void setBlood(int life){ this->blood = life; }
	int getAttack(){ return attack; }
	void setAttack(int attack){ this->attack = attack; }
	int getSpeed(){ return speed; }
	void setSpeed(int speed){ this->speed = speed; }
	int getCost(){ return cost; }
	void setCost(int cost){ this->cost = cost; }
	int getPoint(){ return point; }
	void setPoint(int speed){ this->point = speed; }
	int getAttackExtra(){ return attack_extra; }
	void setAttackExtra(int attack){ this->attack_extra = attack; }
	GameEntityStatus getValid(){ return valid; }
	void setValid(GameEntityStatus valid){ this->valid = valid; }
	Vec2 getPos(){ return pos; }
	void setPos(Vec2 pos){ this->pos = pos; }

	//@hanjie 2017.2.15
	BuffType getBuffType(){ return buff; }
	void setBuffType(BuffType buff){ this->buff = buff; }

	/*基础创建实体*/
	void baseCreate(char* path, char* name, GameEntityStatus status = GameEntityStatus::valid);
	Sequence* haveAction();
	/*接口函数*/
	virtual void createEntity() = 0;
	virtual void switchAction(){};//实体动作切换(僵尸在与植物发生碰撞检测时调用)
    void resetEntity();//实体初始化，在实体生命值降为0后调用。初始化后即可等待下次使用

	//@hanjie 2017.2.20
	void fireBuffEffect();
};

#endif