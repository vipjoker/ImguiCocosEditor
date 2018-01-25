//
//  MathUtil.cpp
//  SpritebuilderIOS
//
//  Created by Oleh on 10/28/17.
//

#include "MathUtil.hpp"

Vec2 math::getSnappedPoint(Vec2 pointer,int precision){
    
    
    const int PRECISSION = precision;
    int x = pointer.x;
    int y = pointer.y;
    int difx = x%PRECISSION;
    int dify = y%PRECISSION;
    
    pointer.x = x + (difx < PRECISSION/2 ? -(difx):(PRECISSION - difx));
    pointer.y = y + (dify < PRECISSION/2 ? -(dify):(PRECISSION- dify));
    return pointer;
}
