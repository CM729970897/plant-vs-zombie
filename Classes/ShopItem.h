#ifndef __SHOP_ITEM_H__
#define __SHOP_ITEM_H__

#include "cocos2d.h"
#include "EntityConst.h"

USING_NS_CC;

class ShopItem{
private:
	GameEntityType id;
	int cost;
	int num;
	std::string description;
public:
	void setID(GameEntityType id){ this->id = id; }
	void setCost(int cost){ this->cost = cost; }
	void setNum(int num){ this->num = num; }
	void setDescription(std::string description){ this->description = description; }

	GameEntityType getID(){ return id; }
	int getCost(){ return cost; }
	int getNum(){ return num; }
	std::string getDescription(){ return description; }

};

#endif