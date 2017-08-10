#include "DataConfig.h"
#include "UserManager.h"

USING_NS_CC;

DataConfig* DataConfig::instance = NULL;

DataConfig* DataConfig::getInstance(){
	if (instance == NULL){
		instance = new DataConfig();
	}
	return instance;
}

bool DataConfig::init(){
	std::string entity_file = FileUtils::getInstance()->getStringFromFile("game/dataConfig/EntityDataConfig.json");
	std::string game_file = FileUtils::getInstance()->getStringFromFile("game/dataConfig/GameDataConfig.json");
	std::string user_file = FileUtils::getInstance()->getStringFromFile("game/dataConfig/UserList.json");
	std::string plant_file = FileUtils::getInstance()->getStringFromFile("game/dataConfig/PlantIntroduction.json");
	std::string zombie_file = FileUtils::getInstance()->getStringFromFile("game/dataConfig/ZombieIntroduction.json");
	std::string hscore_file = FileUtils::getInstance()->getStringFromFile("game/dataConfig/Point.json");
	std::string cproperty_file = FileUtils::getInstance()->getStringFromFile("game/dataConfig/PropertyList.json");
	std::string shop_file = FileUtils::getInstance()->getStringFromFile("game/dataConfig/Shop.json");
	bool bRet = true;
	bRet = bRet && reader.parse(entity_file, entity_config, false);
	bRet = bRet && reader.parse(game_file, game_config, false);
	bRet = bRet && reader.parse(user_file, user_config, false);
	bRet = bRet && reader.parse(plant_file, plant_config, false);
	bRet = bRet && reader.parse(zombie_file, zombie_config, false);
	bRet = bRet && reader.parse(shop_file, shop_config, false);
	bRet = bRet && reader.parse(hscore_file, hscore_config, false);
	bRet = bRet && reader.parse(cproperty_file, cproperty_config, false);
	return bRet;

}

void DataConfig::setGameEntityAttr(GameEntity* obj){
	int count = entity_config["game_entity"]["data"].size();
	for (int i = 0; i < count; i++){
		if (obj->getType() == entity_config["game_entity"]["data"][i]["id"].asInt()){//若待获取数据的类型相匹配
			if (obj->getType() > GameEntityType::begin_plant && obj->getType() < GameEntityType::end_plant){//植物数据加载
				obj->setBlood(entity_config["game_entity"]["data"][i]["blood"].asInt());
				obj->setAttack(entity_config["game_entity"]["data"][i]["attack"].asInt());
				obj->setSpeed(entity_config["game_entity"]["data"][i]["speed"].asInt());
				obj->setCost(entity_config["game_entity"]["data"][i]["cost"].asInt());
				obj->setPoint(entity_config["game_entity"]["data"][i]["point"].asInt());
				obj->setAttackExtra(obj->getPoint());
			}
			else if (obj->getType() > GameEntityType::begin_zombie && obj->getType() < GameEntityType::end_zombie){//僵尸数据加载
				obj->setBlood(entity_config["game_entity"]["data"][i]["blood"].asInt());
				obj->setAttack(entity_config["game_entity"]["data"][i]["attack"].asInt());
				obj->setSpeed(entity_config["game_entity"]["data"][i]["speed"].asInt());
				obj->setCost(entity_config["game_entity"]["data"][i]["cost"].asInt());
				obj->setPoint(entity_config["game_entity"]["data"][i]["point"].asInt());
				obj->setAttackExtra(obj->getAttack());
			}
			break;
		}
	}
}

void DataConfig::setDerivedEntityAttr(DerivedEntity* obj){
	int count = entity_config["derived_entity"]["data"].size();
	for (int i = 0; i < count; i++){
		if (obj->getType() == entity_config["derived_entity"]["data"][i]["id"].asInt()){//若待获取数据的类型相匹配
			obj->setPower(entity_config["derived_entity"]["data"][i]["power"].asInt());
			break;
		}
	}
}

void DataConfig::setAdventureLevelData(ValueMapIntKey* numList, ValueMapIntKey* probList, unsigned short level){
	char level_str[10];
	sprintf(level_str, "level_%d", level);
	int prob_num = game_config["adventure_mode"][level_str]["probList"].size();
	for (int i = 0; i < prob_num; i++){
		auto prob = game_config["adventure_mode"][level_str]["probList"][i]["prob"].asInt();
		(*probList)[prob] = game_config["adventure_mode"][level_str]["probList"][i]["id"].asInt();
	}
	int num_num = game_config["adventure_mode"][level_str]["numList"].size();
	for (int i = 0; i < num_num; i++){
		auto feq = game_config["adventure_mode"][level_str]["numList"][i]["feq"].asInt();
		(*numList)[feq] = game_config["adventure_mode"][level_str]["numList"][i]["num"].asInt();
	}
	return;
}

void DataConfig::setSurvivalModeData(ValueMapIntKey* numList, ValueMapIntKey* probList){
	int prob_num = game_config["survival_mode"]["probList"].size();
	for (int i = 0; i < prob_num; i++){
		auto prob = game_config["survival_mode"]["probList"][i]["prob"].asInt();
		(*probList)[prob] = game_config["survival_mode"]["probList"][i]["id"].asInt();
	}
	int num_num = game_config["survival_mode"]["numList"].size();
	for (int i = 0; i < num_num; i++){
		auto feq = game_config["survival_mode"]["numList"][i]["feq"].asInt();
		(*numList)[feq] = game_config["survival_mode"]["numList"][i]["num"].asInt();
	}
	return;
}

