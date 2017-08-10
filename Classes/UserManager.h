#ifndef __USER_MANAGER_H__
#define __USER_MANAGER_H__

#include "cocos2d.h"
#include "User.h"
#include "EntityConst.h"

USING_NS_CC;

//用户管理(单例模式) @hanjie 2017.1.11
class UserManager{
private:
	static UserManager* instance;
	std::list<User*> userList;//所有用户列表
	User* current_user = NULL;//当前用户
	std::map<std::string, unsigned int>pointList;//当前用户的生存模式历史积分列表
	std::map<GameEntityType, int>propertyList;//当前用户的道具列表（种类和数量）

	UserManager();
	~UserManager();
	bool fileRead();//数据文件读取
	bool fileWrite();//数据文件写回
public:
	static UserManager* getInstance();

	bool loadUserData();//加载数据文件的数据进入内存

	/*
	将当前用户转换为参数指定的用户：将current_user对应的数据写回到对应的文件中;
	在userList中查找name指示的用户，更新current_user;从对应的数据文件中将更新后
	的数据调入对应的数据结构。
	*/
	bool switchUser(std::string name);
	/*
	创建一个新用户：首先在userList中查找是否存在与name同名的用户。只有在无同名用
	户时才能继续进行创建；在排除重名之后，创建一个User对象并初始化，创建对应的数
	据文件，将该对象加入到userList表中，最后将current_user设为新创建的用户
	*/
	bool createUser(std::string name);
	/*
	删除一个用户：首先判断name所指示的用户是否存在。只有当存在时才会继续进行删除,
	首先将userList中对应的项删去，再将对应的数据文件全部删去。
	注：当前已登录的用户不能删除自身。
	*/
	bool deleteUser(std::string name);

	bool updateUserProgress();//更新冒险模式进度,每次冒险模式关卡胜利时进行调用

	bool updateUserGold(int delta);//更新用户金币数，每场游戏结束后调用

	unsigned short getUserProgress(){ return current_user->getProgress(); }

	unsigned int getUserGold(){ return current_user->getGold(); }
	
	std::list<User*> getUserList(){ return userList; }
	User* getCurrentUser() { return current_user; }
	std::map<std::string, unsigned int> getHistoryPoint(){return pointList;}
	std::map<GameEntityType, int> getPropList() { return propertyList; }

	//@hanjie 2017.2.22
	bool updateUserProperty(GameEntityType id, int num);
	//@hanjie 2017.2.24
	int getUserPropertyByID(GameEntityType id){ return propertyList[id]; }

	//su 2.26
	void setHistoryPoint(std::string s, unsigned int p) { pointList.insert({s,p}); }

	bool updateUserInfo();
};

#endif