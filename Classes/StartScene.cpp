#include "StartScene.h"
#include "MainMenuScene.h"
#include "SimpleAudioEngine.h"
#include "UserManager.h"


USING_NS_CC;

Scene* StartScene::createScene()
{
    auto scene = Scene::create();
	auto layer = StartScene::create();
    scene->addChild(layer);
    return scene;
}

bool StartScene::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    
	//suzhe  ¼ÓÔØÊý¾Ý
	UserManager::getInstance()->loadUserData();

    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto origin = Director::getInstance()->getVisibleOrigin();

    auto background = Sprite::create("game/welcomelayer/titlescreen.png");
	background->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    this->addChild(background, 0);

	auto lawn = Sprite::create("game/welcomelayer/down.png");
	lawn->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y - 200));
	this->addChild(lawn, 0);

	auto scrollgrass = Sprite::create("game/welcomelayer/scrollgrass.png");
	scrollgrass->setPosition(Vec2(visibleSize.width / 2 - 180 + origin.x, visibleSize.height / 2 + origin.y - 150));
	auto rotateBy = RotateBy::create(3, 2 * 360);
	auto scaleBy = ScaleBy::create(3, 0.0f);
	auto spawn = Spawn::create(rotateBy, scaleBy, NULL);
	auto removeFunc = CallFuncN::create(this,callfuncN_selector(StartScene::removeScrollGrass));
	auto rotateScaleSequence = Sequence::create(spawn,removeFunc,NULL);
	scrollgrass->runAction(rotateScaleSequence);
	this->addChild(scrollgrass, 0);
	auto moveTo = MoveTo::create(3, Vec2(visibleSize.width / 2 + 150 + origin.x, visibleSize.height / 2 + origin.y - 180));
	auto moveSequence = Sequence::create(moveTo, NULL);
	scrollgrass->runAction(moveSequence);

	auto grass = Sprite::create("game/welcomelayer/grass.png");
	auto progress = ProgressTimer::create(grass);
	grass->setPosition(Vec2(visibleSize.width / 2 + origin.x - 10, visibleSize.height / 2 + origin.y - 175));
	progress->setType(ProgressTimer::Type::BAR);
	auto progressTo = ProgressFromTo::create(3,0,100);
	progress->setMidpoint(Point::ZERO);
	progress->runAction(progressTo);
	this->addChild(grass);

	flag = true;
	schedule(schedule_selector(StartScene::replaceScene), 3.0f);
    return true;
}

void StartScene::removeScrollGrass(cocos2d::Node* sprite){
	sprite->removeFromParent();
}

void StartScene::replaceScene(float a){
	if (flag){
		unschedule(schedule_selector(StartScene::replaceScene));
		auto scene = MainMenuScene::createScene();
		//auto crossFade = TransitionCrossFade::create(1, scene);
		Director::getInstance()->replaceScene(scene);
	}
	
}
