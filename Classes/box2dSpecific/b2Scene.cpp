//
// Created by Oleh on 2/12/18.
//

#include "b2Scene.h"
#include <iostream>
float b2Scene::RATIO = 32;
b2Scene *b2Scene::createScene(b2Vec2 gravity) {

    b2Scene *pRet = new(std::nothrow) b2Scene(gravity);
    if (pRet && pRet->init()) {
        pRet->autorelease();

        return pRet;
    } else {
        delete pRet;
        pRet = nullptr;
        return nullptr;
    }
}

b2World *b2Scene::getWorld() {
    return world;
}

void b2Scene::showDebug() {
    b2DebugLayer *layer = b2DebugLayer::create(world,RATIO);
    addChild(layer);
}

b2Scene::~b2Scene() {

    if (world)delete (world);
}

b2Scene::b2Scene(b2Vec2 gravity):Scene() {
    world = new b2World(gravity);
}

bool b2Scene::init() {
    if(!Scene::init()){
         return false;
    }
    scheduleUpdate();
    return true;

}

void b2Scene::update(float dt) {
    world->Step(dt,8,3);


    world->DrawDebugData();
}

