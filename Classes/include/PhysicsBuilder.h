//
// Created by oleh on 30.11.17.
//

#ifndef IMGUIEDITOR_PHYSICSBUILDER_H
#define IMGUIEDITOR_PHYSICSBUILDER_H

#include "cocos2d.h"
#include "EditorRoot_generated.h"
USING_NS_CC;


class PhysicsBuilder {
public:
    PhysicsShape *createShapeFromFixture(Editor::FixtureT *fixture);

    PhysicsBody *createPhysicsBody(Editor::BodyT *bode);
};


#endif //IMGUIEDITOR_PHYSICSBUILDER_H
