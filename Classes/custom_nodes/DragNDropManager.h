//
// Created by oleh on 30.11.17.
//

#ifndef IMGUIEDITOR_DRAGNDROPMANAGER_H
#define IMGUIEDITOR_DRAGNDROPMANAGER_H

#include "cocos2d.h"

USING_NS_CC;
typedef  std::function<void(Vec2)> Vec2Calback;

class DragNDropManager {
    Node *node;
    Vec2 startDrawNodePosition;
    Vec2 startLocation;
    EventListenerMouse *listener;
    std::function<void(Vec2)> callback;
    bool hastouch = false;
public:
    void addDragNDrop(Node *node,Vec2Calback);
    void countLocation(Vec2 &location);
    void removeDragNDrop();
};


#endif //IMGUIEDITOR_DRAGNDROPMANAGER_H
