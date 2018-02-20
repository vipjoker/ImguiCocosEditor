//
// Created by Oleh on 2/14/18.
//

#include "CastUtil.h"
#include <iostream>

CastType CastUtil::getType(cocos2d::Node *node) {

    if (dynamic_cast<cocos2d::Sprite *>(node)) {
        std::cout << "sprite" << std::endl;
        return SPRITE;
    } else if (dynamic_cast<cocos2d::Label *>(node)) {
        std::cout << "label" << std::endl;;
        return LABEL;

    } else if (dynamic_cast<cocos2d::ui::Button *>(node)) {
        return BUTTON;
    } else if (dynamic_cast<cocos2d::ui::Layout *>(node)) {
        return LAYOUT;
    }
    std::cout << "Node" << std::endl;;
    return NODE;
}

std::string CastUtil::asString(CastType type) {
    switch (type) {
        case SPRITE:
            return "Sprite";
        case LABEL:
            return "Label";
        case BUTTON:
            return "Button";
        case LAYOUT:return "Layout";
        default:return "Node";
    }
}

