#ifndef __GRIDMANAGER_H__
#define __GRIDMANAGER_H__
#include "cocos2d.h"
USING_NS_CC;
class GridManager{
private:
	static GridManager* instance;
	GridManager();
	~GridManager();
	Vec2 grid[5][11];
	int col;  //列
	int row;  //行
    int status[5][9];   //判断某一区域是否已经种植植物，0：未种 1：已种
	void init();
public:
	static GridManager* getInstance();
	Vec2 getCoordPosition();   //返回点击草坪后选择种植植物
	bool isValidate(Vec2 pos);
	int onJudgePos(Vec2 pos);   //植物生成或死亡坐标位置定位
	void clearPosStatus(Vec2 pos);
	Vec2 getCoordPosition(int j);  //返回僵尸初始位置
	void resetStatus();
	//2.25
	bool isCanShovel(Vec2 pos);
#ifdef _DEBUG
	Vec2 getCoordPosition(int i,int j);
#endif
};

#endif
