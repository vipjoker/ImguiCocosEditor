//
// Created by oleh on 19.02.18.
//

#ifndef MYGAME_CAMERAACTION_H
#define MYGAME_CAMERAACTION_H

#include "EditorAction.h"
#include "cocos2d.h"
class CameraAction :public EditorAction{
public:
    virtual void onMove(cocos2d::Touch *touch,cocos2d::Node *selected, cocos2d::Vector<cocos2d::Node*> *nodes);
};


#endif //MYGAME_CAMERAACTION_H
