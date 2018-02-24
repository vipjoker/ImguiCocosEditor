//
// Created by oleh on 22.02.18.
//

#ifndef MYGAME_B2JOINTDRAWNODE_H
#define MYGAME_B2JOINTDRAWNODE_H

#include "cocos2d.h"
#include "b2Sprite.h"
class b2JointDrawNode :public cocos2d::DrawNode{




    b2Sprite *bodyA;
    b2Sprite *bodyB;
    b2JointDef jointDef;
public:
    bool init() override ;
    b2JointDef *createPhysics();
    void initWithSprites(b2Sprite *a,b2Sprite *b);
    void updateDrawNode();
    CREATE_FUNC(b2JointDrawNode);
};


#endif //MYGAME_B2JOINTDRAWNODE_H
