//
//  BaseModel.hpp
//  SpritebuilderIOS
//
//  Created by Oleh on 10/19/17.
//

#ifndef BaseModel_hpp
#define BaseModel_hpp

#include <stdio.h>
#include "cocos2d.h"
USING_NS_CC;
enum DrawType{
   CIRCLE,SQUARE,LINE
};
struct BaseModel{
    DrawType type;
    std::vector<Vec2> points;
    Vec2 pos;
    bool isPressed;
    
    BaseModel(DrawType type,Vec2 position) :type(type),pos(position),isPressed(false)
    {
    }
    
};

#endif /* BaseModel_hpp */
