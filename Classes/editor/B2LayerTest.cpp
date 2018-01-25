//
//  B2LayerTest.cpp
//  Box2dEditor
//
//  Created by Oleh Mahobey on 8/26/17.
//
//


#include "B2LayerTest.hpp"
bool B2LayerTest::init(){
    if(!Layer::init()){
        return false;
    }
    lastTouch = nullptr;
    
    this->world = new b2World(b2Vec2(0,-9.8));
    
    auto debuglayer = b2DebugLayer::create(world, B2D_RATIO);
    
    square ;//= helper::createSquare(*world, Vec2(2,3));
    circle = helper::createCircle(*world,.5, Vec2(3,3));
    auto ground = helper::createGround(*world);
    ground->SetTransform(ground->GetPosition() - b2Vec2(0,5), ground->GetAngle());
    car =  Car::create();
    
    car->createCar(*world);
    addChild(car);
    
    
    
    
    Texture2D *texture = Director::getInstance()->getTextureCache()->addImage("brick.png");
    Texture2D::TexParams params;
    
    params.minFilter = GL_NEAREST;
    params.magFilter = GL_NEAREST;
    
    params.wrapS = GL_REPEAT;
    params.wrapT = GL_REPEAT;
    texture->setTexParameters(params);
    background = Sprite::createWithTexture(texture, (Rect){ 0, 0, 500, 500 });
    
    addChild(background,0);
    background->setAnchorPoint(Vec2::ZERO);
    background->addChild(debuglayer);
    
    
    
    auto listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = CC_CALLBACK_2(B2LayerTest::touchBegan,this);
    listener->onTouchMoved = CC_CALLBACK_2(B2LayerTest::touchMove, this);
    listener->onTouchEnded = CC_CALLBACK_2(B2LayerTest::touchEnd, this);
    listener->onTouchCancelled = CC_CALLBACK_2(B2LayerTest::touchCanceled, this);
    getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
    
    UILayer *layer = UILayer::create();
    layer->getRightBtn()->addTouchEventListener(CC_CALLBACK_2(B2LayerTest::moveRight, this));
    
    layer->getLeftBtn()->addTouchEventListener(CC_CALLBACK_2(B2LayerTest::moveLeft, this));
    layer->getDownBtn()->addClickEventListener(CC_CALLBACK_1(B2LayerTest::moveDown, this));
    layer->getUpBtn()->addClickEventListener(CC_CALLBACK_1(B2LayerTest::moveUp, this));
    
    
    Device::setAccelerometerEnabled(true);
    
    
    auto accListener = EventListenerAcceleration::create([](Acceleration *acc, Event *event){
        CCLOG("X %f Y %f Z %f",acc->x,acc->y,acc->z);
    });
    getEventDispatcher()->addEventListenerWithSceneGraphPriority(accListener, this);
    addChild(layer,5);
    parseMap();
    scheduleUpdate();
    return true;
}




void B2LayerTest::update(float dt){
    world->Step(dt, 2, 6);
    
    
}


bool B2LayerTest::touchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event){
    lastTouch = new Vec2(touch->getLocation() - background->getPosition());
    return true;
}
void B2LayerTest::touchMove(cocos2d::Touch *touch, cocos2d::Event *event){
    Vec2 moveTo = touch->getLocation() - *lastTouch;
    background->setPosition(moveTo);
}
void B2LayerTest::touchEnd(cocos2d::Touch *touch, cocos2d::Event *event){
    if(lastTouch) delete lastTouch;
    lastTouch = nullptr;
    
    
    // auto action = MoveTo::create(0.5, Vec2::ZERO);
    
    // auto easing  = EaseIn::create(action, .5);
    //background->runAction(easing);
}

void B2LayerTest::touchCanceled(cocos2d::Touch *touch, cocos2d::Event *event){
    if(lastTouch)delete lastTouch;
    lastTouch = nullptr;
}

void B2LayerTest::moveLeft(Ref *ref,ui::Widget::TouchEventType type){
    //square->ApplyLinearImpulse(b2Vec2(-10,0), square->GetWorldCenter(), true);
    
    
    
    switch (type) {
        case cocos2d::ui::Widget::TouchEventType::BEGAN:{
            car->moveBackward(true);
        }
            break;
        case cocos2d::ui::Widget::TouchEventType::CANCELED:
        case  cocos2d::ui::Widget::TouchEventType::ENDED:{
            car->moveBackward(false);
        }
            break;
        case cocos2d::ui::Widget::TouchEventType::MOVED:
            break;
            
            
    }

    
}

void B2LayerTest::moveRight(Ref *ref,ui::Widget::TouchEventType type){
    // square->ApplyLinearImpulse(b2Vec2(10,0), square->GetWorldCenter(), true);
    switch (type) {
        case cocos2d::ui::Widget::TouchEventType::BEGAN:{
            car->moveForward(true);
        }
            break;
        case cocos2d::ui::Widget::TouchEventType::CANCELED:
        case  cocos2d::ui::Widget::TouchEventType::ENDED:{
                car->moveForward(false);
        }
            break;
        case cocos2d::ui::Widget::TouchEventType::MOVED:
            break;
            
    }
    
}

void B2LayerTest::parseMap(){
   
    
}

void B2LayerTest::moveUp(cocos2d::Ref *ref){
    square->ApplyLinearImpulse(b2Vec2(0,5), square->GetWorldCenter(), true);
    
}

void B2LayerTest::moveDown(cocos2d::Ref *ref){
    
}

Scene *B2LayerTest::createScene(){
    Scene *scene = Scene::create();
    scene->addChild(B2LayerTest::create());
    return scene;
}

B2LayerTest::~B2LayerTest(){
    delete world;
}
