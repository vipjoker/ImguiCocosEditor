//
// Created by Oleh on 2/11/18.
//

#include "SelectionAction.h"

USING_NS_CC;

void SelectionManager::clearSelection() {
    for (Node *n: nodes) {
        n->setLocalZOrder(n->getLocalZOrder() - 100);
        n->setColor(Color3B::WHITE);
        Node *drawNode = n->getChildByTag(777);
        if (drawNode)drawNode->removeFromParent();
    }
    nodes.clear();
}

void SelectionManager::addSelection(cocos2d::Node *node) {
    if (!nodes.contains(node)) {
        node->setLocalZOrder(node->getLocalZOrder() + 100);
        node->setColor(Color3B::YELLOW);
        auto drawNode = DrawNode::create();
        drawNode->setTag(777);
        node->addChild(drawNode);
        cocos2d::Rect r = node->getBoundingBox();
        drawNode->drawRect(Vec2::ZERO, r.size, Color4F::RED);
        nodes.pushBack(node);
    }
}

const Vector<cocos2d::Node *> SelectionManager::getNodes() {
    return nodes;
}

