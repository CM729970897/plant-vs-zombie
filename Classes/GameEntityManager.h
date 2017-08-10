#ifndef __GAME_ENTITY_MANAGER_H__
#define __GAME_ENTITY_MANAGER_H__

#include "cocos2d.h"
#include "EntityConst.h"
#include "GameEntity.h"
#include "DerivedEntity.h"
#include "DataConfig.h"

USING_NS_CC;
//��Ϸʵ������࣬������Ϸʵ���ͳһ�����������������˶������յ� @ hanjie 2017.1.8
//��Ϊ����ģʽ @hanjie 2017.1.12
class GameEntityManager{
private:
	static GameEntityManager* instance;
	DataConfig* dataConfig;
	GameEntityManager(){ dataConfig = DataConfig::getInstance(); }
	~GameEntityManager(){}
	GameEntity* createEntity(GameEntityType entityType, Vec2 pos);
public:
	static GameEntityManager* getInstance();
	Vector<GameEntity*>gameEntityArray;//��Ϸʵ���
	GameEntity* haveEntity(GameEntityType entityType, Vec2 pos);

	//@hanjie 2017.2.16
	int countValidNobuffPeashooter();//������Ч���޼ӳɵ��㶹��������
	void applyFireBuffToPeashooter(Layer* layer, ValueVector index, BuffType type);//���ݸ���������ֵ������������Ӧ��ֲ������buff
	GameEntity* haveEntityForAlbum(GameEntityType entityType, Vec2 pos);//��������ͼ������Ϸʵ�壨������ͼ����
	void resetAlbumEntity();//����ͼ��ʵ��
	
	//@hanjie 2017.2.24
	void haveEntityForItem(Layer* layer, GameEntityType type, Vec2 pos);//������Ϊ���ߵ���Ϸʵ�壨�����̵ꡢ��������Ϸģʽ����������ײ��⡿�У�
	void applyIceBuffToZombie(Layer* layer);

	//@hanjie 2017.2.27
	GameEntity* haveNearestZombie();//Ѱ�ҳ�����������ߵĽ�ʬ��������Ĺ�������
};

#endif