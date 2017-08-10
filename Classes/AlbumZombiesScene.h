#ifndef __ALBUM_ZOMBIES_SCENE_H__
#define __ALBUM_ZOMBIES_SCENE_H__

#include "cocos2d.h"
#include "FlowWord.h"
#include "SimpleAudioEngine.h"

//½©Ê¬Í¼¼øË÷Òý³¡¾°
//lishi 2017.2.13
class AlbumZombiesScene : public cocos2d::Layer{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();
	void albumIndex(Ref*);
	void mainMenu(Ref*);

	//lishi 2017.2.17
	void display_zombie(Ref*);
	void display_flagZombie(Ref*);
	void display_coneheadZombie(Ref*);
	void display_bucketheadZombie(Ref*);

	CREATE_FUNC(AlbumZombiesScene);
private:
	std::map<std::string, std::string> zombieMap;
	FlowWord* word;
	int audioID;
};

#endif