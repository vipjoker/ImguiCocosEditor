//
// Created by Oleh on 2/12/18.
//

#ifndef TEMPLATE_B2SCENE_H
#define TEMPLATE_B2SCENE_H

#include "cocos2d.h"
#include "Box2D.h"
#include "b2Sprite.h"
#include "b2DebugLayer.h"
#include "TraverseUtil.h"
class b2Scene :public cocos2d::Scene{
    b2World *world;
    b2DebugLayer *layer;
    bool isRunningPhysics = false;
    std::vector<b2JointDef*> jointDefs;

public:
    bool isScheduled();
    static float RATIO;
    static b2Scene *createScene(b2Vec2 gravity);
    b2World *getWorld();
    void showDebug();
    void playPhysics();
    void stopPhysics();
    void translateDebugLayer(cocos2d::Vec2 pos);
    bool init() override ;
    explicit b2Scene(b2Vec2 gravity);
    virtual ~b2Scene();
    void update(float dt) override;

};


#endif //TEMPLATE_B2SCENE_H
