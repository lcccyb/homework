#include "GameOver.h"
#include "MenuScene.h"
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

	auto over = ui::ImageView::create("gameOver.jpg");		
	over->setPosition(Vec2(0,0));                           
	over->setAnchorPoint(Vec2(0, 0));						
	float uiX = over->getContentSize().width;				
	float uiY = over->getContentSize().height;			    
	over->setScaleX(480 / uiX);							    					
	over->setScaleY(600 / uiY);							    
	this->addChild(over);	

	auto dic = Dictionary::createWithContentsOfFile("fonts/Chanies.xml");

	auto str = (String*)dic->objectForKey("gameover");	
	auto anew = Label::create();
	anew->setString(str->getCString());
	anew->setSystemFontSize(50);
	anew->setColor(Color3B::BLACK);

	auto anewmenu = MenuItemLabel::create(anew, CC_CALLBACK_1(GameOver::startMenu, this));
	anewmenu->setPosition(Point(visibleSize.width / 2, visibleSize.height /2.7));

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
	
	return true;
}

void GameOver::startMenu(Ref* ref){

	Director::getInstance()->replaceScene(MenuScene::createScene());
}

void GameOver::exitMenu(Ref* ref){
	Director::getInstance()->end();
}