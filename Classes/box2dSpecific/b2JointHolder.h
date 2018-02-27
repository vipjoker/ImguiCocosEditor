//
// Created by oleh on 27.02.18.
//

#ifndef MYGAME_B2JOINTHOLDER_H
#define MYGAME_B2JOINTHOLDER_H


#include "b2Sprite.h"
#include <iostream>
class b2JointHolder {
    b2Sprite *bodyA;
    b2Sprite *bodyB;

public:
    enum JointType{
        DISTANCE,FRICTION,GEAR,MOTOR,MOUSE,PRISMATIC,PULLEY,REVOLUTE,ROPE,WELD,WHEEL
    };
    b2JointDef *jointDef;
    b2JointHolder(b2Sprite *bodyA,b2Sprite *bodyB,JointType type);

    ~b2JointHolder();
    b2JointDef *createJointByType(JointType type);
};


#endif //MYGAME_B2JOINTHOLDER_H
