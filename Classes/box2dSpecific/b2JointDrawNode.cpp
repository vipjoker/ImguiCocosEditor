//
// Created by oleh on 22.02.18.
//

#include "b2JointDrawNode.h"

bool b2JointDrawNode::init() {
    if(!DrawNode::init()){
        return false;
    }



    return true;
}

b2JointDef *b2JointDrawNode::createPhysics() {
    jointDef.bodyA = bodyA->getBody();
    jointDef.bodyB = bodyB->getBody();
    return &jointDef;
}

void b2JointDrawNode::updateDrawNode() {
    clear();
    if(bodyA && bodyB){
        drawLine(bodyA->getPosition(),bodyB->getPosition(),Color4F::RED);
    }
}

void b2JointDrawNode::initWithSprites(b2Sprite *a, b2Sprite *b) {
    b2JointDrawNode::bodyA = a;
    b2JointDrawNode::bodyB = b;
    updateDrawNode();
}
