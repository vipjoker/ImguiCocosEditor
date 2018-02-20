//
// Created by Oleh on 2/11/18.
//

#ifndef TEMPLATE_SELECTIONACTION_H
#define TEMPLATE_SELECTIONACTION_H

#include "cocos2d.h"

class SelectionManager {
    cocos2d::Vector<cocos2d::Node *> nodes;
public:
    void clearSelection();

    void addSelection(cocos2d::Node *node);

    cocos2d::Vector<cocos2d::Node *> *getNodes();

    static cocos2d::Vec2 pointInView(cocos2d::Touch *touch, cocos2d::Node *node);
};

#endif
