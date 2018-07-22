#include "GameOver.h"
#include "GameScene.h"
#include <ui/UIImageView.h>
#include "SimpleAudioEngine.h"

USING_NS_CC;
using namespace CocosDenshion;

Scene* GameOver::createScene()
{
	auto scene = Scene::create();
	auto layer = GameOver::create();
	scene->addChild(layer);
	return scene;
}

bool GameOver::init()
{
	if (!Layer::init()){
		return false;
	}
	auto visibleSize = Director::getInstance()->getVisibleSize();

	//��Ϸ��������
	auto over = ui::ImageView::create("gameOver.jpg");		
	over->setPosition(Vec2(0,0));                           
	over->setAnchorPoint(Vec2(0, 0));						
	float uiX = over->getContentSize().width;				
	float uiY = over->getContentSize().height;			    
	over->setScaleX(480 / uiX);							    					
	over->setScaleY(600 / uiY);							    
	this->addChild(over);	

	//��ȡXML�ļ�
	auto dic = Dictionary::createWithContentsOfFile("fonts/Chanies.xml");

	//���¿�ʼ��ť
	auto str = (String*)dic->objectForKey("gameover");	
	auto anew = Label::create();
	anew->setString(str->getCString());
	anew->setSystemFontSize(50);
	anew->setColor(Color3B::BLACK);

	auto anewmenu = MenuItemLabel::create(anew, CC_CALLBACK_1(GameOver::startMenu, this));
	anewmenu->setPosition(Point(visibleSize.width / 2, visibleSize.height /2.7));

	//�˳���Ϸ��ť
	auto str2 = (String*)dic->objectForKey("exitgame");
	auto exit = Label::create();
	exit->setString(str2->getCString());
	exit->setSystemFontSize(50);
	exit->setColor(Color3B::BLACK);

	auto exitmenu = MenuItemLabel::create(exit, CC_CALLBACK_1(GameOver::exitMenu, this));
	exitmenu->setPosition(Point(visibleSize.width / 2, visibleSize.height / 6.4));

	auto menu = Menu::create(exitmenu, anewmenu, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu);

	FsRecord();//������¼
	
	return true;
}

//������¼
void GameOver::FsRecord()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto dic = Dictionary::createWithContentsOfFile("fonts/Chanies.xml");

	//��߷�����ǩ
	auto tall_score = Label::create();
	tall_score->setString(((__String*)(dic->objectForKey("tallscore")))->getCString());
	tall_score->setSystemFontSize(30);
	tall_score->setColor(Color3B::GREEN);
	tall_score->setAnchorPoint(Point(0.5, 0.5));   //����ê��
	tall_score->setPosition(Point(visibleSize.width / 2, visibleSize.height - 185));
	this->addChild(tall_score);

	auto Gfjl = Label::create();
	Gfjl->setSystemFontSize(20);
	Gfjl->setColor(Color3B::BLUE);
	Gfjl->setPosition(Point(visibleSize.width / 2, visibleSize.height - 220));
	this->addChild(Gfjl);

	//��ǰ������ʾ
	auto dq_score = Label::create();
	dq_score->setString(((__String*)(dic->objectForKey("score")))->getCString());
	dq_score->setSystemFontSize(30);
	dq_score->setColor(Color3B::GREEN);
	dq_score->setPosition(Point(visibleSize.width / 2, visibleSize.height - 255));
	this->addChild(dq_score);

	auto Fsjl = Label::create();
	Fsjl->setSystemFontSize(20);
	Fsjl->setColor(Color3B::BLUE);
	Fsjl->setPosition(Point(visibleSize.width / 2, visibleSize.height - 295));
	this->addChild(Fsjl);

	//��ȡ��߷�
	auto score_win = UserDefault::getInstance()->getIntegerForKey("tallscore");
	auto score_dq = UserDefault::getInstance()->getIntegerForKey("score");

	//��ʾ��߷�
	Gfjl->setString(String::createWithFormat("%d", score_win)->getCString());
	//��ʾ��ǰ��
	Fsjl->setString(String::createWithFormat("%d", score_dq)->getCString());
	
}

//���¿�ʼ��ť
void GameOver::startMenu(Ref* ref){
	//�л�����
	Director::getInstance()->replaceScene(GameScene::createScene());

	//���²��ű�������
	SimpleAudioEngine::getInstance()->playBackgroundMusic("sound/bgyy.mp3");
}

//�˳���Ϸ��ť
void GameOver::exitMenu(Ref* ref){
	//�л�����
	Director::getInstance()->end();
}