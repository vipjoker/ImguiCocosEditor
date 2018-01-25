//
//  Ball.cpp
//  Box2dEditor
//
//  Created by Oleh Mahobey on 8/26/17.
//
//

#include "Ball.hpp"


Ball *Ball::createWithFile(const char *file, b2World &world,const Vec2 vec){
    
    Ball *ball = new Ball();
    if(ball && ball->initWithFile(file)){
        ball->autorelease();
        ball->initPhysics(world,vec);
        return ball;
    }else{
        delete ball;
        ball = nullptr;
        return nullptr;
    }
}
void Ball::initPhysics(b2World &world, Vec2 vec){
    Size size =getContentSize();
    b2BodyDef def;
    
    b2Vec2  bVec= helper::tob2Vec(vec);
    def.position.Set(bVec.x, bVec.y);
    def.type = b2BodyType::b2_dynamicBody;
    b2CircleShape shape;
    shape.m_radius = size.height/(30*2);
    body = world.CreateBody(&def);
    body->CreateFixture(&shape,1);
    
    scheduleUpdate();
    CCLOG("Content size %f %f", size.width,size.height);
}

void Ball::update(float dt){
    b2Vec2 vec = body->GetPosition();
    Vec2 vector = helper::toVec2(vec);
    setPosition(vector);
}


Ball::Ball(){
    
    
}

Ball::~Ball(){
    
}
