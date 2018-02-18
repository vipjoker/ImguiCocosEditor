//
// Created by Oleh on 2/12/18.
//

#include "b2Sprite.h"
USING_NS_CC;
bool b2Sprite::init() {
    if(!Sprite::init()){
        return false;
    }

    scheduleUpdate();
    return true;
}



void b2Sprite::update(float dt) {
    if(body){
        setPosition(helper::toVec2(body->GetPosition()));
        setRotation(-MATH_RAD_TO_DEG(body->GetAngle()));
    }

}

void b2Sprite::setBody(b2Body *body) {
    this->body = body;
}

void b2Sprite::createCircleBody() {

}

void b2Sprite::createSquareBody() {

}

void b2Sprite::onEnter() {
    Node::onEnter();
    b2Scene *scene = dynamic_cast<b2Scene*>(getScene());
    if(scene){
        b2World *world =  scene->getWorld();
        b2Body *body = helper::createCircle(*world,1,Vec2(10,10));
        body->SetAngularVelocity(1);
        body->ApplyForceToCenter(b2Vec2(10,0),true);
        setBody(body);
    }
}
