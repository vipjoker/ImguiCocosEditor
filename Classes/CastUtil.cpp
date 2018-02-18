//
// Created by Oleh on 2/14/18.
//

#include "CastUtil.h"
#include <iostream>
CastType CastUtil::getType(cocos2d::Node *node) {

    if (typeid(node) == typeid(cocos2d::Sprite)){
        std::cout << "sprite" <<std::endl;
        return SPRITE;
    }
    else if (typeid(node) == typeid(cocos2d::Label)){
        std::cout << "label"<<std::endl;;
        return LABEL;

    }
    else if (typeid(node) == typeid(cocos2d::ui::Button)) {
        return BUTTON;
    }
    else if(typeid(node) == typeid(cocos2d::ui::Layout)){
        return LAYOUT;
    }
    std::cout << "Node" <<std::endl;;
    return NODE;
}
