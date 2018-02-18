//
// Created by Oleh on 2/12/18.
//

#ifndef TEMPLATE_B2SPRITE_H
#define TEMPLATE_B2SPRITE_H

#include "cocos2d.h"
#include "Box2D.h"
#include "b2Utils.hpp"
#include "b2Scene.h"

class b2Sprite :public cocos2d::Sprite{
    b2Body *body;
    bool init() override;
    void update(float dt) override;
    void onEnter() override;
public:
    void setBody(b2Body *body);
    void createCircleBody();
    void createSquareBody();
    CREATE_FUNC(b2Sprite);



};


#endif //TEMPLATE_B2SPRITE_H
