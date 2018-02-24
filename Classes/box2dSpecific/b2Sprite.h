//
// Created by Oleh on 2/12/18.
//

#ifndef TEMPLATE_B2SPRITE_H
#define TEMPLATE_B2SPRITE_H

#include <iostream>
#include "cocos2d.h"
#include "Box2D.h"
#include "b2Utils.hpp"

#include "EditableDrawNode.h"

class b2Sprite : public cocos2d::Sprite{
    b2Body *body = nullptr;
public:
    cocos2d::Vector<EditableDrawNode*>editableDrawNodes;
    b2Body *getBody() const;
    b2BodyDef bodyDef;
    bool init() override;
    void update(float dt) override;
    void onEnter() override;
    void setBody(b2Body *body);
    void createSquareFixture();
    virtual void setPosition(const cocos2d::Vec2 position);
    cocos2d::Vector<EditableDrawNode*> *getEditableDrawNodes();
    CREATE_FUNC(b2Sprite);
    b2Body *createBody(b2World *world);


    void showEditablePoints();
    void hideEditablePoints();

};


#endif //TEMPLATE_B2SPRITE_H
