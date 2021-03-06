//
// Created by Oleh on 2/14/18.
//

#ifndef TEMPLATE_CASTUTIL_H
#define TEMPLATE_CASTUTIL_H

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "b2Sprite.h"
#include <typeinfo>
enum CastType{
    NODE,SPRITE,LABEL,LAYOUT,BUTTON
};

class CastUtil {
public:
    static CastType getType(cocos2d::Node *node);

    static std::string asString(CastType type);
};


#endif
