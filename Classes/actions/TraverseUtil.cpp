//
// Created by oleh on 18.02.18.
//

#include "TraverseUtil.h"

void TraverseUtil::traversAllChildren(cocos2d::Node *node, std::function<void(cocos2d::Node *)> callback) {
    for(cocos2d::Node *n:node->getChildren()){
        if(n->getChildrenCount() > 0)traversAllChildren(n,callback);
        callback(n);
    }
}

void TraverseUtil::traversAllParents(cocos2d::Node *node, std::function<void(cocos2d::Node *)> callback) {
    callback(node);
    for (cocos2d::Node *n = node; n != nullptr; n = n->getParent()) {
        callback(n);
    }
}

bool TraverseUtil::isChild(cocos2d::Node *parent, cocos2d::Node *child) {

    for(cocos2d::Node *n:parent->getChildren()){
        if(n->getChildrenCount() > 0){
             if(isChild(n,child)){
                 return true;
             };
        }

        if(n == child)return true;
    }

    return false;
}
