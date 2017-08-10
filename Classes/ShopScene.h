#ifndef __SHOP_SCENE_H__
#define __SHOP_SCENE_H__

#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "ShopItem.h"
#include "BagScene.h"


//…ÃµÍ≥°æ∞
//tangsai 2017.2.14
class ShopScene : public cocos2d::Layer{
private:
	std::list<ShopItem*>itemList;
	ShopItem* currentItem = NULL;
	int audioID;
	FlowWord* word;
	FlowWord* gold;
public:
	static cocos2d::Scene* createScene();

	virtual bool init();
	void menuCloseCallback(cocos2d::Ref* pSender);
	void display_Torchwood(Ref*);
	void buy(Ref*);

	CREATE_FUNC(ShopScene);
	//su 2.25
	void showCurrentShopItem(int id);
	void display_Iceshroom(Ref*);
};

#endif