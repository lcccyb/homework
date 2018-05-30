#include "GameScene.h"

USING_NS_CC;

Scene* GameSence::createScene()
{
	return GameSence::create();
}

// on "init" you need to initialize your instance
bool GameSence::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Scene::init())
	{
		return false;
	}

	//add touch listener
	EventListenerTouchOneByOne* listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);
	listener->onTouchBegan = CC_CALLBACK_2(GameSence::onTouchBegan, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);


	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("level-sheet.plist");

	auto level = Sprite::create("level-background-0.jpg");
	level->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	this->addChild(level, 0);

	stoneLayer = Layer::create();
	stoneLayer->setAnchorPoint(Vec2(0, 0));
	stoneLayer->setPosition(0, 0);
	stone = Sprite::create("stone.png");
	stone->setPosition(Vec2(560, 480));
	stoneLayer->addChild(stone);
	this->addChild(stoneLayer, 1);

	mouseLayer = Layer::create();
	mouseLayer->setAnchorPoint(Vec2(0, 0));
	mouseLayer->setPosition(Vec2(0, visibleSize.height / 2));
	mouse = Sprite::createWithSpriteFrameName("gem-mouse-0.png");
	mouse->setPosition(Vec2(visibleSize.width / 2, 0));
	mouseLayer->addChild(mouse);
	this->addChild(mouseLayer, 1);

	auto shoot = MenuItemFont::create("Shoot", CC_CALLBACK_1(GameSence::shootMenuCallback, this));
	shoot->setFontSizeObj(70);
	shoot->setColor(Color3B(255, 255, 255));
	shoot->setPosition(Vec2(visibleSize.width / 2 + origin.x + 330, visibleSize.height / 2 + origin.y + 160));
	auto menu = Menu::create(shoot, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);

	return true;
}

bool GameSence::onTouchBegan(Touch *touch, Event *unused_event) {

	auto location = touch->getLocation();

	auto cheese = Sprite::create("cheese.png");
	cheese->setPosition(location);
	this->addChild(cheese, 0);
	auto cheeseFadeOut = FadeOut::create(6);
	cheese->runAction(cheeseFadeOut);

	auto location_node = mouseLayer->convertToNodeSpace(location);
	auto mouseMoveTo = MoveTo::create(2, location_node);
	auto seq = Sequence::create(mouseMoveTo, nullptr);
	mouse->runAction(seq);

	return true;
}

void GameSence::shootMenuCallback(Ref * pSender)
{
	Size visibleSize = Director::getInstance()->getVisibleSize();

	int random_width = CCRANDOM_0_1() * visibleSize.width;
	int random_height = CCRANDOM_0_1() * visibleSize.height;
	auto location = mouseLayer->convertToNodeSpace(Vec2(random_width, random_height));
	auto MoveTo = MoveTo::create(1, location);
	auto RotateTo = RotateBy::create(1, 360);
	auto seq = Spawn::createWithTwoActions(MoveTo, RotateTo);
	mouse->runAction(seq);

	auto position = mouseLayer->convertToWorldSpace(mouse->getPosition());
	auto diamond = Sprite::create("diamond.png");
	diamond->setPosition(position);
	this->addChild(diamond, 1);

	auto stone = Sprite::create("stone.png");
	stone->setPosition(Vec2(560, 480));
	this->addChild(stone, 1);
	auto stoneMoveTo = MoveTo::create(1, position);
	stone->runAction(stoneMoveTo);
	auto stoneFadeOut = FadeOut::create(3);
	stone->runAction(stoneFadeOut);
}


