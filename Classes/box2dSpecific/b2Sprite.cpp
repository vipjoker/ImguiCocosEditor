//
// Created by Oleh on 2/12/18.
//

#include "b2Sprite.h"

USING_NS_CC;

bool b2Sprite::init() {
    if (!Sprite::init()) {
        return false;
    }

    // scheduleUpdate();


    return true;
}


void b2Sprite::update(float dt) {
    if (body) {
        setPosition(helper::toVec2(body->GetPosition()));
        setRotation(-MATH_RAD_TO_DEG(body->GetAngle()));
    }

}

void b2Sprite::setBody(b2Body *body) {
    this->body = body;
}

void b2Sprite::createSquareFixture() {
    EditableDrawNode *editableDrawNode = EditableDrawNode::create();
    editableDrawNodes.pushBack(editableDrawNode);
    addChild(editableDrawNode);
}

void b2Sprite::onEnter() {
    Node::onEnter();
}

void b2Sprite::setPosition(cocos2d::Vec2 position) {
    Sprite::setPosition(position);


}


b2Body *b2Sprite::getBody() const {
    return body;
}

cocos2d::Vector<EditableDrawNode *> *b2Sprite::getEditableDrawNodes() {
    return &editableDrawNodes;
}

b2Body *b2Sprite::createBody(b2World *world) {
    b2Vec2 pos = helper::tob2Vec(getPosition());
    bodyDef.position.Set(pos.x, pos.y);
    body = world->CreateBody(&bodyDef);

    for (EditableDrawNode *fixtureNode: editableDrawNodes) {
        b2FixtureDef *fixtureDef = fixtureNode->getFixture();
        body->CreateFixture(fixtureNode->getFixture());
        delete fixtureDef->shape;
    }

    return body;
}


void b2Sprite::showEditablePoints() {
    for (EditableDrawNode *editableDrawNode:editableDrawNodes)
        editableDrawNode->setVisible(true);
}

void b2Sprite::hideEditablePoints() {
    for (EditableDrawNode *editableDrawNode:editableDrawNodes)
        editableDrawNode->setVisible(false);
}





