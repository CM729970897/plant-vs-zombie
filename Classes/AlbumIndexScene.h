#ifndef __ALBUM_INDEX_SCENE_H__
#define __ALBUM_INDEX_SCENE_H__

#include "cocos2d.h"

//ÓÎÏ·Í¼¼øË÷Òý³¡¾°
//lishi 2017.2.13
class AlbumIndexScene : public cocos2d::Layer{
public:
	~AlbumIndexScene(){};
	static cocos2d::Scene* createScene();

	virtual bool init();
	void plantIndex(Ref*);
	void zombieIndex(Ref*);
	void mainMenu(Ref*);

	CREATE_FUNC(AlbumIndexScene);
private:
	int audioID;
};

#endif