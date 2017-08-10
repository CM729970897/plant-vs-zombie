#include"cocos2d.h"
#include"EntityConst.h"

USING_NS_CC;


class OptPropUI: public Layer
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();
	bool onTouchBegan(Touch* a,Event* b);
	void onTouchMoved(Touch* a,Event* b);
	void onTouchEnded(Touch* a,Event* b);
	void menuCloseCallback(Ref* pSender);
	MenuItemImage* menuItem;
	
	void remove();
	OptPropUI();
	~OptPropUI();
	CREATE_FUNC(OptPropUI);
private:
	bool mode;
	int sumPlant;
	int propCount;
	int propSum;
	int optValue[5][5];
	int prop[5][5];
	bool StartGame;
	OPT start[7];   //µÀ¾ßÀ¸
	int audioID;

};