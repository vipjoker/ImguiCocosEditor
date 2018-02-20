//
// Created by oleh on 20.02.18.
//

#include "DragAction.h"

void DragAction::onMove(cocos2d::Touch *touch,cocos2d::Node *selected, cocos2d::Vector<cocos2d::Node*> *nodes) {
    for (cocos2d::Node *n : *nodes)
        n->setPosition(n->getPosition() + touch->getDelta());
}
