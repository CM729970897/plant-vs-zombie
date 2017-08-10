#ifndef __USER_H__
#define __USER_H__

#include <string.h>
#include "cocos2d.h"

USING_NS_CC;

//用户实体类 @hanjie 2017.1.11
class User{
private:
	std::string name;//用户昵称
	unsigned short progress;//冒险模式当前进度
	unsigned int gold;//当前持有的金币数
	bool tag;//标识当前用户，为true表示优先加载
public:
	User(){};
	~User(){};
	void setName(std::string name){ this->name=name; }
	std::string getName(){ return name; }
	void setProgress(unsigned short progress){ this->progress = progress; }
	unsigned short getProgress(){ return progress; }
	void setGold(unsigned int gold){ this->gold = gold; }
	unsigned int getGold(){ return gold; }
	void setTag(bool tag){ this->tag = tag; }
	bool getTag(){ return tag; }
};

#endif