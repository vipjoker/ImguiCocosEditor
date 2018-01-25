//
//  Car.cpp
//  Box2dEditor
//
//  Created by Oleh Mahobey on 8/31/17.
//
//

#include "Car.hpp"
bool Car::init() {
    if(!Node::init()){
        return false;
    }
    
    return true;
}

void Car::createCar(b2World &world){
    b2BodyDef bodyDef;
    
    b2PolygonShape polyShape;
    bodyDef.type  = b2BodyType::b2_dynamicBody;
    b2FixtureDef fixDef ;
    fixDef.shape = &polyShape;
    b2Vec2 array[3];
    array[0] = b2Vec2(1,0);
    array[1] = b2Vec2(-0.6,1);
    array[2] = b2Vec2(-1,0);
    polyShape.Set(array, 3);
    auto b = world.CreateBody(&bodyDef);
    b->CreateFixture(&fixDef);
    b2WheelJointDef wheelJoint;
    b2WheelJointDef backJointDef;
    
    
    auto frontWheel = helper::createCircle(world, .3,Vec2(1.5,0),1.0);
    auto backWheel = helper::createCircle(world, .3,Vec2(-1.5,0),1.0);
    wheelJoint.Initialize(b, frontWheel, b2Vec2(1,-0.5), b2Vec2(0,1));
    backJointDef.Initialize(b, backWheel, b2Vec2(-1,-0.5), b2Vec2(0,1));
    
    wheelJoint.localAnchorB = b2Vec2(0,0);
    
    wheelJoint.maxMotorTorque = 50;
    wheelJoint.motorSpeed = 10;
    backJointDef.localAnchorB = b2Vec2(0,0);
    backJointDef.enableMotor = true;
    backJointDef.maxMotorTorque = 100;
    world.CreateJoint(&wheelJoint);
    backJoint = (b2WheelJoint*) world.CreateJoint(&backJointDef);
    createChain(world, *b);
    
}

void Car::moveForward(bool acc){
    CCLOG("Move forward");
    backJoint->EnableMotor(acc);
    backJoint->SetMotorSpeed(-10);
    
}

void Car::moveBackward(bool acc){
    CCLOG("Move backward");
    backJoint->EnableMotor(acc);
    backJoint->SetMotorSpeed(10);
}
void Car::createChain(b2World &world,b2Body &body){
    b2Body *last = &body;
    b2RevoluteJointDef def;
    def.localAnchorA = b2Vec2(-1,.1);
    def.localAnchorB = b2Vec2(1,.1);
    
    
    
    for (int i =0 ; i < 10; i++) {
        
        b2Body *cur ;//= helper::createSquare(world, Vec2(5 + i * 5,5),1,.2);
        def.bodyA = last;
        def.bodyB = cur;
        world.CreateJoint(&def);
        last = cur;
        
    }
}

void Car::turnLeft(){
    
}

void Car::turnRight(){
    
}
