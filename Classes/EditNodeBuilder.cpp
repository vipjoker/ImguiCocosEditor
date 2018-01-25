//
// Created by oleh on 28.11.17.
//

#include "include/EditNodeBuilder.h"

Editor::NodeTreeT *EditNodeBuilder::createSpriteNode(string spriteName) {
    NodeTreeT *node = createNode();
    cocos2d::SpriteFrame *spriteFrame =  cocos2d::SpriteFrameCache::getInstance()->getSpriteFrameByName(spriteName);
    cocos2d::Size size = spriteFrame->getTexture()->getContentSize();
    Sizef *sizef = new Sizef(size.width,size.height);
    node->size.reset(sizef) ;
    node->type = NodeType_SPRITE;
    node->component.type = Editor::Component::Component_Sprite;
    node->component.value = new SpriteT();

    static_cast<SpriteT*>(node->component.value)->frameName = spriteName;
    return node;
}

Editor::NodeTreeT *EditNodeBuilder::createButton() {
//    "default_btn"
    NodeTreeT *node = createNode();
    ButtonT *buttonT = new ButtonT();
    buttonT->textureNormal = "default_btn";
    buttonT->textureSelected= "default_btn";
    buttonT->textureDisabled = "default_btn";
    node->type = NodeType_BUTTON;
    node->component.type = Editor::Component_Button;
    node->component.value = buttonT;
    return node;
}

Editor::NodeTreeT *EditNodeBuilder::createLabel() {
    NodeTreeT *node = createNode();
    LabelT *label = new LabelT();
    label->text = "Label";
    node->type = NodeType_LABEL;
    node->component.type = Editor::Component_Label;
    node->component.value = label;
    return node;
}

Editor::NodeTreeT *EditNodeBuilder::createNode() {

    NodeTreeT *node = new NodeTreeT();
    Vec2f *vec2f = new Vec2f(50, 50);
    Vec2f *anchor = new Vec2f(0,0);


    node->position = unique_ptr<Vec2f>(vec2f);
    node->anchor = unique_ptr<Vec2f>(anchor);
    node->size = unique_ptr<Sizef>(new Sizef(0,0));
    node->color = unique_ptr<Vec4f>(new Vec4f(1,1,1,1));
    return node;
}

void EditNodeBuilder::createDefaultPhysics(Editor::NodeTreeT *nodeTreeT) {
    BodyT *body = new BodyT();
    body->type = BodyType::BodyType_DYNAMIC;
    body->pos.reset(new Vec2f(0,0));
    FixtureT *fixtureT = new FixtureT();
    fixtureT->type = FixtureType_POLYGON;
    fixtureT->name = "Fixture";
    fixtureT->density = 1;
    fixtureT->friction = 0.5;
    fixtureT->restitution = 0.5;
    fixtureT->points.push_back(Vec2f(0,0));
    fixtureT->points.push_back(Vec2f(0,10));
    fixtureT->points.push_back(Vec2f(10,10));
    fixtureT->points.push_back(Vec2f(10,0));
    body->fixtures.push_back(unique_ptr<FixtureT>(fixtureT));

    nodeTreeT->physics.reset(body);

}

bool EditNodeBuilder::containsPoint(Editor::NodeTreeT *node, cocos2d::Vec2 point) {

    cocos2d::Rect r(node->position->x(),node->position->y(),node->size->width(),node->size->height());

    point.rotate(r.origin,MATH_DEG_TO_RAD(node->rotation));
    return r.containsPoint(point);
//    return true;

}
