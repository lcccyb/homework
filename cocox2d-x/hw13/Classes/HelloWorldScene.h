#pragma once
#include "cocos2d.h"
using namespace cocos2d;

class HelloWorld : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

	void HelloWorld::move(char ch);

	void HelloWorld::action(char cid);

	void HelloWorld::Time(float dt);

	void HelloWorld::createMonster(float dt);

	void HelloWorld::hitByMonster(float dt);

	bool HelloWorld::attackMonster();

	void HelloWorld::stop(float dt);

	void HelloWorld::deadCallback();
        
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);
private:
	cocos2d::Sprite* player;
	cocos2d::Vector<SpriteFrame*> attack;
	cocos2d::Vector<SpriteFrame*> dead;
	cocos2d::Vector<SpriteFrame*> run;
	cocos2d::Vector<SpriteFrame*> idle;
	cocos2d::Size visibleSize;
	cocos2d::Vec2 origin;
	cocos2d::Label* time;
	cocos2d::Label* score;
	int dtime;
	int dscore;
	bool temp;
	bool isDead = false;
	bool isAction;
	cocos2d::ProgressTimer* pT;
};
