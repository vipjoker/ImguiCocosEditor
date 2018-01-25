//
//  Ball.hpp
//  Box2dEditor
//
//  Created by Oleh Mahobey on 8/26/17.
//
//

#ifndef Ball_hpp
#define Ball_hpp

#include "cocos2d.h"
#include "Box2D/Box2D.h"
#include "b2Utils.hpp"
USING_NS_CC;
class Ball:public Sprite{
    b2Body *body;
    void update(float dt) override;
public:
    static Ball *createWithFile(const char* file,b2World &world,const Vec2 vec);
    void initPhysics(b2World &world, Vec2 v);
    Ball();
    ~Ball();
    
};
#endif /* Ball_hpp */
