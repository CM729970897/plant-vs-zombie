#ifndef __ENTITYDATA_CONFIG_H__
#define __ENTITYDATA_CONFIG_H__

#include "json/json.h"
#include "cocos2d.h"
#include "EntityConst.h"
#include "GameEntity.h"
#include "DerivedEntity.h"
#include "User.h"
#include "ShopItem.h"

USING_NS_CC;

//游戏数据配置读取
//@hanjie 2017.2.17
class DataConfig {
private:
	Json::Reader reader;
	Json::FastWriter writer;
	Json::Value entity_config;//实体基本数据
	Json::Value game_config;//游戏基本数据
	Json::Value user_config;  //用户信息数据
	Json::Value plant_config;  //植物信息
	Json::Value zombie_config;  //僵尸信息
	Json::Value hscore_config;  //历史记录
	Json::Value cproperty_config; //背包信息
	Json::Value shop_config; //商店信息配置

	DataConfig(){ init(); }
	bool init();
	static DataConfig* instance;
public:
	static DataConfig* getInstance();
	void setGameEntityAttr(GameEntity* obj);//根据配置文件设置游戏实体属性
	void setDerivedEntityAttr(DerivedEntity* obj);//根据配置文件设置派生实体属性

	//@hanjie 2017.2.18
	void setAdventureLevelData(ValueMapIntKey *numList, ValueMapIntKey *probList, unsigned short level);//根据配置文件设置游戏冒险模式下指定关卡的基本属性
	void setSurvivalModeData(ValueMapIntKey *numList, ValueMapIntKey *probList);//根据配置文件设置游戏生存模式的基本属性

	//suzhe
	std::list<User*> getUserDataFromConfig();  //读取用户基本信息文件
	void setUserDataToConfig(std::list<User*>);        //写入用户信息到文件
	std::map<std::string, unsigned int> getUserHistoryScoreFromConfig(std::string currentUser);  //读取玩家生成模式历史记录
	void setUserScoreToConfig(std::string,unsigned int point);   //写入玩家一次游戏的分数记录
	std::map<GameEntityType, int> getUserPropertyFromConfig(std::string);  //当前玩家背包信息

	std::map<std::string, std::string> getPlantsMessageFromConfig();   //读取图鉴植物信息
	std::map<std::string, std::string> getZombiesMessageFromConfig();  //读取图鉴僵尸信息

	//hanjie 2017.2.22
	std::list<ShopItem*> getShopItemListFromConfig();//读取商城商品信息配置文件
	// su 2.25
	void setUserPropertyToConfig(std::map<GameEntityType, int> pmap);  //写入当前用户道具信息
	void deleteTargetUserProperty(std::string target_name);  //// 删除我的背包中的某一用户的道具信息

	// 2.26
	std::map<GameEntityType,int> getZombiePoint();   //获取僵尸的分数

};

#endif