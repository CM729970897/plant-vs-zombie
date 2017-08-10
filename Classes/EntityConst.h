#ifndef __ENTITY_CONST_H__
#define __ENTITY_CONST_H__


#include"cocos2d.h"
USING_NS_CC;
//定义游戏实体常数
//@hanjie 2017.1.7
typedef enum {
	begin_plant = 100,
	sunflower,//向日葵
	wallnut,//坚果墙
	peashooter,//豌豆射手
	cherrybomb,//樱桃炸弹
	jalapeno,//火爆辣椒
	flashbamboo,//闪电竹
	end_plant,
	torchwood = 130,//火炬树桩（攻击加成道具）
	iceshroom,//寒冰菇（僵尸减速道具）
	begin_zombie = 150,
	zombie,//普通僵尸
	buckethead_zombie,//铁桶僵尸
	conehead_zombie,//路障僵尸
	flag_zombie,//旗帜僵尸
	end_zombie
}GameEntityType;//游戏实体类型

typedef enum{
	invalid  = 0,//无效状态（不可见）
	album,//图鉴状态（不参与实体交互和碰撞检测，且游戏实体池中最多只可以有一个实体处于该状态）
	valid,//有效状态（植物为在场状态，僵尸为行走状态）
	attack,//攻击状态（僵尸特有的状态）
	boom//爆炸状态
}GameEntityStatus;//游戏实体状态

typedef enum{
	begin_derived_entity_type = 200,
	sunshine,//阳光
	peabullet,//豌豆子弹
	fire_peabullet,//拥有攻击加成的豌豆子弹
	gold,//僵尸阵亡随机掉落的金币
	bambooshoot,//竹笋子弹
	end_derived_entity_type
}DerivedEntityType;//派生实体类型

typedef enum{
	nobuff = 400,//没有加成
	fire//攻击加成
}BuffType;//道具类型

typedef enum{
	success = 500,//游戏通关
	failure,//游戏失败
	on//游戏继续
}GameStatus;

typedef enum{
	main_menu = 600,//游戏菜单场景
	adventure_mode,//游戏冒险模式场景
	survival_mode//游戏生存模式场景
}GameScene;

//植物面板
struct OPT
{
	Point start;       // 植物初始在面板中的位置
	int value;
	int x;
	int y;
};
struct ONOFF
{
	bool on;
	bool on2;
	int value;
	int score;
};

#endif