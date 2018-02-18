//
// Created by oleh on 27.11.17.
//

#include <cocos/ui/UIButton.h>
#include "include/NodeBuilder.h"
#include <typeinfo>

void NodeBuilder::buildNode(Editor::EditorRootT *editorRoot, Node *parent) {


    for (int i = 0; i < editorRoot->nodes.size(); i++) {

        NodeTreeT *nodeTree = editorRoot->nodes[i].get();
        if (!nodeTree->children.empty()) {

        }
        Node *node;
        switch (nodeTree->type) {
            case NodeType_SPRITE:
                node = parseSprite(nodeTree, parent);
                break;
            case NodeType_LABEL:
                node = parseLabel(nodeTree, parent);
                break;
            case NodeType_BUTTON:
                node = parseButton(nodeTree, parent);
                break;
            case NodeType_UI_LIST_VIEW:
                node = parseListView(nodeTree, parent);
                break;
            case NodeType_UI_SCROLL_VIEW:
                node = parseScrolView(nodeTree, parent);
                break;
            case NodeType_LAYOUT:
                node = parseLayout(nodeTree, parent);
                break;
            default:
                std::cout << "Unknown node type " << nodeTree->type << endl;
                exit(-1);

        }

        if (nodeTree->position) node->setPosition(nodeTree->position->x(), nodeTree->position->y());
        if (nodeTree->scale) node->setScale(nodeTree->scale->x(), nodeTree->scale->y());
        if (nodeTree->size)node->setContentSize(cocos2d::Size(nodeTree->size->width(), nodeTree->size->height()));
        if (nodeTree->anchor)node->setAnchorPoint(Vec2(nodeTree->anchor->x(), nodeTree->anchor->y()));

        if (nodeTree->color){
            Color4F color4F(nodeTree->color->r(), nodeTree->color->g(), nodeTree->color->b(),nodeTree->color->a());
            node->setColor(Color3B(color4F));
        }
        node->setRotation(nodeTree->rotation);
        node->setLocalZOrder(nodeTree->zOrder);
        node->setName(nodeTree->name);

        if(nodeTree->enablePhysics){
            BodyT *bodyT = nodeTree->physics.get();
            PhysicsBody *body = physicsBuilder.createPhysicsBody(bodyT);
            node->setPhysicsBody(body);
        }

        parent->addChild(node);


    }

}

Node *NodeBuilder::parseSprite(NodeTreeT *nodeTree, Node *parent) {
    SpriteT *spriteT = (SpriteT *) nodeTree->component.value;
    auto sprite = cocos2d::Sprite::createWithSpriteFrameName(spriteT->frameName);
    return sprite;
}

Node *NodeBuilder::parseLabel(NodeTreeT *nodeTree, Node *parent) {
    LabelT *labelT = (LabelT *) nodeTree->component.value;

    cocos2d::Label *label = cocos2d::Label::create();
    label->setString(labelT->text);

    return label;
}

Node *NodeBuilder::parseButton(NodeTreeT *nodeTree, Node *parent) {
    ButtonT *buttonT = (ButtonT *) nodeTree->component.value;
    ui::Button *button = ui::Button::create(buttonT->textureNormal, buttonT->textureSelected, buttonT->textureDisabled,
                                            ui::Button::TextureResType::PLIST);
    return button;
}

Node *NodeBuilder::parseLayout(NodeTreeT *nodeTree, Node *parent) {
    ui::Layout *layout = ui::Layout::create();
    return layout;
}

Node *NodeBuilder::parseScrolView(NodeTreeT *nodeTree, Node *parent) {
    ui::ScrollView *scrollView = ui::ScrollView::create();
    return scrollView;
}

Node *NodeBuilder::parseListView(NodeTreeT *nodeTree, Node *parent) {
    ui::ListView *list = ui::ListView::create();
    return list;
}




