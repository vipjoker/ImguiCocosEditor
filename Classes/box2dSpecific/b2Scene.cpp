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
    layer = b2DebugLayer::create(world,RATIO);
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

void b2Scene::translateDebugLayer(cocos2d::Vec2 pos) {
    layer->setPosition(pos);
}

void b2Scene::stopPhysics() {
    isRunningPhysics = false;
    unscheduleUpdate();
    Vector<b2Sprite*> sprites;
    TraverseUtil::traversAllChildren(this,[&sprites](cocos2d::Node *n){

        b2Sprite *sprt = dynamic_cast<b2Sprite*>(n);
        if(sprt){
            sprites.pushBack(sprt);
        }
    });

    for(b2Sprite *sprt:sprites){

        sprt->showEditablePoints();
        if(sprt->getBody()){
            auto body = sprt->getBody();
            world->DestroyBody( body);
            sprt->setBody(nullptr);
        }
    }

}

void b2Scene::playPhysics() {
    isRunningPhysics = true;
    Vector<b2Sprite*> sprites;
    TraverseUtil::traversAllChildren(this,[&sprites](cocos2d::Node *n){

        b2Sprite *sprt = dynamic_cast<b2Sprite*>(n);
        if(sprt){
            sprites.pushBack(sprt);
        }
    });
    for(b2Sprite *sprt: sprites){
        sprt->hideEditablePoints();
        sprt->createBody(world);
    }
    std::cout << "Node found " << sprites.size()<< std::endl;
    scheduleUpdate();
}

bool b2Scene::isScheduled() {
    return isRunningPhysics;
}

