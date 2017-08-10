#include "UserManager.h"
#include "DataConfig.h"

UserManager* UserManager::instance = NULL;

UserManager* UserManager::getInstance(){
	if (instance == NULL){
		instance = new UserManager();
	}
	return instance;
}

UserManager::UserManager(){
}

bool UserManager::fileRead(){
	DataConfig* config = DataConfig::getInstance();
	userList=config->getUserDataFromConfig();   //�û��б�

	for (auto iter = userList.begin(); iter != userList.end(); iter++){
		if ((*iter)->getTag() == true)
		{
			current_user = *iter;
			break;
		}
	}
	 pointList = config->getUserHistoryScoreFromConfig(current_user->getName());   //��ǰ�û���ʷ��¼

	propertyList = config->getUserPropertyFromConfig(current_user->getName());  //��ȡ��ǰ�û�������Ϣ

	return true;
}

bool UserManager::fileWrite(){
	DataConfig::getInstance()->setUserDataToConfig(userList);  //д�û���Ϣ
	return true;
}

bool UserManager::loadUserData(){
	fileRead();
	return true;
}

bool UserManager::switchUser(std::string name){
	if (name.empty()){
		return false;
	}

	User* target_user = NULL;
	for (auto userObj : userList){
		if (userObj->getName()==name){//�ҵ���Ӧ���û�
			target_user = userObj;
		}
	}
	if (target_user == NULL){//�������ڴ�ת�����û�
		return false;
	}


	// su  2.25  �޸�
	for (auto userObj : userList){
		if (userObj->getTag() == true){
			userObj->setTag(false);
		}
	}//���������û��������ļ��������ȼ�

	target_user->setTag(true);
	current_user = target_user;

	fileWrite();   //�л��û�������ļ�
	//fileRead();
	propertyList = DataConfig::getInstance()->getUserPropertyFromConfig(current_user->getName()); //�л�����ǰ�û�������Ϣ
	pointList = DataConfig::getInstance()->getUserHistoryScoreFromConfig(current_user->getName());  //�л�����ǰ�û�����ʷ��¼

	return true;
}

bool UserManager::createUser(std::string name){
	if (name.empty()){
		return false;
	}

	for (auto userObj : userList){
		if (userObj->getName() == name){
			return false;
		}
	}//������ͬ���û��򲻿ɽ��д���

	auto user = new User();//�������û�
	user->setName(name);
	user->setProgress(1);
	user->setTag(1);//�����û��������ļ��������ȼ���Ϊ���
	user->setGold(0);

	for (auto userObj : userList){
		if (userObj->getTag() == true){
			userObj->setTag(false);
		}
	}//���������û��������ļ��������ȼ�

	userList.push_back(user);//������û�
	current_user = user;

	//Todo::��Ӷ�Ӧ�û������ļ������ɴ���
	fileWrite();   //�����û�������ļ�
	propertyList = DataConfig::getInstance()->getUserPropertyFromConfig(current_user->getName()); //�л�����ǰ�û�������Ϣ
	pointList = DataConfig::getInstance()->getUserHistoryScoreFromConfig(current_user->getName());  //�л�����ǰ�û�����ʷ��¼
	return true;
}

bool UserManager::deleteUser(std::string name){

	User* target_user = NULL;
	for (auto userObj : userList){
		if (userObj->getName() == name){//�ҵ���Ӧ���û�
			target_user = userObj;
			break;
		}
	}
	if (target_user == NULL){//�������ڴ�ת�����û�
		return false;
	}

	if (target_user == current_user){//����ɾ�����û�Ϊ��ǰ�û�����ɾ��ʧ��
		return false;
	}

	userList.remove(target_user);  
	//�ҵı����е���Ӧ�û���Ϣɾ��
	DataConfig::getInstance()->deleteTargetUserProperty(target_user->getName());
	

	fileWrite();   //ɾ���û�������ļ�

	return true;
}

bool UserManager::updateUserProgress(){
	if (current_user == NULL){
		return false;
	}

	if (current_user->getProgress() == 5){//��ǰ�û���ͨ��
		current_user->setProgress(1);//�û���������
	}
	else{
		current_user->setProgress(current_user->getProgress() + 1);//�û���������
	}

	return true;
}

bool UserManager::updateUserInfo()
{
	for (auto user : userList)
	{
		if (user == current_user)
		{
			user->setGold(current_user->getGold());
			user->setProgress(current_user->getProgress());
			break;
		}
	}
	DataConfig::getInstance()->setUserDataToConfig(userList);
	return true;
}

bool UserManager::updateUserGold(int delta){
	if (current_user == NULL){
		return false;
	}

	current_user->setGold(current_user->getGold() + delta);

	return true;
}

bool UserManager::updateUserProperty(GameEntityType id, int num){
	if (current_user == NULL){
		return false;
	}
	propertyList[id] += num;
	// su 2.25 ���±�������
	DataConfig::getInstance()->setUserPropertyToConfig(propertyList);

	return true;
}