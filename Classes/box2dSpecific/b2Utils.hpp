//
//  b2Utils.hpp
//  Box2dEditor
//
//  Created by Oleh Mahobey on 8/26/17.
//
//

#ifndef b2Utils_hpp
#define b2Utils_hpp

#include "cocos2d.h"
#include "Box2D/Box2D.h"

#define B2D_RATIO 32.0f

USING_NS_CC;
namespace helper {
    Vec2 toVec2(const b2Vec2 &vec);

    b2Vec2 tob2Vec(Vec2 vec);

    float toB2d(float length);

    float fromB2d(float length);

    b2Body *createSquare(b2World &world, Vec2 pos, Vec2 *points, int count);

    b2Body *createGround(b2World &world);

    b2Body *createCircle(b2World &world, float radius, Vec2 pos = Vec2::ZERO, float friction = 0.5, float density = 1,
                         float restitution = .5);

    b2Body *createBike(b2World &world);

    void createCell(b2World &world);
}
#endif /* b2Utils_hpp */
