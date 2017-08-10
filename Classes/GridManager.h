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
	int col;  //��
	int row;  //��
    int status[5][9];   //�ж�ĳһ�����Ƿ��Ѿ���ֲֲ�0��δ�� 1������
	void init();
public:
	static GridManager* getInstance();
	Vec2 getCoordPosition();   //���ص����ƺ��ѡ����ֲֲ��
	bool isValidate(Vec2 pos);
	int onJudgePos(Vec2 pos);   //ֲ�����ɻ���������λ�ö�λ
	void clearPosStatus(Vec2 pos);
	Vec2 getCoordPosition(int j);  //���ؽ�ʬ��ʼλ��
	void resetStatus();
	//2.25
	bool isCanShovel(Vec2 pos);
#ifdef _DEBUG
	Vec2 getCoordPosition(int i,int j);
#endif
};

#endif
