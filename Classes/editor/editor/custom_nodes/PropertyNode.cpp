//
//  PropertyNode.cpp
//  SpritebuilderIOS
//
//  Created by Oleh on 11/4/17.
//

#include "PropertyNode.hpp"
bool PropertyNode::init() {
    if(!ui::ListView::init()){
        return false;
    }
    setBackGroundColorType(cocos2d::ui::Layout::BackGroundColorType::SOLID);
    setBackGroundColor(Color3B(50,50,50));
    return true;
    
}
