//
// Created by oleh on 19.02.18.
//

#include "DragNDropAction.h"

cocos2d::Node *DragNDropAction::onBegin(cocos2d::Touch *touch, cocos2d::Vector<cocos2d::Node *> *nodes) {
//TODO not needed
    for (cocos2d::Node *node :*nodes) {
        if (node->getBoundingBox().containsPoint(node->getParent()->convertTouchToNodeSpace(touch))) {
            cocos2d::DrawNode *draw = cocos2d::DrawNode::create();
//            draw->drawRect(cocos2d::Vec2::ZERO, node->getBoundingBox().size, cocos2d::Color4F::RED);
//            draw->setTag(DRAW_NODE_TAG);
//            node->addChild(draw);
            node->setLocalZOrder(100);
            return node;
        }
    }
    return nullptr;
}

void DragNDropAction::onMove(cocos2d::Touch *touch, cocos2d::Node *selected, cocos2d::Vector<cocos2d::Node *> *nodes) {
    if (selected) {
        selected->setPosition(selected->getPosition() + touch->getDelta());
        for (cocos2d::Node *n : *nodes)n->setOpacity(255);

        for (cocos2d::Node *n : *nodes) {
            if (selected == n) continue;

            if (n->getBoundingBox().containsPoint(n->getParent()->convertTouchToNodeSpace(touch))) {

                n->setOpacity(100);
                break;
            }
        }
    }
}

void DragNDropAction::onEnd(cocos2d::Touch *touch, cocos2d::Node *selected, cocos2d::Vector<cocos2d::Node *> *nodes) {
    if (selected) {
        selected->setOpacity(255);
        selected->setLocalZOrder(0);
        cocos2d::Node *n = nullptr;
        if((n = selected->getChildByTag(DRAW_NODE_TAG)))n->removeFromParent();
    }else{
        return;
    }

    for (cocos2d::Node *n : *nodes) {
        if (selected == n) continue;
        if (isChildOfNode(n, selected))continue;


        if (n->getBoundingBox().containsPoint(n->getParent()->convertTouchToNodeSpace(touch))) {
            selected->removeFromParent();
            cocos2d::Vec2 position = n->convertTouchToNodeSpace(touch);
            cocos2d::Vec2 childPosition = selected->convertTouchToNodeSpace(touch);
            selected->setPosition(position);
            n->addChild(selected);
            break;
        }
    }
}

bool DragNDropAction::isChildOfNode(cocos2d::Node *parent, cocos2d::Node *child) {
    if(parent == child)return true;
    for (cocos2d::Node *n = child; n != nullptr; n = n->getParent()) {
        if (parent == n) {
            return true;
        }
    }
    return TraverseUtil::isChild(child,parent);
}
