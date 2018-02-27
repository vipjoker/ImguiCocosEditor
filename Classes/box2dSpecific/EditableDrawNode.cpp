//
// Created by oleh on 22.02.18.
//

#include <cocos/base/ccTypes.h>
#include "EditableDrawNode.h"
#include <iostream>
#include "b2Utils.hpp"
USING_NS_CC;
bool EditableDrawNode::init() {
    if(!DrawNode::init()){
        return false;
    }


    auto shape = new b2PolygonShape();;
    shape->SetAsBox(1,1);
    fixtureDef.shape = shape;

    fromShapeToPoints(*shape);

    redraw();
    setupListener();
    return true;
}

void EditableDrawNode::redraw() {
    setLineWidth(1);
    clear();
    Vec2 array[rects.size()];
    int i =0;
    for(cocos2d::Rect *r:rects){
        Color4F c = r == selected ? cocos2d::Color4F::GREEN:cocos2d::Color4F::MAGENTA;
        drawSolidRect(r->origin,cocos2d::Vec2(r->getMaxX(),r->getMaxY()),c);
        array[i++] = r->origin + r->size/2;
    }

    Color4F Red(1,0,0,1);
    Color4F RedTransparent(1,0,0,0.3);

    switch (type){
        case CIRCLE:{
            float distance = array[0].getDistance(array[1]);
            drawSolidCircle(Vec2::ZERO,distance,0,32,RedTransparent);
            drawCircle(Vec2::ZERO,distance,0,32,true,Red);
        }
            break;
        case POLY:{
            drawSolidPoly(array,rects.size(),RedTransparent);
            drawPoly(array,rects.size(),true,Red);
        }
            break;
        case EDGE:{
            drawLine(array[0],array[1],Red);
        }
            break;
        case CHAIN:{
            drawPoly(array,rects.size(),false,Red);
        }
            break;

    }



}
void EditableDrawNode::setupListener() {
    EventListenerTouchOneByOne *listenerTouchOneByOne = EventListenerTouchOneByOne::create();
    listenerTouchOneByOne->onTouchBegan = [this](Touch *touch,Event *event){
        for(cocos2d::Rect *r:rects){
            Vec2 v = convertTouchToNodeSpace(touch);
            if(r->containsPoint(v)){
                selected =r;
                return true;
            }
        }
        return false;
    };

    listenerTouchOneByOne->onTouchMoved = [this](Touch *touch,Event *event){
        if(selected){
            if(type == CIRCLE) {
                if (selected == rects.at(0)) {
                    rects.at(1)->origin += touch->getDelta();
                }
            }
            selected->origin += touch->getDelta();
            redraw();
        }

    };

    listenerTouchOneByOne->onTouchEnded = [this](Touch *touch,Event *event){
        selected = nullptr;
        redraw();
    };
    listenerTouchOneByOne->setSwallowTouches(true);


    getEventDispatcher()->addEventListenerWithSceneGraphPriority(listenerTouchOneByOne,this);
}

EditableDrawNode::ShapeType EditableDrawNode::getType() const {
    return type;
}

void EditableDrawNode::setType(EditableDrawNode::ShapeType type) {
    EditableDrawNode::type = type;
}

b2FixtureDef *EditableDrawNode::getFixture() {

    switch(type){
        case CIRCLE:{
            b2CircleShape *shape = new b2CircleShape();


            b2Vec2 a = helper::tob2Vec(rectToVec(rects.at(0)));
            b2Vec2 b = helper::tob2Vec(rectToVec(rects.at(1)));
            float radius = b2Distance(a,b);
            shape->m_radius = radius;
            fixtureDef.shape = shape;
        }break;
        case EDGE:{

            b2EdgeShape *shape = new b2EdgeShape();
            b2Vec2 a = helper::tob2Vec(rectToVec(rects.at(0)));
            b2Vec2 b = helper::tob2Vec(rectToVec(rects.at(1)));

            std::cout << "Created edge " << a.x << " " << a.y << std::endl;
            std::cout << "Created edge " << b.x << " " << b.y << std::endl;

            shape->Set(a,b);
            fixtureDef.shape = shape;
        }break;
        case POLY:{
            b2PolygonShape *shape = new b2PolygonShape();

            int count  = rects.size();
            int counter = 0;
            b2Vec2 points[count];
            for(Rect *r : rects){
                points[counter++] = helper::tob2Vec(rectToVec(r));
            }
            shape->Set(points,count);

            fixtureDef.shape = shape;



        }break;
        case CHAIN:{
            b2ChainShape *shape = new b2ChainShape();

            int count  = rects.size();

            int counter = 0;
            b2Vec2 points[count];
            for(Rect *r : rects){
                points[counter++] = helper::tob2Vec(rectToVec(r));
            }
            shape->CreateChain(points,count);


            fixtureDef.shape = shape;

        }break;
    }


    return &fixtureDef;
}

std::vector<cocos2d::Rect *> *EditableDrawNode::getRects() {
    return &rects;
}

void EditableDrawNode::addPoint(cocos2d::Vec2 point) {

    rects.push_back(new cocos2d::Rect(point - cocos2d::Vec2(5,5),cocos2d::Size(10,10)));

}

cocos2d::Vec2 EditableDrawNode::rectToVec(cocos2d::Rect *rect) {
    return Vec2(rect->origin + rect->size/2);
}

void EditableDrawNode::fromShapeToPoints(b2Shape &shape) {

    switch(shape.m_type){
        case b2Shape::Type::e_circle:{
            const b2CircleShape *sh = dynamic_cast<const b2CircleShape *>(&shape);
            Vec2 center = helper::toVec2(sh->m_p);
            addPoint(center);
            float radius = helper::fromB2d(sh->m_radius);
            addPoint(center + cocos2d::Vec2(radius,0));
        }break;
        case b2Shape::Type::e_polygon:{
            const b2PolygonShape *sh = dynamic_cast<const b2PolygonShape *>(&shape);

            for(int i = 0 ; i < sh->GetVertexCount();i++){
                addPoint(helper::toVec2(sh->GetVertex(i)));
            }

        }break;
        case b2Shape::Type::e_chain:{

        }break;
        case b2Shape::Type::e_edge:{

        }break;
    }
}

