#ifndef __USER_HISTORYSCORE_H__
#define __USER_HISTORYSCORE_H__

#include "cocos2d.h"
#include"cocos-ext.h"

USING_NS_CC;
USING_NS_CC_EXT;
//定义生存模式个人历史记录
class UserHistoryScoreUI : public cocos2d::Layer, public TableViewDataSource, public TableViewDelegate
{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
	void onClose(Ref*);

	CREATE_FUNC(UserHistoryScoreUI);
	virtual void scrollViewDidScroll(ScrollView* view) {};
	virtual void scrollViewDidZoom(ScrollView* view) {};
	virtual void tableCellTouched(TableView* table, TableViewCell* cell);
	virtual Size tableCellSizeForIndex(TableView *table, ssize_t idx);
	virtual TableViewCell* tableCellAtIndex(TableView *table, ssize_t idx);
	virtual ssize_t numberOfCellsInTableView(TableView *table);

	virtual void tableCellUnhighlight(TableView* table, TableViewCell* cell);
	virtual void tableCellHighlight(TableView* table, TableViewCell* cell);
	virtual bool onTouchBegan(Touch* touch, Event* event);
	virtual void onTouchMoved(Touch* touch, Event* event);
	virtual void onTouchEnded(Touch* touch, Event* event);

	std::string  getScoreAtIndex(std::map<std::string, unsigned int>umap, ssize_t idx);
private:
	std::map<std::string,unsigned int> scoreMap;
	int cellNum;
};

#endif __USER_HISTORYSCORE_H__
