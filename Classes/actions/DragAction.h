//
// Created by oleh on 20.02.18.
//

#ifndef MYGAME_DRAGACTION_H
#define MYGAME_DRAGACTION_H

#include "cocos2d.h"

class DragAction {
public:
    void onMove(cocos2d::Touch *touch,cocos2d::Node *selected, cocos2d::Vector<cocos2d::Node*> *nodes);
};


#endif
