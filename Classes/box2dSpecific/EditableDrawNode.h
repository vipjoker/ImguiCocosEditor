//
// Created by oleh on 22.02.18.
//

#ifndef MYGAME_EDITABLEDRAWNODE_H
#define MYGAME_EDITABLEDRAWNODE_H

#include "cocos2d.h"
#include <vector>
#include "Box2D.h"
class EditableDrawNode :public  cocos2d::DrawNode{

    std::vector<cocos2d::Rect*> rects;
    cocos2d::Rect *selected = nullptr;
    b2FixtureDef fixtureDef;



public:
    enum ShapeType{
        CIRCLE,EDGE,POLY,CHAIN
    };
    ShapeType type = POLY;
    void redraw();
    bool init() override ;

    CREATE_FUNC(EditableDrawNode);
    void setupListener();

    ShapeType getType() const;

    void addPoint(cocos2d::Vec2 point);
    void setType(ShapeType type);

    b2FixtureDef *getFixture();
    cocos2d::Vec2 rectToVec(cocos2d::Rect *rect);
    std::vector<cocos2d::Rect*> *getRects();

    void fromShapeToPoints(b2Shape &shape);


};


#endif //MYGAME_EDITABLEDRAWNODE_H
