//
// Created by oleh on 30.11.17.
//

#include "DragNDropManager.h"

void DragNDropManager::addDragNDrop(Node *node,Vec2Calback posCalback) {
    this->callback = posCalback;
    this->node = node;


    listener = EventListenerMouse::create();

    listener->onMouseDown = [this](EventMouse *mouse) {
        if (mouse->getMouseButton() == EventMouse::MouseButton::BUTTON_LEFT) {

            Vec2 l = mouse->getLocation();
            CCLOG("loacation before %f %f",l.x,l.y);
            countLocation(l);
            Vec2 location = this->node->getParent()->convertToNodeSpace(l);;
            CCLOG("loacation after %f %f",location.x,location.y);
            CCLOG("Bounding box %f %f", this->node->getBoundingBox().origin.x,this->node->getBoundingBox().origin.y);


            this->node->getParent()->convertToWorldSpace(this->node->getPosition());

            if (this->node->getBoundingBox().containsPoint(location)) {
                hastouch = true;
                mouse->stopPropagation();
                startDrawNodePosition = this->node->getPosition();
                startLocation = location;

            }

        }
    };



    listener->onMouseMove = [this](EventMouse *mouse) {

        if (hastouch && mouse->getMouseButton() == EventMouse::MouseButton::BUTTON_LEFT) {

            Vec2 location = mouse->getLocation();
            countLocation(location);

            location = this->node->getParent()->convertToNodeSpace(location);

            Vec2 offset = location - startLocation;
            Vec2 res = startDrawNodePosition + offset;
            this->node->setPosition(res);
            callback(res);
        }
    };

    listener->onMouseUp = [this](EventMouse *mouse) {
        hastouch = false;
    };

    node->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, node);


}

void DragNDropManager::removeDragNDrop() {
    node->getEventDispatcher()->removeEventListener(listener);
}

void DragNDropManager::countLocation(Vec2 &location) {
    location.y = Director::getInstance()->getVisibleSize().height - location.y;
}
