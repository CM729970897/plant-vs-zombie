#ifndef __ENTITYINTERACTMANAGER_H__
#define __ENTITYINTERACTMANAGER_H__

#include "cocos2d.h"
#include "GameEntityManager.h"
#include "DerivedEntityManager.h"
#include "GridManager.h"

USING_NS_CC;

//ʵ�彻����������ģʽ��[������ײ���] @hanjie 2017.1.12

class EntityInteractManager{
private:
	GameEntityManager* gameEntityManager;
	DerivedEntityManager* derivedEntityManager;
	GridManager* gridManager;

	static EntityInteractManager* instance;
	int randomSunshineInterval_const = 15;//�����������������ʱ������������
	int randomSunshineInterval_temp = 15;//�����������������ʱ������������
	ValueMapIntKey zombieAppearProb;//���ֽ�ʬ���ֵĸ����б�����һ��Ϊ���ұ����䣬�������0-100��
	ValueMapIntKey zombieNumConfig;//��ʬ���ֵ�ʱ��������������
	int currentZombieInterval_temp=5;//��ǰ�غ��½�ʬ���ֵ�ʱ������������
	int currentZombieInterval_const=5;//��ǰ�غ��½�ʬ���ֵ�ʱ������������
	int currentScore = 1000;
	
	EntityInteractManager(){ init(); };
	~EntityInteractManager();
	Rect getBoundingBox(Sprite* entity);
	void init();

	//@hanjie 2017.2.13
	Rect getCherryBombArea(Sprite* entity);//��ȡӣ�ҵı�ը��Χ��Χ������9��ÿ���ȡ85����ȡ100.

	//@hanjie 2017.2.14
	bool zombieAppear(Layer* layer, bool mode);//������������������õĸ������䣬����ÿ�г��ֵĽ�ʬ,mode��ʶ��Ϸģʽ��trueΪð�գ�falseΪ����;����ֵ��true��ʾ��ǰ��Ϸ���Լ����ͷŽ�ʬ��false��ʾ��ǰ��Ϸ���ܼ����ͷŽ�ʬ
	bool judgeZombieCrossLine();//�жϽ�ʬ�Ƿ�Խ�����ĵ���,trueΪԽ�ߣ�falseΪδԽ��
	bool judgeZombieValidation();//�жϵ�ǰ�����Ƿ������Ч�Ľ�ʬ��trueΪ���ڣ�falseΪ������

	//su 2.26
	std::map<GameEntityType, int>pMap;
	int point=0;   //����ģʽ����

public:
	static EntityInteractManager* getInstance();
	
	//@hanjie 2017.1.13����2017.1.14
	void plantsAttackZombies(Layer* layer);//ֲ��Խ�ʬ�Ĺ���
	void zombiesAttackPlants(Layer* layer);//�����Ľ�ʬ�������ֲ��֮�����ײ��⣨�ı�ֲ���Ѫ����
	void checkHitZombiesAndBullets(Layer* layer);//��ʬ���ӵ�����ײ���
	void checkHitWalkZombiesAndLivePlants();//���ߵĽ�ʬ�������ֲ��֮�����ײ��⣨ת�佩ʬ�˶���̬��
	void checkHitAttackZombiesAndDeadPlants();//�����Ľ�ʬ��������ֲ��֮�����ײ��⣨ת�佩ʬ�˶���̬��
	void collectSunshine(Vec2 pos);//������ռ�����

	//@hanjie 2017.2.4
	void produceRandomSunshine(Layer* layer);//�����������������
	bool loadZombieConfig(ValueMapIntKey numList,ValueMapIntKey probList);//���ظ��ֽ�ʬ���ֵ���������
	//bool zombieAppear(Layer* layer,bool mode);//������������������õĸ������䣬����ÿ�г��ֵĽ�ʬ,mode��ʶ��Ϸģʽ��trueΪð�գ�falseΪ����

	//@hanjie 2017.2.14
	GameStatus judgeGameStatus(Layer* layer,bool mode);//������Ϸģʽ����Ӧ�������жϵ�ǰ��Ϸ״̬����δ�������򲻶ϵ������µĽ�ʬ��true��ʾ��Ϸ������false��ʾ��Ϸ����

	void setSunScore(int x) { currentScore = x; }
	int getSunScore() { return currentScore; }

	//@hanjie 2017.2.21
	void plantCherryBomb(Layer* layer, GameEntity* plantObj);
	void plantJalapeno(Layer* layer, GameEntity* plantObj);
	void UnleashFireBuff(Layer* layer);//�ͷŻ���ӳɵ���
	void randomDropGold(Layer* layer, GameEntity* zombie);//��ʬ����ʱ��������ҡ���Ұ���һ���ĸ����������䡿
	void collectGold(Vec2 pos);//�ռ����

	//@hanjie 2017.2.23
	void collectAllGolds();//��Ϸʤ��ʱ���ռ�����δ��ʰ�Ľ�ҡ�

	//@hanjie 2017.2.24
	void UnleashIceBuff(Layer* layer);//�ͷź������ٵ���

	//su 2.27
	void setPoint(int point) { this->point = point; }
	//su 2.26
	int getPoint() { return point; }  //��ȡ��ǰ����

	void ShovelPlant(Vec2 pos);
};

#endif