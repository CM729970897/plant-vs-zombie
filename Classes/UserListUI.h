#ifndef __USERLIST_UI_H__
#define __USERLIST_UI_H__
#include"cocos2d.h"
#include"cocos-ext.h"
#include"FlowWord.h"
#include"User.h"
#include "UserManager.h"


USING_NS_CC;
USING_NS_CC_EXT;

class UserListUI :public cocos2d::Layer,public TableViewDataSource,public TableViewDelegate
{
public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	void onOk(Ref*);
	void onCancel(Ref*);
	void onCreate(Ref*);
	void onDelete(Ref*);
	virtual bool onTouchBegan(Touch* touch, Event* event);
	virtual void onTouchMoved(Touch* touch, Event* event);
	virtual void onTouchEnded(Touch* touch, Event* event);
	CREATE_FUNC(UserListUI);
	virtual void scrollViewDidScroll(ScrollView* view) {};
	virtual void scrollViewDidZoom(ScrollView* view) {};
	virtual void tableCellTouched(TableView* table, TableViewCell* cell);
	virtual Size tableCellSizeForIndex(TableView *table, ssize_t idx);
	virtual TableViewCell* tableCellAtIndex(TableView *table, ssize_t idx);
	virtual ssize_t numberOfCellsInTableView(TableView *table);

	virtual void tableCellUnhighlight(TableView* table, TableViewCell* cell);
	virtual void tableCellHighlight(TableView* table, TableViewCell* cell);

	User* getUserAtIndex(std::list<User*>ulist, ssize_t idx);
private:
	Size visibleSize;
	Vec2 p1;
	std::list<User*> contentList;
	FlowWord* word;
	ssize_t index=-1;
	TableView* tableView;
	int cellNum;
	UserManager* usermanager;

};
#endif __USERLIST_UI_H__