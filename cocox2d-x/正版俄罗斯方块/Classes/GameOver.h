#ifndef _GameOver_H_
#define _GameOver_H_

#include "cocos2d.h"
USING_NS_CC;

class GameOver :public Layer{
public:
	static Scene* createScene();
	virtual bool init();
	
	void startMenu(Ref* ref);   //���¿�ʼ��ť
	void exitMenu(Ref* ref);    //�˳���Ϸ��ť
	void FsRecord();            //������¼

	CREATE_FUNC(GameOver);
};

#endif