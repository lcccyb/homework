#pragma execution_character_set("utf-8")
#include "GameScene.h"
#include "GameOver.h"
#include "SimpleAudioEngine.h"
#include <string.h>
#define database UserDefault::getInstance()

USING_NS_CC;
using namespace CocosDenshion;
using namespace std;

void GameScene::setPhysicsWorld(PhysicsWorld* world) { m_world = world; }

Scene* GameScene::createScene() {
    srand((unsigned)time(NULL));
    auto scene = Scene::createWithPhysics();
    
    scene->getPhysicsWorld()->setAutoStep(true);
    
    Vect gravity(0, -50.0f);
    scene->getPhysicsWorld()->setGravity(gravity);
    
    auto layer = GameScene::create();
    layer->setPhysicsWorld(scene->getPhysicsWorld());
    scene->addChild(layer);
    return scene;
}


// on "init" you need to initialize your instance
bool GameScene::init() {
    if (!Scene::init()) {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    //设置边界
    auto body = PhysicsBody::createEdgeBox(Size(256, 506), PHYSICSBODY_MATERIAL_DEFAULT, 3);
    body->setCategoryBitmask(0xFFFFFFFF);
    body->setCollisionBitmask(0xFFFFFFFF);
    body->setContactTestBitmask(0xFFFFFFFF);
    auto node = Node::create();
    node->setTag(0);
    node->setPosition(Point(visibleSize.width/2, visibleSize.height/2));
    node->setPhysicsBody(body);
    addChild(node);
    
    
    auto next = Label::createWithTTF("next block:", "fonts/arial.ttf", 36);
    next->setPosition(Vec2(700, 540));
    addChild(next);
    // 显示下一个俄罗斯方块
    
    score = -10;
    // 分数
    auto scorelabel = Label::createWithTTF("score:", "fonts/arial.ttf", 36);
    scorelabel->setPosition(Vec2(270, 540));
    addChild(scorelabel);
    Score = Label::createWithTTF("0", "fonts/arial.ttf", 36);
    Score->setPosition(Vec2(origin.x + 270, origin.y + 500));
    addChild(Score, 3);
    
    auto restart = MenuItemLabel::create(Label::createWithTTF("restart", "fonts/arial.ttf", 36), [&](Ref *sender) {
        // 重新开始
        for (auto i : blockvec) {
            i->removeFromParentAndCleanup(true);
        }
        blockvec.clear();
        score = 0;
        GameScene::syncscore();
        currentBlock = randomBuildBlock();
        GameScene::buildNextBlock();
    });
    
    auto restartbutton = Menu::create(restart, NULL);
    restartbutton->setPosition(Vec2(origin.x + 270, origin.y + 380));
    addChild(restartbutton, 2);
    
    auto start = MenuItemLabel::create(Label::createWithTTF("start", "fonts/arial.ttf", 36), [&](Ref *sender) {
        // 开始、继续游戏
        for (auto i : blockvec) {
            (i->getPhysicsBody())->setDynamic(true);
            (i->getPhysicsBody())->setVelocity(Vec2(0, -10));
        }
        is_pause = 0;
    });
    
    auto startbutton = Menu::create(start, NULL);
    startbutton->setPosition(Vec2(origin.x + 270, origin.y + 440));
    addChild(startbutton, 2);
    
    auto pause = MenuItemLabel::create(Label::createWithTTF("pause", "fonts/arial.ttf", 36), [&](Ref *sender) {
        // 暂停游戏
        is_pause = 1;
        for (auto i : blockvec) {
            (i->getPhysicsBody())->setDynamic(false);
        }
    });
    
    auto pausebutton = Menu::create(pause, NULL);
    pausebutton->setPosition(Vec2(origin.x + 270, origin.y + 320));
    addChild(pausebutton, 2);
    
    auto back = MenuItemLabel::create(Label::createWithTTF("back", "fonts/arial.ttf", 36), [&](Ref *sender) {
        // 返回主页面
        Director::getInstance()->popScene();
    });
    
    auto backbutton = Menu::create(back, NULL);
    backbutton->setPosition(Vec2(origin.x + 270, origin.y + 260));
    addChild(backbutton, 2);
    is_next = 1;
    
    
    currentBlock = randomBuildBlock();
    
    this->scheduleUpdate();
    addListener();
    return true;
}

void GameScene::update(float dt) {
    if (currentBlock->getPositionX() >= visibleSize.width / 2 - 50
        && currentBlock->getPositionX() <= visibleSize.width / 2 + 50
        && currentBlock->getPositionY() >= visibleSize.height / 2 + 220)
    {
        gameOver();
    }
    
    if (is_pause == 0 && std::fabs(currentBlock->getPositionY() == lastPosition.y && is_next)) {
        score += 10;
        syncscore();
        buildNextBlock();
        is_next = 0;
    }
    else {
        lastPosition = currentBlock->getPosition();
    }
    
}


void GameScene::buildNextBlock()
{
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    if (nextBlock == NULL)
    {
        currentBlock = randomBuildBlock();
    }
    else
    {
        currentBlock = nextBlock;
    }
    
    currentBlock->setPosition(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2 + 220);
    currentBlock->getPhysicsBody()->setGravityEnable(true);
    blockvec.pushBack(currentBlock);
    nextBlock = randomBuildBlock();
    nextBlock->setPosition(origin.x + 700, visibleSize.height / 2 + 150);
    nextBlock->getPhysicsBody()->setGravityEnable(false);
}

void GameScene::addListener() {
    auto keyboardListener = EventListenerKeyboard::create();
    keyboardListener->onKeyPressed = CC_CALLBACK_2(GameScene::onKeyPressed, this);
    keyboardListener->onKeyReleased = CC_CALLBACK_2(GameScene::onKeyReleased, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(keyboardListener, this);
    
    auto contactListener = EventListenerPhysicsContact::create();
    contactListener->onContactBegin = CC_CALLBACK_1(GameScene::onConcactBegin, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);
}

void GameScene::onKeyPressed(EventKeyboard::KeyCode code, Event* event) {
    if (code == EventKeyboard::KeyCode::KEY_A || code == EventKeyboard::KeyCode::KEY_LEFT_ARROW)
    {
        currentBlock->getPhysicsBody()->setVelocity(Vec2(-100.0f, currentBlock->getPhysicsBody()->getVelocity().y));
    } else if (code == EventKeyboard::KeyCode::KEY_D || code == EventKeyboard::KeyCode::KEY_RIGHT_ARROW)
    {
        currentBlock->getPhysicsBody()->setVelocity(Vec2(100.0f, currentBlock->getPhysicsBody()->getVelocity().y));
    } else if (code == EventKeyboard::KeyCode::KEY_W || code == EventKeyboard::KeyCode::KEY_UP_ARROW)
    {
        currentBlock->getPhysicsBody()->setAngularVelocity(-5.0f);
        isRotating = true;
    } else if (code == EventKeyboard::KeyCode::KEY_S || code == EventKeyboard::KeyCode::KEY_DOWN_ARROW)
    {
        currentBlock->getPhysicsBody()->setVelocity(Vec2(currentBlock->getPhysicsBody()->getVelocity().x, -150.0f));
        isAccelerating = true;
    }
}

void GameScene::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event)
{
    currentBlock->getPhysicsBody()->setVelocity(Vec2(0, (isAccelerating && currentBlock->getPhysicsBody()->getVelocity().y < -50.0f)
                                                     ? currentBlock->getPhysicsBody()->getVelocity().y + 50.0f : currentBlock->getPhysicsBody()->getVelocity().y));
    currentBlock->getPhysicsBody()->setAngularVelocity((isRotating && currentBlock->getPhysicsBody()->getAngularVelocity() <= -5.0f)
                                                       ? currentBlock->getPhysicsBody()->getAngularVelocity() + 5.0f : currentBlock->getPhysicsBody()->getAngularVelocity());
    
    isAccelerating = false;
    isRotating = false;
}

Sprite* GameScene::randomBuildBlock() {
    int num = random(1, 19);
    
    string picture = to_string(num) + ".png";
    auto block = Sprite::create(picture);
    block->setScale(0.7, 0.7);
    block->setPosition(visibleSize.width / 2, visibleSize.height);
    
    // 添加刚体
    auto blockbody = PhysicsBody::createBox(block->getContentSize(), PhysicsMaterial(10000000.0f, 0.0f, 1.0f));
    blockbody->setCategoryBitmask(0xFFFFFFFF);
    blockbody->setCollisionBitmask(0xFFFFFFFF);
    blockbody->setContactTestBitmask(0xFFFFFFFF);
    blockbody->setDynamic(true);
    block->setPhysicsBody(blockbody);
    block->setTag(1);
    this->addChild(block, 1);
    
    return block;
}


bool GameScene::onConcactBegin(PhysicsContact & contact) {
    auto c1 = contact.getShapeA(), c2 = contact.getShapeB();
    auto nodeA = c1->getBody()->getNode();
    auto nodeB = c2->getBody()->getNode();
    
    if ((nodeA->getTag() == 1 && nodeB->getTag() == 0) || (nodeB->getTag() == 1 && nodeA->getTag() == 0)) {
        if (nodeA->getTag() == 1) {
            nodeA->setTag(0);
            is_next = 1;
        }
        else {
            nodeB->setTag(0);
            is_next = 1;
        }
    }
    return true;
}

void GameScene::syncscore(){
    char scorestring[10];
    sprintf(scorestring, "%d", score);
    Score->setString(scorestring);
}

void GameScene::gameOver() {
	Director::getInstance()->replaceScene(GameOver::createScene());
}
