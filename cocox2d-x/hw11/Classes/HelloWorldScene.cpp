#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#pragma execution_character_set("utf-8")

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    return HelloWorld::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }

    visibleSize = Director::getInstance()->getVisibleSize();
    origin = Director::getInstance()->getVisibleOrigin();

	//����һ����ͼ
	auto texture = Director::getInstance()->getTextureCache()->addImage("$lucia_2.png");
	//����ͼ�������ص�λ�и�����ؼ�֡
	auto frame0 = SpriteFrame::createWithTexture(texture, CC_RECT_PIXELS_TO_POINTS(Rect(0, 0, 113, 113)));
	//ʹ�õ�һ֡��������
	player = Sprite::createWithSpriteFrame(frame0);
	player->setPosition(Vec2(origin.x + visibleSize.width / 2,
		origin.y + visibleSize.height / 2));
	addChild(player, 3);

	TTFConfig ttfConfig;
	ttfConfig.fontFilePath = "fonts/arial.ttf";
	ttfConfig.fontSize = 36;

	time = Label::createWithTTF(ttfConfig, "180");
	time->setPosition(Vec2(origin.x + visibleSize.width / 2,
		origin.y + visibleSize.height - time->getContentSize().height));
	addChild(time);
	dtime = 180;
	schedule(schedule_selector(HelloWorld::Time), 1.0f, kRepeatForever, 0);

	//hp��
	Sprite* sp0 = Sprite::create("hp.png", CC_RECT_PIXELS_TO_POINTS(Rect(0, 320, 420, 47)));
	Sprite* sp = Sprite::create("hp.png", CC_RECT_PIXELS_TO_POINTS(Rect(610, 362, 4, 16)));

	//ʹ��hp������progressBar
	pT = ProgressTimer::create(sp);
	pT->setScaleX(90);
	pT->setAnchorPoint(Vec2(0, 0));
	pT->setType(ProgressTimerType::BAR);
	pT->setBarChangeRate(Point(1, 0));
	pT->setMidpoint(Point(0, 1));
	pT->setPercentage(100);
	pT->setPosition(Vec2(origin.x + 14 * pT->getContentSize().width, origin.y + visibleSize.height - 2 * pT->getContentSize().height));
	addChild(pT, 1);
	sp0->setAnchorPoint(Vec2(0, 0));
	sp0->setPosition(Vec2(origin.x + pT->getContentSize().width, origin.y + visibleSize.height - sp0->getContentSize().height));
	addChild(sp0, 0);

	// ��̬����
	idle.reserve(1);
	idle.pushBack(frame0);

	// ��������
	attack.reserve(17);
	for (int i = 0; i < 17; i++) {
		auto frame = SpriteFrame::createWithTexture(texture, CC_RECT_PIXELS_TO_POINTS(Rect(113 * i, 0, 113, 113)));
		attack.pushBack(frame);
	}
	attack.pushBack(frame0);

	// ���Է��չ�������
	// ��������(֡����22֡���ߣ�90����79��
	auto texture2 = Director::getInstance()->getTextureCache()->addImage("$lucia_dead.png");
	dead.reserve(22);
	for (int i = 0; i < 22; i++) {
		auto frame = SpriteFrame::createWithTexture(texture2, CC_RECT_PIXELS_TO_POINTS(Rect(79 * i, 0, 79, 90)));
		dead.pushBack(frame);
	}
	dead.pushBack(frame0);
	// Todo

	// �˶�����(֡����8֡���ߣ�101����68��
	auto texture3 = Director::getInstance()->getTextureCache()->addImage("$lucia_forward.png");
	run.reserve(8);
	for (int i = 0; i < 8; i++) {
		auto frame = SpriteFrame::createWithTexture(texture3, CC_RECT_PIXELS_TO_POINTS(Rect(68 * i, 0, 68, 101)));
		run.pushBack(frame);
	}

	auto menuLabelW = Label::createWithTTF(ttfConfig, "W");
	auto menuLabelS = Label::createWithTTF(ttfConfig, "S");
	auto menuLabelA = Label::createWithTTF(ttfConfig, "A");
	auto menuLabelD = Label::createWithTTF(ttfConfig, "D");
	auto menuLabelX = Label::createWithTTF(ttfConfig, "X");
	auto menuLabelY = Label::createWithTTF(ttfConfig, "Y");

	auto ButtonW = MenuItemLabel::create(menuLabelW, CC_CALLBACK_0(HelloWorld::move, this, 'W'));
	auto ButtonS = MenuItemLabel::create(menuLabelS, CC_CALLBACK_0(HelloWorld::move, this, 'S'));
	auto ButtonA = MenuItemLabel::create(menuLabelA, CC_CALLBACK_0(HelloWorld::move, this, 'A'));
	auto ButtonD = MenuItemLabel::create(menuLabelD, CC_CALLBACK_0(HelloWorld::move, this, 'D'));
	auto ButtonX = MenuItemLabel::create(menuLabelX, CC_CALLBACK_0(HelloWorld::action, this, 'X'));
	auto ButtonY = MenuItemLabel::create(menuLabelY, CC_CALLBACK_0(HelloWorld::action, this, 'Y'));

	ButtonA->setPosition(Vec2(origin.x + ButtonA->getContentSize().width, origin.y + ButtonA->getContentSize().height));
	ButtonD->setPosition(Vec2(ButtonA->getPosition().x + 3 * ButtonD->getContentSize().width, ButtonA->getPosition().y));
	ButtonS->setPosition(Vec2(ButtonA->getPosition().x + 1.5*ButtonS->getContentSize().width, ButtonA->getPosition().y));
	ButtonW->setPosition(Vec2(ButtonS->getPosition().x, ButtonS->getPosition().y + ButtonW->getContentSize().height));
	ButtonX->setPosition(Vec2(origin.x + visibleSize.width - ButtonX->getContentSize().width, ButtonW->getPosition().y));
	ButtonY->setPosition(Vec2(ButtonX->getPosition().x - ButtonY->getContentSize().width, ButtonA->getPosition().y));

	auto menu = Menu::create(ButtonW, ButtonS, ButtonA, ButtonD, ButtonX, ButtonY, nullptr);
	menu->setPosition(Vec2(0, 0));
	addChild(menu, 1);

    return true;
}

