//
// Created by oleh on 28.11.17.
//

#ifndef IMGUIEDITOR_EDITNODEBUILDER_H
#define IMGUIEDITOR_EDITNODEBUILDER_H

#include "cocos2d.h"
#include "EditorRoot_generated.h"
using namespace std;
using namespace Editor;
class EditNodeBuilder {
public:
    Editor::NodeTreeT *createSpriteNode(string spriteName);
    Editor::NodeTreeT *createButton();
    Editor::NodeTreeT *createLabel();
    Editor::NodeTreeT *createNode();
    void createDefaultPhysics(Editor::NodeTreeT* nodeTreeT);

    static bool containsPoint(Editor::NodeTreeT *node, cocos2d::Vec2 point);
};


#endif //IMGUIEDITOR_EDITNODEBUILDER_H
