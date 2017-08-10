#include "GridManager.h"
#include "cocos2d.h"

GridManager* GridManager::instance = NULL;

GridManager::GridManager(){
	init();
}

GridManager::~GridManager(){

}

GridManager* GridManager::getInstance(){
	if (instance == NULL){
		instance = new GridManager();
	}
	return instance;
}

void GridManager::init(){
	
	int i,j;
	float h=85;
	memset(status,0,sizeof(status));
	grid[0][0] = Vec2(-50,h);
	grid[0][1] = Vec2(85, h);
	grid[0][2] = Vec2(175, h);
	grid[0][3] = Vec2(255, h);
	grid[0][4] = Vec2(340, h);
	grid[0][5] = Vec2(420, h);
	grid[0][6] = Vec2(500, h);
	grid[0][7] = Vec2(575, h);
	grid[0][8] = Vec2(660, h);
	grid[0][9] = Vec2(750, h);
	grid[0][10] = Vec2(840, h);
	for (i = 1; i < 5; i++)
	{
		for (j = 0; j < 11; j++)
		{
			grid[i][j].x = grid[i - 1][j].x;
			grid[i][j].y = grid[i - 1][j].y + 100;
		}
	}

}

Vec2 GridManager::getCoordPosition(){     //获取调整后种植的具体位置，在判断之前，这里表示会有效种植

	status[row][col-1] = 1;   //已种植
	return grid[row][col];
}

bool GridManager::isValidate(Vec2 pos)   //验证输入的点能否有效种植
{
	onJudgePos(pos);
	if (row==-1||col==-1)
		return false;
	if (status[row][col-1])
		return false;
	return true;
}

int GridManager::onJudgePos(Vec2 pos)   //判断输入的点在所在的区域
{
	row = col = -1;
	if (40 <= pos.x&&pos.x < 135)
		col = 1;
	else if (135 <= pos.x&&pos.x < 210)
		col = 2;
	else if (210 <= pos.x&&pos.x < 300)
		col = 3;
	else if (300 <= pos.x&&pos.x < 375)
		col = 4;
	else if (375 <= pos.x&&pos.x < 460)
		col = 5;
	else if (460 <= pos.x&&pos.x < 535)
		col = 6;
	else if (535 <= pos.x&&pos.x < 620)
		col = 7;
	else if (620 <= pos.x&&pos.x < 700)
		col = 8;
	else if (700 <= pos.x&&pos.x <= 780)
		col = 9;

	if (20 <= pos.y&&pos.y < 130)
		row = 0;
	else if (130 <= pos.y&&pos.y < 210)
		row = 1;
	else if (210 <= pos.y&&pos.y < 320)
		row = 2;
	else if (320 <= pos.y&&pos.y < 415)
		row = 3;
	else if (415 <= pos.y&&pos.y <= 510)
		row = 4;
	return row;
}

void GridManager::clearPosStatus(Vec2 pos)   //植物没有后的状态清除
{
	onJudgePos(pos);
	status[row][col-1] = 0;
}

Vec2 GridManager::getCoordPosition(int j)  
{
	return grid[j][10];
}

void GridManager::resetStatus()
{
	memset(status,0,sizeof(status));
}

bool GridManager::isCanShovel(Vec2 pos)
{
	onJudgePos(pos);
	if (row == -1 || col == -1)
		return false;
	if (status[row][col - 1])  //有植物才能铲
		return true;
	return false;
}


#ifdef _DEBUG

Vec2 GridManager::getCoordPosition(int i,int j){
	return grid[i][j];
}

#endif