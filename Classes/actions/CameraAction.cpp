//
// Created by oleh on 19.02.18.
//

#include "CameraAction.h"

void CameraAction::onMove(cocos2d::Touch *touch, cocos2d::Node *selected, cocos2d::Vector<cocos2d::Node *> *nodes) {
//    cocos2d::Camera *cam = selected->getScene()->getDefaultCamera();
//    cam->setPosition(cam->getPosition() - touch->getDelta());

    selected->getScene()->setPosition(selected->getScene()->getPosition() + touch->getDelta());
}
