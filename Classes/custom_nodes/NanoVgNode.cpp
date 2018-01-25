//
// Created by oleh on 29.11.17.
//

#include "NanoVgNode.h"

#include <utility>


bool NanoVgNode::init(Editor::Vec2f *target,Vec2Calback callback) {
    if (!Node::init()) {
        return false;
    }
    drawNode = DrawNode::create(1);
    this->target = target;
    setPosition(target->x(),target->y());

    setContentSize(cocos2d::Size(10, 10));

    drawNode->drawSolidRect(Vec2::ZERO, getContentSize(), Color4F(0.1, .8, 0, .9));




    //*****************************

    float alpha = 0.5;

    drawNode->drawTriangle(Vec2(0,60), Vec2(5,50),Vec2(-5,50), Color4F(1,0,0,alpha));
    drawNode->drawTriangle(Vec2(60,0), Vec2(50,5),Vec2(50,-5), Color4F(0,1,0,alpha));
//    if(isPressed){
//        drawNode->drawSolidRect(touchableArea.origin,touchableArea.origin + touchableArea.size ,Color4F(1,1,1,0.2));
//        drawNode->drawRect(touchableArea.origin,touchableArea.origin + touchableArea.size ,Color4F::MAGENTA);
//    }else{
//        drawNode->drawSolidRect(touchableArea.origin,touchableArea.origin + touchableArea.size ,Color4F(1,1,1,.1));
//
//    }
//
    drawNode->drawLine(Vec2::ZERO , Vec2(0,50), Color4F(1,0,0,alpha));
    drawNode->drawLine(Vec2::ZERO, Vec2(50,0), Color4F(0,1,0,alpha));


    //*****************************



    addChild(drawNode);

    this->callback = std::move(callback);
    dragNDropManager.addDragNDrop(this, this->callback);


    return true;
}

void NanoVgNode::draw(Renderer *renderer, const Mat4 &transform, uint32_t flags) {
    Node::draw(renderer, transform, flags);
}

NanoVgNode *NanoVgNode::createWithTarget(Editor::Vec2f *target,Vec2Calback callback) {
    NanoVgNode *pRet = new(std::nothrow) NanoVgNode();
    if (pRet && pRet->init(target,callback))
    {

        pRet->autorelease();
        return pRet;
    }
    else
    {
        delete pRet;
        pRet = nullptr;
        return nullptr;
    }
}



