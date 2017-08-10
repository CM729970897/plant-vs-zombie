#ifndef __GAME_ENTITY_H__
#define __GAME_ENTITY_H__
#include "cocos2d.h"
#include "EntityConst.h"

USING_NS_CC;
//��Ϸʵ����ֲࣨ���ʬ��
//@hanjie 2017.1.7
class GameEntity : public cocos2d::Sprite{
	GameEntityType type;//ʵ�����ƣ�ֲ���ʬ���ƣ�
	int blood;//����ֵ
	int attack;//ֲ���ӵ�����Ƶ��\��ʬ�����˺�ֵ
	int speed;//ֲ���ٴβ������ȴʱ��\��ʬ�н��ٶ�
	int cost;//����ֲ����Ҫ������ֵ\��ʬ���������
	int point;//����ֲ����ȴʱ��\��ʬ�����ķ���
	int attack_extra;//����ֲ���ӵ�����Ƶ��\��ʬ��Ϊ-1
	GameEntityStatus valid;//ʵ��״̬��־�����ڴ���ʵ�����ײ���
	Vec2 pos;//ʵ���ʼλ�ñ���

	//@hanjie 2017.2.15
	BuffType buff;//�㶹���ֵĹ����ӳɵ���

public:
	//ʵ���ʼ������������ֵ��EntityDataConfig��������ã��˴�ȫ��ȱʡΪ0��
	GameEntity(GameEntityType type,Vec2 pos) :
		type(type), blood(0), attack(0), speed(0), cost(0), valid(GameEntityStatus::invalid), pos(pos), attack_extra(0), point(0),buff(BuffType::nobuff){}
	/*������������*/
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

	/*��������ʵ��*/
	void baseCreate(char* path, char* name, GameEntityStatus status = GameEntityStatus::valid);
	Sequence* haveAction();
	/*�ӿں���*/
	virtual void createEntity() = 0;
	virtual void switchAction(){};//ʵ�嶯���л�(��ʬ����ֲ�﷢����ײ���ʱ����)
    void resetEntity();//ʵ���ʼ������ʵ������ֵ��Ϊ0����á���ʼ���󼴿ɵȴ��´�ʹ��

	//@hanjie 2017.2.20
	void fireBuffEffect();
};

#endif