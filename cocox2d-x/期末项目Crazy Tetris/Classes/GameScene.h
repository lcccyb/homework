#ifndef _GAMESCENE_H_
#define _GAMESCENE_H_

#include "cocos2d.h"
#include "SimpleAudioEngine.h"
USING_NS_CC;

class GameScene : public Scene {
public:
    static Scene* createScene();
    void setPhysicsWorld(PhysicsWorld * world);
    bool onConcactBegin(PhysicsContact & contact);
    virtual bool init();
    void syncscore();
    CREATE_FUNC(GameScene);
    
private:
    PhysicsWorld * m_world;
    Vector<Sprite*> blockvec;
    GLboolean isRotating = false;
    GLboolean isAccelerating = false;
    int score = 0;
    int is_pause = 0;
    int is_next = 0;
    int scoreBase = 0;
    void update(float dt);
    void buildNextBlock();
    void gameOver();
    Sprite *randomBuildBlock();
    
    Size visibleSize;
    Vec2 origin;
    Vec2 lastPosition = Vec2(0, 0);
    Sprite *currentBlock;
    Sprite *nextBlock;
    Label* scoreLabel;
    
    cocos2d::Label* Score;
    
    void onKeyPressed(EventKeyboard::KeyCode code, Event* event);
    void onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event);
    void addListener();
};

#endif
