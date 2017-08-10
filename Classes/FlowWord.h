#ifndef _FlowWord_H_
#define _FlowWord_H_

#include "cocos2d.h"
USING_NS_CC;

class FlowWord : public CCNode {
public:
	static FlowWord* create();
	bool init();

public:
	void showWord(std::string text, Vec2 pos);
	void showWordint(int x, Vec2 pos);
	CCLabelTTF* getLableTTF() { return m_textLab; }
	void flowEnd();
private:
	CCLabelTTF* m_textLab;
};

#endif