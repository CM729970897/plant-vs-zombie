#ifndef __GAME_ENTITY_MANAGER_H__
#define __GAME_ENTITY_MANAGER_H__

#include "cocos2d.h"
#include "EntityConst.h"
#include "GameEntity.h"
#include "DerivedEntity.h"
#include "DataConfig.h"

USING_NS_CC;
//游戏实体管理类，用于游戏实体的统一化管理，包括创建，运动，回收等 @ hanjie 2017.1.8
//改为单例模式 @hanjie 2017.1.12
class GameEntityManager{
private:
	static GameEntityManager* instance;
	DataConfig* dataConfig;
	GameEntityManager(){ dataConfig = DataConfig::getInstance(); }
	~GameEntityManager(){}
	GameEntity* createEntity(GameEntityType entityType, Vec2 pos);
public:
	static GameEntityManager* getInstance();
	Vector<GameEntity*>gameEntityArray;//游戏实体池
	GameEntity* haveEntity(GameEntityType entityType, Vec2 pos);

	//@hanjie 2017.2.16
	int countValidNobuffPeashooter();//计算有效且无加成的豌豆射手数量
	void applyFireBuffToPeashooter(Layer* layer, ValueVector index, BuffType type);//根据给定的索引值，对索引所对应的植物设置buff
	GameEntity* haveEntityForAlbum(GameEntityType entityType, Vec2 pos);//给出用于图鉴的游戏实体（仅用于图鉴）
	void resetAlbumEntity();//重置图鉴实体
	
	//@hanjie 2017.2.24
	void haveEntityForItem(Layer* layer, GameEntityType type, Vec2 pos);//给出作为道具的游戏实体（用于商店、背包和游戏模式【不参与碰撞检测】中）
	void applyIceBuffToZombie(Layer* layer);

	//@hanjie 2017.2.27
	GameEntity* haveNearestZombie();//寻找场上走在最左边的僵尸（闪电竹的攻击对象）
};

#endif