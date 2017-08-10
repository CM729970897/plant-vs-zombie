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
	userList=config->getUserDataFromConfig();   //用户列表

	for (auto iter = userList.begin(); iter != userList.end(); iter++){
		if ((*iter)->getTag() == true)
		{
			current_user = *iter;
			break;
		}
	}
	 pointList = config->getUserHistoryScoreFromConfig(current_user->getName());   //当前用户历史记录

	propertyList = config->getUserPropertyFromConfig(current_user->getName());  //获取当前用户背包信息

	return true;
}

bool UserManager::fileWrite(){
	DataConfig::getInstance()->setUserDataToConfig(userList);  //写用户信息
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
		if (userObj->getName()==name){//找到相应的用户
			target_user = userObj;
		}
	}
	if (target_user == NULL){//若不存在待转换的用户
		return false;
	}


	// su  2.25  修改
	for (auto userObj : userList){
		if (userObj->getTag() == true){
			userObj->setTag(false);
		}
	}//降低其他用户的数据文件加载优先级

	target_user->setTag(true);
	current_user = target_user;

	fileWrite();   //切换用户后更新文件
	//fileRead();
	propertyList = DataConfig::getInstance()->getUserPropertyFromConfig(current_user->getName()); //切换到当前用户道具信息
	pointList = DataConfig::getInstance()->getUserHistoryScoreFromConfig(current_user->getName());  //切换到当前用户的历史记录

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
	}//若存在同名用户则不可进行创建

	auto user = new User();//创建新用户
	user->setName(name);
	user->setProgress(1);
	user->setTag(1);//将新用户的数据文件加载优先级设为最高
	user->setGold(0);

	for (auto userObj : userList){
		if (userObj->getTag() == true){
			userObj->setTag(false);
		}
	}//降低其他用户的数据文件加载优先级

	userList.push_back(user);//添加新用户
	current_user = user;

	//Todo::添加对应用户数据文件的生成代码
	fileWrite();   //创建用户后更新文件
	propertyList = DataConfig::getInstance()->getUserPropertyFromConfig(current_user->getName()); //切换到当前用户道具信息
	pointList = DataConfig::getInstance()->getUserHistoryScoreFromConfig(current_user->getName());  //切换到当前用户的历史记录
	return true;
}

bool UserManager::deleteUser(std::string name){

	User* target_user = NULL;
	for (auto userObj : userList){
		if (userObj->getName() == name){//找到相应的用户
			target_user = userObj;
			break;
		}
	}
	if (target_user == NULL){//若不存在待转换的用户
		return false;
	}

	if (target_user == current_user){//若待删除的用户为当前用户，则删除失败
		return false;
	}

	userList.remove(target_user);  
	//我的背包中的相应用户信息删除
	DataConfig::getInstance()->deleteTargetUserProperty(target_user->getName());
	

	fileWrite();   //删除用户后更新文件

	return true;
}

bool UserManager::updateUserProgress(){
	if (current_user == NULL){
		return false;
	}

	if (current_user->getProgress() == 5){//当前用户已通关
		current_user->setProgress(1);//用户进度重置
	}
	else{
		current_user->setProgress(current_user->getProgress() + 1);//用户进度自增
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
	// su 2.25 更新背包数据
	DataConfig::getInstance()->setUserPropertyToConfig(propertyList);

	return true;
}