std::list<User*> DataConfig::getUserDataFromConfig()
{
	int num = user_config["user"].size();
	std::list<User*> userlist;
	for (int i = 0; i < num; i++){
		User* user = new User();
		user->setName(user_config["user"][i]["name"].asCString());
		user->setProgress(user_config["user"][i]["progress"].asInt());
		user->setGold(user_config["user"][i]["gold"].asInt());
		user->setTag(user_config["user"][i]["tag"].asBool());
		userlist.push_back(user);
	}
	return userlist;
}

void DataConfig::setUserDataToConfig(std::list<User*> ulist)
{
	Json::Value user_configW;
	int num = ulist.size();
	auto it = ulist.begin();
	for (int i = 0; i < num; i++,it++)
	{
		user_configW["user"][i]["name"] = (*it)->getName();
		user_configW["user"][i]["progress"] = (*it)->getProgress();
		user_configW["user"][i]["gold"] = (*it)->getGold();
		user_configW["user"][i]["tag"] = (*it)->getTag();
	}
	std::string user_file = writer.write(user_configW);
	FILE* file = fopen("game/dataConfig/UserList.json", "w");
	fprintf(file,user_file.c_str());
	fclose(file);
}

std::map<std::string, std::string> DataConfig::getPlantsMessageFromConfig()                                         
{
	int num = plant_config["plant"].size();
	std::map<std::string, std::string> pmap;
 	for (int i = 0; i < num; i++)
		pmap.insert({ plant_config["plant"][i]["name"].asCString(), plant_config["plant"][i]["content"].asCString() });
	return pmap;
}

std::map<std::string, std::string> DataConfig::getZombiesMessageFromConfig()
{
	
	std::map<std::string, std::string> zmap;
	int num = zombie_config["zombie"].size();
	for (int i = 0; i < num; i++)
		zmap.insert({ zombie_config["zombie"][i]["name"].asCString(), zombie_config["zombie"][i]["content"].asCString() });
	return zmap;
}

std::map<std::string, unsigned int> DataConfig::getUserHistoryScoreFromConfig(std::string currentUser)
{
	std::map<std::string, unsigned int> smap;
	int num = hscore_config[currentUser].size();
	for (int i = 0; i <num; i++)
		smap.insert({hscore_config[currentUser][i]["time"].asString(),hscore_config[currentUser][i]["point"].asInt()});
	return smap;
}

void DataConfig::setUserScoreToConfig(std::string text, unsigned int point)
{
	

	UserManager* usermanager = UserManager::getInstance();
	std::string currentUser = usermanager->getCurrentUser()->getName();
	Json::Value hscore_configW;
	Json::Value array=hscore_config;

	hscore_configW["time"] =text;
	hscore_configW["point"] =point;

	array[currentUser].append(hscore_configW);

	std::string hscore_fileW = writer.write(array);
	FILE* file = fopen("game/dataConfig/Point.json", "w");
	fprintf(file, hscore_fileW.c_str());
	fclose(file);

}

std::map<GameEntityType, int> DataConfig::getUserPropertyFromConfig(std::string currentUser)
{
	std::map<GameEntityType, int> pmap;
	int num = cproperty_config[currentUser].size();
	for (int i = 0; i < num; i++)
		pmap.insert({ (GameEntityType)cproperty_config[currentUser][i]["id"].asInt(), cproperty_config[currentUser][i]["num"].asInt() });
	return pmap;
}
std::list<ShopItem*> DataConfig::getShopItemListFromConfig(){
	int num = shop_config["itemList"].size();
	std::list<ShopItem*> itemlist;
	for (int i = 0; i < num; i++){
		ShopItem* item = new ShopItem();
		item->setID((GameEntityType)shop_config["itemList"][i]["id"].asInt());
		item->setCost(shop_config["itemList"][i]["cost"].asInt());
		item->setNum(shop_config["itemList"][i]["num"].asInt());
		item->setDescription(shop_config["itemList"][i]["description"].asString());
		itemlist.push_back(item);
	}
	return itemlist;
}

void DataConfig::setUserPropertyToConfig(std::map<GameEntityType, int> pmap)    //!!!!!!
{
	UserManager* usermanager = UserManager::getInstance();
	std::string currentUser = usermanager->getCurrentUser()->getName();
	int num = pmap.size();
	auto it = pmap.begin();
	for (int i = 0; i < num; i++, it++)
	{
		cproperty_config[currentUser][i]["id"] = it->first;
		cproperty_config[currentUser][i]["num"] = it->second;
	}

	std::string cproperty_fileW = writer.write(cproperty_config);
	FILE* file = fopen("game/dataConfig/PropertyList.json", "w");
	fprintf(file, cproperty_fileW.c_str());
	fclose(file);
}

void DataConfig::deleteTargetUserProperty(std::string target_name)
{
	cproperty_config.removeMember(target_name);
	std::string cproperty_fileW = writer.write(cproperty_config);
	FILE* file = fopen("game/dataConfig/PropertyList.json", "w");
	fprintf(file, cproperty_fileW.c_str());
	fclose(file);
}

std::map<GameEntityType, int> DataConfig::getZombiePoint()
{
	int count = entity_config["game_entity"]["data"].size();
	std::map<GameEntityType, int> pointMap;
	for (int i = 0; i < count; i++)
	{
		int type = entity_config["game_entity"]["data"][i]["id"].asInt();
		if (type>GameEntityType::begin_zombie&&type < GameEntityType::end_zombie)
		{
			pointMap.insert({ (GameEntityType)entity_config["game_entity"]["data"][i]["id"].asInt(), entity_config["game_entity"]["data"][i]["point"].asInt() });
		}
	}
	return pointMap;
}