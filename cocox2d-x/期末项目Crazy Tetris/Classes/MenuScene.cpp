#include "MenuScene.h"
#include "GameScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

Scene* MenuScene::createScene()
{
    return MenuScene::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}
void MenuScene::menuCloseCallback(Ref *pSender){
    Director::getInstance()->pushScene(GameScene::createScene());
}
// on "init" you need to initialize your instance
bool MenuScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();


	auto bg = Sprite::create("bg.jpg");
    bg->setScale(visibleSize.width / (bg->getContentSize()).width, visibleSize.height / (bg->getContentSize()).height);
	bg->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	this->addChild(bg, 0);
    
    auto gametitle = Sprite::create("timg.png");
    gametitle->setScale( 1.5, 1.5);
    gametitle->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y + 80));
    this->addChild(gametitle, 2);
    
    auto starttile = Label::createWithTTF("START", "fonts/arial.ttf", 50);
    starttile->setColor(Color3B::YELLOW);
    auto menuitem = MenuItemLabel::create(starttile, CC_CALLBACK_1(MenuScene::menuCloseCallback, this));
    auto menu = Menu::create(menuitem, NULL);
    menu->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y - 100));
    this->addChild(menu, 2);
    return true;
}

