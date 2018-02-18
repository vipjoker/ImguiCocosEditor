//
// Created by Oleh on 2/14/18.
//

#ifndef TEMPLATE_CASTUTIL_H
#define TEMPLATE_CASTUTIL_H

#include "cocos2d.h"
#include "ui/CocosGUI.h"
enum NodeType{
    NODE,SPRITE,LABEL,LAYOUT,BUTTON
};

class CastUtil {
public:
    static NodeType getType(cocos2d::Node *node);
};


#endif //TEMPLATE_CASTUTIL_H
