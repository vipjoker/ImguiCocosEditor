//
// Created by oleh on 29.11.17.
//

#ifndef IMGUIEDITOR_NANOVGNODE_H
#define IMGUIEDITOR_NANOVGNODE_H

#include "cocos2d.h"
#include "DragNDropManager.h"
#include "EditorRoot_generated.h"
USING_NS_CC;

class NanoVgNode :public Node{
    DrawNode *drawNode;
    Vec2Calback callback;
    DragNDropManager dragNDropManager;
    Editor::Vec2f *target;
    bool init(Editor::Vec2f *target,Vec2Calback callback) ;
public:
    static NanoVgNode* createWithTarget(Editor::Vec2f *target,Vec2Calback callback);

    virtual void draw(Renderer *renderer, const Mat4& transform, uint32_t flags);
};


#endif //IMGUIEDITOR_NANOVGNODE_H
