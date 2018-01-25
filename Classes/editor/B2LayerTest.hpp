//
//  B2LayerTest.hpp
//  Box2dEditor
//
//  Created by Oleh Mahobey on 8/26/17.
//
//

#ifndef B2LayerTest_hpp
#define B2LayerTest_hpp

#include "cocos2d.h"
#include "b2DebugLayer.h"
#include "Box2D/Box2D.h"
#include "Ball.hpp"
#include "b2Utils.hpp"
#include "UILayer.hpp"
#include "Car.hpp"
USING_NS_CC;
class B2LayerTest:public Layer{
    b2World *world;
    Sprite *background;
    Vec2 *lastTouch;
    b2Body *circle,*square;
    Car *car;
    bool touchBegan(Touch *touch,Event *event);
    void touchEnd(Touch *touch, Event *event);
    void touchCanceled(Touch *touch, Event *event);
    void touchMove(Touch *touch,Event *event);
    void moveLeft(Ref *ref,ui::Widget::TouchEventType type);
    void moveRight(Ref *ref,ui::Widget::TouchEventType type);
    void moveDown(Ref *ref);
    void moveUp(Ref *ref);
    
public:
    void parseMap();
    virtual bool init();
    CREATE_FUNC(B2LayerTest);
    static Scene *createScene();
    virtual void update(float dt);
    ~B2LayerTest();
};

#endif /* B2LayerTest_hpp */