void HelloWorld::move(char ch) {

	auto animation = Animation::createWithSpriteFrames(run, 0.08f);
	auto animate = Animate::create(animation);

	if (ch == 'W') {
		if (player->getPositionY() < visibleSize.height + origin.y - 48) {
			Point p = Point(player->getPositionX(), player->getPositionY() + 30);
			auto move = MoveTo::create(0.4f, p);
			auto myspawn = Spawn::createWithTwoActions(move, animate);
			player->runAction(myspawn);
		}
	}
	if (ch == 'A') {
		if (player->getPositionX() > origin.x + 45) {
			Point p = Point(player->getPositionX() - 30, player->getPositionY());
			auto move = MoveTo::create(0.4f, p);
			auto myspawn = Spawn::createWithTwoActions(move, animate);
			player->runAction(myspawn);
		}
	}
	if (ch == 'S') {
		if (player->getPositionY() > origin.y + 48) {
			Point p = Point(player->getPositionX(), player->getPositionY() - 30);
			auto move = MoveTo::create(0.4f, p);
			auto myspawn = Spawn::createWithTwoActions(move, animate);
			player->runAction(myspawn);
		}
	}
	if (ch == 'D') {
		if (player->getPositionX() < visibleSize.width + origin.x - 45) {
			Point p = Point(player->getPositionX() + 30, player->getPositionY());
			auto move = MoveTo::create(0.4f, p);
			auto myspawn = Spawn::createWithTwoActions(move, animate);
			player->runAction(myspawn);
		}
	}
}


void HelloWorld::action(char cid) {

	if (isAction) return;
	auto begin = CallFuncN::create([&](Ref* sender) {
		isAction = true;
	});
	auto end = CallFuncN::create([&](Ref* sender) {
		isAction = false;
	});

	auto animate = Animate::create(Animation::createWithSpriteFrames(dead, 0.1f));
	auto animate2 = Animate::create(Animation::createWithSpriteFrames(attack, 0.1f));

	auto seq = Sequence::create(begin, animate, end, NULL);
	auto seq2 = Sequence::create(begin, animate2, end, NULL);

	if (cid == 'X') {
		pT->setPercentage(pT->getPercentage() - 10);
		player->runAction(seq);
	}
	if (cid == 'Y') {
		pT->setPercentage(pT->getPercentage() + 10);
		player->runAction(seq2);
	}
}

void HelloWorld::Time(float dt) {
	if (dtime > 0) {
		dtime--;
		char* str = new char[10];
		sprintf(str, "%d", dtime);
		time->setString(str);
	}
}


