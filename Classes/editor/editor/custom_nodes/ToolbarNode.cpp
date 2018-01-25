//
//  ToolbarNode.cpp
//  SpritebuilderIOS
//
//  Created by Oleh on 11/4/17.
//

#include "ToolbarNode.hpp"

bool ToolbarNode::init(){
    if(!ui::Layout::init()){
        return false;
    }
    setBackGroundImageScale9Enabled(true);
    setBackGroundImage(res::back_toolbar);
    setLayoutType(ui::Layout::Type::HORIZONTAL);
    setSpacing(10);
    return true;
}
