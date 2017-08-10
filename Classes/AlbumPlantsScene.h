#ifndef __ALBUM_PLANTS_SCENE_H__
#define __ALBUM_PLANTS_SCENE_H__

#include "cocos2d.h"
#include "FlowWord.h"

//Ö²ÎïÍ¼¼øË÷Òý³¡¾°
//lishi 2017.2.13
class AlbumPlantsScene : public cocos2d::Layer{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();
	void albumIndex(Ref*);
	void mainMenu(Ref*);

	//lishi 2017.2.16
	void display_peaShooter(Ref*);
	void display_sunFlower(Ref*);
	void display_wallNut(Ref*);
	void display_cherryBomb(Ref*);
	void display_jalapeno(Ref*);
	//su 2.28
	void display_bamBoo(Ref*);


	CREATE_FUNC(AlbumPlantsScene);
private:
	std::map<std::string, std::string> plantMap;
	FlowWord* word;
	int audioID;
};

#endif