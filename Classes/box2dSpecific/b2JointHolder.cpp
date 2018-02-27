//
// Created by oleh on 27.02.18.
//

#include "b2JointHolder.h"

b2JointHolder::b2JointHolder(b2Sprite *bodyA, b2Sprite *bodyB, b2JointHolder::JointType type) {
    this->bodyA = bodyA;
    this->bodyB = bodyB;
    this->jointDef = createJointByType(type);
}

b2JointDef *b2JointHolder::createJointByType(b2JointHolder::JointType type) {

    switch(type){
        case DISTANCE:{
            return new b2DistanceJointDef();
        }
        case FRICTION:{
            return new b2FrictionJointDef();
        }
        case GEAR:{
            return new b2GearJointDef();
        }
        case MOTOR:{
            return new b2MotorJointDef();
        }
        case MOUSE:{
            return new b2MouseJointDef();
        }
        case PRISMATIC:{
            return new b2PrismaticJointDef();
        }
        case PULLEY:{
            return new b2PulleyJointDef();
        }
        case REVOLUTE:{
            return new b2RevoluteJointDef();
        }
        case ROPE:{
            return new b2RopeJointDef();
        }
        case WELD:{
         return new b2WeldJointDef();
        }
        default:{
            return new b2WheelJointDef();
        }
    }
}

b2JointHolder::~b2JointHolder() {
    std::cout << "Removing join holder" << std::endl;
    delete jointDef;
}
