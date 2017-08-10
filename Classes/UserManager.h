#ifndef __USER_MANAGER_H__
#define __USER_MANAGER_H__

#include "cocos2d.h"
#include "User.h"
#include "EntityConst.h"

USING_NS_CC;

//�û�����(����ģʽ) @hanjie 2017.1.11
class UserManager{
private:
	static UserManager* instance;
	std::list<User*> userList;//�����û��б�
	User* current_user = NULL;//��ǰ�û�
	std::map<std::string, unsigned int>pointList;//��ǰ�û�������ģʽ��ʷ�����б�
	std::map<GameEntityType, int>propertyList;//��ǰ�û��ĵ����б������������

	UserManager();
	~UserManager();
	bool fileRead();//�����ļ���ȡ
	bool fileWrite();//�����ļ�д��
public:
	static UserManager* getInstance();

	bool loadUserData();//���������ļ������ݽ����ڴ�

	/*
	����ǰ�û�ת��Ϊ����ָ�����û�����current_user��Ӧ������д�ص���Ӧ���ļ���;
	��userList�в���nameָʾ���û�������current_user;�Ӷ�Ӧ�������ļ��н����º�
	�����ݵ����Ӧ�����ݽṹ��
	*/
	bool switchUser(std::string name);
	/*
	����һ�����û���������userList�в����Ƿ������nameͬ�����û���ֻ������ͬ����
	��ʱ���ܼ������д��������ų�����֮�󣬴���һ��User���󲢳�ʼ����������Ӧ����
	���ļ������ö�����뵽userList���У����current_user��Ϊ�´������û�
	*/
	bool createUser(std::string name);
	/*
	ɾ��һ���û��������ж�name��ָʾ���û��Ƿ���ڡ�ֻ�е�����ʱ�Ż��������ɾ��,
	���Ƚ�userList�ж�Ӧ����ɾȥ���ٽ���Ӧ�������ļ�ȫ��ɾȥ��
	ע����ǰ�ѵ�¼���û�����ɾ������
	*/
	bool deleteUser(std::string name);

	bool updateUserProgress();//����ð��ģʽ����,ÿ��ð��ģʽ�ؿ�ʤ��ʱ���е���

	bool updateUserGold(int delta);//�����û��������ÿ����Ϸ���������

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