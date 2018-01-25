//
// Created by oleh on 27.11.17.
//

#ifndef IMGUIEDITOR_NODEBUILDER_H
#define IMGUIEDITOR_NODEBUILDER_H

#include "cocos2d.h"
#include "EditorRoot_generated.h"
#include "PhysicsBuilder.h"
#include "ui/CocosGUI.h"
#include <iostream>

USING_NS_CC;
using namespace std;
using namespace Editor;


class NodeBuilder {
    PhysicsBuilder physicsBuilder;
public:


    void buildNode(Editor::EditorRootT *editorRoot, Node *parent,NodeTreeT *selected);

private:
    Node *parseSprite(NodeTreeT *nodeTree, Node *parent);

    Node *parseLabel(NodeTreeT *nodeTree, Node *parent);

    Node *parseButton(NodeTreeT *nodeTree, Node *parent);

    Node *parseLayout(NodeTreeT *nodeTree, Node *parent);

    Node *parseScrolView(NodeTreeT *nodeTree, Node *parent);

    Node *parseListView(NodeTreeT *nodeTree,Node *parent);
};


#endif //IMGUIEDITOR_NODEBUILDER_H
