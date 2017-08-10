#ifndef __USER_H__
#define __USER_H__

#include <string.h>
#include "cocos2d.h"

USING_NS_CC;

//�û�ʵ���� @hanjie 2017.1.11
class User{
private:
	std::string name;//�û��ǳ�
	unsigned short progress;//ð��ģʽ��ǰ����
	unsigned int gold;//��ǰ���еĽ����
	bool tag;//��ʶ��ǰ�û���Ϊtrue��ʾ���ȼ���
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