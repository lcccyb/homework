#include "StartScene.h"
#include "GameScene.h"
#include "SimpleAudioEngine.h"
#include <ui/UIImageView.h>

USING_NS_CC;
using namespace CocosDenshion;

Scene* StartScene::createScene()
{
	auto scene = Scene::create();
	auto layer = StartScene::create();
	scene->addChild(layer);
	return scene;
}

bool StartScene::init(){
	if (!Layer::init()){
		return false;
	}
	auto visibleSize = Director::getInstance()->getVisibleSize();

	auto homeBj = ui::ImageView::create("bg.jpg");			
	homeBj->setPosition(Vec2(0,0));	
	homeBj->setAnchorPoint(Vec2(0, 0));							
	float uiX = homeBj->getContentSize().width;					
	float uiY = homeBj->getContentSize().height;				
	homeBj->setScaleX(480 / uiX);													
	homeBj->setScaleY(600 / uiY);								
	this->addChild(homeBj);

	//��Ϸ����
	auto gameBt = Sprite::create("title.png");
	gameBt->setPosition(Point(visibleSize.width / 2, visibleSize.height - 50));
	this->addChild(gameBt);

	//��ȡXML�ļ�
	auto dic = Dictionary::createWithContentsOfFile("fonts/Chanies.xml");
	auto str = (String*)dic->objectForKey("play");
	//��ʼ��ť
	auto start = Label::create();
	start->setString(str->getCString());
	start->setSystemFontSize(40);
	start->setColor(Color3B::BLUE);

	auto startmenu = MenuItemLabel::create(start, CC_CALLBACK_1(StartScene::startMenu, this));
	startmenu->setPosition(Point(visibleSize.width / 2, visibleSize.height / 6));

	auto menu = Menu::create(startmenu, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu);

	//��ӱ������֣���Ч
	auto music = SimpleAudioEngine::getInstance();
	music->preloadBackgroundMusic("sound/bgyy.mp3");
	music->playBackgroundMusic("sound/bgyy.mp3", true);

	return true;
}

//��ʼ��ť
void StartScene::startMenu(Ref*ref){
	//�л�����
	Director::getInstance()->replaceScene(TransitionFade::create(0.2, GameScene::createScene()));
}