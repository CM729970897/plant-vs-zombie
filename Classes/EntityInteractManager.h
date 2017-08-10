#ifndef __ENTITYINTERACTMANAGER_H__
#define __ENTITYINTERACTMANAGER_H__

#include "cocos2d.h"
#include "GameEntityManager.h"
#include "DerivedEntityManager.h"
#include "GridManager.h"

USING_NS_CC;

//实体交互管理（单例模式）[包括碰撞检测] @hanjie 2017.1.12

class EntityInteractManager{
private:
	GameEntityManager* gameEntityManager;
	DerivedEntityManager* derivedEntityManager;
	GridManager* gridManager;

	static EntityInteractManager* instance;
	int randomSunshineInterval_const = 15;//天空中随机掉落的阳光时间间隔（定量）
	int randomSunshineInterval_temp = 15;//天空中随机掉落的阳光时间间隔（变量）
	ValueMapIntKey zombieAppearProb;//各种僵尸出现的概率列表（概率一律为左开右闭区间，总区间从0-100）
	ValueMapIntKey zombieNumConfig;//僵尸出现的时间间隔和数量配置
	int currentZombieInterval_temp=5;//当前回合下僵尸出现的时间间隔（变量）
	int currentZombieInterval_const=5;//当前回合下僵尸出现的时间间隔（定量）
	int currentScore = 1000;
	
	EntityInteractManager(){ init(); };
	~EntityInteractManager();
	Rect getBoundingBox(Sprite* entity);
	void init();

	//@hanjie 2017.2.13
	Rect getCherryBombArea(Sprite* entity);//获取樱桃的爆炸范围，围绕自身共9格，每格宽取85，高取100.

	//@hanjie 2017.2.14
	bool zombieAppear(Layer* layer, bool mode);//根据随机结果，结合设置的概率区间，设置每行出现的僵尸,mode标识游戏模式：true为冒险，false为生存;返回值：true表示当前游戏可以继续释放僵尸，false表示当前游戏不能继续释放僵尸
	bool judgeZombieCrossLine();//判断僵尸是否越过最后的底线,true为越线，false为未越线
	bool judgeZombieValidation();//判断当前场上是否存在有效的僵尸，true为存在，false为不存在

	//su 2.26
	std::map<GameEntityType, int>pMap;
	int point=0;   //生存模式积分

public:
	static EntityInteractManager* getInstance();
	
	//@hanjie 2017.1.13——2017.1.14
	void plantsAttackZombies(Layer* layer);//植物对僵尸的攻击
	void zombiesAttackPlants(Layer* layer);//攻击的僵尸与生存的植物之间的碰撞检测（改变植物的血量）
	void checkHitZombiesAndBullets(Layer* layer);//僵尸与子弹的碰撞检测
	void checkHitWalkZombiesAndLivePlants();//行走的僵尸与生存的植物之间的碰撞检测（转变僵尸运动形态）
	void checkHitAttackZombiesAndDeadPlants();//攻击的僵尸与死亡的植物之间的碰撞检测（转变僵尸运动形态）
	void collectSunshine(Vec2 pos);//鼠标点击收集阳光

	//@hanjie 2017.2.4
	void produceRandomSunshine(Layer* layer);//天空中随机掉落的阳光
	bool loadZombieConfig(ValueMapIntKey numList,ValueMapIntKey probList);//加载各种僵尸出现的配置数据
	//bool zombieAppear(Layer* layer,bool mode);//根据随机结果，结合设置的概率区间，设置每行出现的僵尸,mode标识游戏模式：true为冒险，false为生存

	//@hanjie 2017.2.14
	GameStatus judgeGameStatus(Layer* layer,bool mode);//根据游戏模式和相应的条件判断当前游戏状态。若未结束，则不断的生成新的僵尸。true表示游戏结束，false表示游戏继续

	void setSunScore(int x) { currentScore = x; }
	int getSunScore() { return currentScore; }

	//@hanjie 2017.2.21
	void plantCherryBomb(Layer* layer, GameEntity* plantObj);
	void plantJalapeno(Layer* layer, GameEntity* plantObj);
	void UnleashFireBuff(Layer* layer);//释放火焰加成道具
	void randomDropGold(Layer* layer, GameEntity* zombie);//僵尸阵亡时随机掉落金币【金币按照一定的概率连续掉落】
	void collectGold(Vec2 pos);//收集金币

	//@hanjie 2017.2.23
	void collectAllGolds();//游戏胜利时，收集场上未捡拾的金币。

	//@hanjie 2017.2.24
	void UnleashIceBuff(Layer* layer);//释放寒冰减速道具

	//su 2.27
	void setPoint(int point) { this->point = point; }
	//su 2.26
	int getPoint() { return point; }  //获取当前积分

	void ShovelPlant(Vec2 pos);
};

#endif