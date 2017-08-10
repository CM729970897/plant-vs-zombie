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

//��Ϸ�������ö�ȡ
//@hanjie 2017.2.17
class DataConfig {
private:
	Json::Reader reader;
	Json::FastWriter writer;
	Json::Value entity_config;//ʵ���������
	Json::Value game_config;//��Ϸ��������
	Json::Value user_config;  //�û���Ϣ����
	Json::Value plant_config;  //ֲ����Ϣ
	Json::Value zombie_config;  //��ʬ��Ϣ
	Json::Value hscore_config;  //��ʷ��¼
	Json::Value cproperty_config; //������Ϣ
	Json::Value shop_config; //�̵���Ϣ����

	DataConfig(){ init(); }
	bool init();
	static DataConfig* instance;
public:
	static DataConfig* getInstance();
	void setGameEntityAttr(GameEntity* obj);//���������ļ�������Ϸʵ������
	void setDerivedEntityAttr(DerivedEntity* obj);//���������ļ���������ʵ������

	//@hanjie 2017.2.18
	void setAdventureLevelData(ValueMapIntKey *numList, ValueMapIntKey *probList, unsigned short level);//���������ļ�������Ϸð��ģʽ��ָ���ؿ��Ļ�������
	void setSurvivalModeData(ValueMapIntKey *numList, ValueMapIntKey *probList);//���������ļ�������Ϸ����ģʽ�Ļ�������

	//suzhe
	std::list<User*> getUserDataFromConfig();  //��ȡ�û�������Ϣ�ļ�
	void setUserDataToConfig(std::list<User*>);        //д���û���Ϣ���ļ�
	std::map<std::string, unsigned int> getUserHistoryScoreFromConfig(std::string currentUser);  //��ȡ�������ģʽ��ʷ��¼
	void setUserScoreToConfig(std::string,unsigned int point);   //д�����һ����Ϸ�ķ�����¼
	std::map<GameEntityType, int> getUserPropertyFromConfig(std::string);  //��ǰ��ұ�����Ϣ

	std::map<std::string, std::string> getPlantsMessageFromConfig();   //��ȡͼ��ֲ����Ϣ
	std::map<std::string, std::string> getZombiesMessageFromConfig();  //��ȡͼ����ʬ��Ϣ

	//hanjie 2017.2.22
	std::list<ShopItem*> getShopItemListFromConfig();//��ȡ�̳���Ʒ��Ϣ�����ļ�
	// su 2.25
	void setUserPropertyToConfig(std::map<GameEntityType, int> pmap);  //д�뵱ǰ�û�������Ϣ
	void deleteTargetUserProperty(std::string target_name);  //// ɾ���ҵı����е�ĳһ�û��ĵ�����Ϣ

	// 2.26
	std::map<GameEntityType,int> getZombiePoint();   //��ȡ��ʬ�ķ���

};

#endif