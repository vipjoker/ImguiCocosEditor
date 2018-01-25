//
//  PropertyNode.hpp
//  SpritebuilderIOS
//
//  Created by Oleh on 11/4/17.
//

#ifndef PropertyNode_hpp
#define PropertyNode_hpp

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "Res.h"
USING_NS_CC;
class PropertyNode:public ui::ListView{
public:
    bool init() override;
    CREATE_FUNC(PropertyNode);
};
#endif /* PropertyNode_hpp */
