//
//  CanvasNode.cpp
//  SpritebuilderIOS
//
//  Created by Oleh on 11/4/17.
//

#include "CanvasNode.hpp"
bool CanvasNode::init(){
    if(!ui::Layout::init()){
        return false;
    }
    
    setBackGroundColorType(cocos2d::ui::Layout::BackGroundColorType::SOLID);
    int grey = 20;
    setBackGroundColor(Color3B(grey,grey,grey));
    setContentSize(Size(500,500));
    // setDirection(cocos2d::ui::ScrollView::Direction::BOTH);
    // setInnerContainerSize(Size(2000,2000));
    //   scrollToPercentBothDirection(Point::ANCHOR_MIDDLE, 1, false);
    Rect clip = Rect(getPosition(), getContentSize());
    clippingNode = ClippingRectangleNode::create(clip);
    addChild(clippingNode);
    canvas = Node::create();
    drawNode = DrawNode::create();
    drawNode->setPosition({1000,1000});
    canvas->addChild(drawNode);
    clippingNode->addChild(canvas);
    EventListenerMouse *mouse = EventListenerMouse::create();
    
    mouse->onMouseDown = [this,clip](EventMouse *mouse){
        if(mouse->getMouseButton() == EventMouse::MouseButton::BUTTON_LEFT){
            startDrawNodePosition = canvas->getPosition();
            startLocation = mouse->getLocation();
        }
    };
    
    mouse->onMouseMove = [this,clip](EventMouse *mouse){
        if( mouse->getMouseButton() == EventMouse::MouseButton::BUTTON_LEFT){
            Vec2 offset  = mouse->getLocation() - startLocation;
            canvas->setPosition(startDrawNodePosition + offset);
        }
        
    };
    
    getEventDispatcher()->addEventListenerWithSceneGraphPriority(mouse, this);
    initGrid();
    return true;
}

void CanvasNode::setContentSize(const Size& size) {
    Layout::setContentSize(size);
    if(clippingNode){
        clippingNode->setClippingRegion(Rect(Vec2::ZERO,size));
        CCLOG("RESIZED %f %f",size.width,size.height);
    }
}


void CanvasNode::addCanvasNode(Node *node){
    if(canvas){
        canvas->addChild(node);
    }
    
}


void CanvasNode::initGrid(){
    
    Color4F white = Color4F(1,1,1,0.5f);
    Color4F lightWhite = Color4F(1,1,1,0.2f);
    drawNode->setLineWidth(3);
    for(int i = -2000; i < 2000; i+=10){
        Color4F c = i%100 ? lightWhite:white;
        
        drawNode->drawLine(Vec2(-1000,i), Vec2(1000,i), c);
        drawNode->drawLine(Vec2(i,-1000), Vec2(i,1000), c);
        
    }
}
