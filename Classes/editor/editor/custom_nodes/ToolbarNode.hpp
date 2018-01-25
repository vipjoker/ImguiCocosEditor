//
//  ToolbarNode.hpp
//  SpritebuilderIOS
//
//  Created by Oleh on 11/4/17.
//

#ifndef ToolbarNode_hpp
#define ToolbarNode_hpp

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "Res.h"
USING_NS_CC;
class ToolbarNode:public ui::Layout{
public:
    bool init() override;
    CREATE_FUNC(ToolbarNode);
};

#endif /* ToolbarNode_hpp */
