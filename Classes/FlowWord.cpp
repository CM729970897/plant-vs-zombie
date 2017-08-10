#include "FlowWord.h"

FlowWord* FlowWord::create() {
	FlowWord* flowWord = new FlowWord();
	flowWord->init();
	/*if(flowWord && flowWord->init()) {
		flowWord->autorelease();
	}
	else {
		CC_SAFE_DELETE(flowWord);
	}*/

	return flowWord;
}

bool FlowWord::init() {
	m_textLab = CCLabelTTF::create("", "Arial", 18);
	m_textLab->setColor(ccc3(255, 0, 0));
	m_textLab->setAnchorPoint(Vec2::ZERO);
	m_textLab->setVisible(false);
//	m_textLab->setHorizontalAlignment(kCCTextAlignmentLeft);
	this->addChild(m_textLab,500);
	return true;
}

void FlowWord::showWord(std::string text, Vec2 pos) {
	m_textLab->setString(text);
	m_textLab->setPosition(pos);
	m_textLab->setVisible(true);
}

void FlowWord::showWordint(int x, Vec2 pos) {
	CCString* text = CCString::createWithFormat("%d",x);
	m_textLab->setString(text->_string);
	m_textLab->setPosition(pos);
	m_textLab->setVisible(true);
}

void FlowWord::flowEnd() {
	/* 动作结束，从父节点中删除自身 */
	m_textLab->setVisible(false);
	m_textLab->removeFromParentAndCleanup(true);
}

