//
//  CanvasNode.hpp
//  SpritebuilderIOS
//
//  Created by Oleh on 11/4/17.
//

#ifndef CanvasNode_hpp
#define CanvasNode_hpp

#include "cocos2d.h"
#include "ui/CocosGUI.h"
USING_NS_CC;
class CanvasNode:public ui::Layout{
    Vec2 startDrawNodePosition;
    Vec2 startLocation;
    DrawNode *drawNode;
    ClippingRectangleNode *clippingNode;
    Node *canvas;
public:
    CREATE_FUNC(CanvasNode);
    bool init() override;
    void initGrid();
    void setContentSize(const Size& size) override;
    void addCanvasNode(Node *node);
};

#endif /* CanvasNode_hpp */
