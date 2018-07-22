#ifndef _GameOver_H_
#define _GameOver_H_

#include "cocos2d.h"
USING_NS_CC;

class GameOver :public Layer{
public:
	static Scene* createScene();
	virtual bool init();
	
	void startMenu(Ref* ref);  
	void exitMenu(Ref* ref);    
          
	CREATE_FUNC(GameOver);
};

#endif