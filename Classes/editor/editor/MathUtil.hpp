//
//  MathUtil.hpp
//  SpritebuilderIOS
//
//  Created by Oleh on 10/28/17.
//

#ifndef MathUtil_hpp
#define MathUtil_hpp
#include "cocos2d.h"
USING_NS_CC;

namespace math {
    Vec2 getSnappedPoint(Vec2 p,int precision = 25);
}

#endif /* MathUtil_hpp */
