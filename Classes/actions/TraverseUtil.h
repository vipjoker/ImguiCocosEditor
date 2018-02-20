//
// Created by oleh on 18.02.18.
//

#ifndef MYGAME_TRAVERSEUTIL_H
#define MYGAME_TRAVERSEUTIL_H

#include "cocos2d.h"
#include <functional>
class TraverseUtil {
public:
    static void traversAllChildren(cocos2d::Node *node,std::function<void(cocos2d::Node*)> callback);
    static bool isChild(cocos2d::Node *parent,cocos2d::Node *child);
    static void traversAllParents(cocos2d::Node *node,std::function<void(cocos2d::Node*)> callback);

};


#endif //MYGAME_TRAVERSEUTIL_H
