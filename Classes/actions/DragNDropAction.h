//
// Created by oleh on 19.02.18.
//

#ifndef MYGAME_DRAGNDROPACTION_H
#define MYGAME_DRAGNDROPACTION_H

#include "cocos2d.h"
#include "TraverseUtil.h"
class DragNDropAction {

    const int DRAW_NODE_TAG = 777;

    bool isChildOfNode(cocos2d::Node *parent, cocos2d::Node *child);
public:
    virtual cocos2d::Node *onBegin(cocos2d::Touch *touch, cocos2d::Vector<cocos2d::Node*> *nodes);

    virtual void onMove(cocos2d::Touch *touch,cocos2d::Node *selected, cocos2d::Vector<cocos2d::Node*> *nodes);

    virtual void onEnd(cocos2d::Touch *touch, cocos2d::Node *selected, cocos2d::Vector<cocos2d::Node*> *nodes);

};


#endif //MYGAME_DRAGNDROPACTION_H
