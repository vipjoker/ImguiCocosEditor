//
// Created by oleh on 30.11.17.
//

#include "include/PhysicsBuilder.h"

PhysicsShape *PhysicsBuilder::createShapeFromFixture(Editor::FixtureT *fixture) {
    PhysicsMaterial material(fixture->density, fixture->restitution, fixture->friction);

    int size = (int) fixture->points.size();
    if(size == 0)CCLOGERROR("PhysicsBuilder -> createShapeFromFixture fixture points are empty");

    Vec2 points[size];
    for (int i = 0; i < size; i++) {
        points[i].set(fixture->points[i].x(), fixture->points[i].y());
    }

    PhysicsShape *shape = nullptr;
    switch (fixture->type) {
        case Editor::FixtureType_CIRCLE: {
            float radius = points[1].length();
            shape = PhysicsShapeCircle::create(radius, material,points[0]);

            break;
        }

        case Editor::FixtureType_POLYGON: {
            shape = PhysicsShapePolygon::create(points, size, material,points[0]);
            break;
        }
        case Editor::FixtureType_LINE:
            shape = PhysicsShapeEdgeChain::create(points, size, material);
            break;
    }

    return shape;
}

PhysicsBody *PhysicsBuilder::createPhysicsBody(Editor::BodyT *body) {
    if(!body){
        CCLOGERROR("PhysicsBuilder -> createPhysicsBody body is null");
        return nullptr;
    }

    PhysicsBody *physicsBody = PhysicsBody::create();
    if(body->pos){
        physicsBody->setPositionOffset(Vec2(body->pos->x(),body->pos->y()));
    }else{
       CCLOGERROR("PhysicsBuilder -> createPhysicsBody body position is null");
    }
        switch (body->type) {
            case Editor::BodyType_DYNAMIC:
                physicsBody->setDynamic(true);
                break;
            case Editor::BodyType_STATIC:
                physicsBody->setDynamic(false);
                break;
            case Editor::BodyType_KINEMATIC:
                physicsBody->setDynamic(false);
                break;
        }

    if(!body->fixtures.size() == 0){
//        CCLOGERROR("PhysicsBuilder -> fixtures are empty");
    }else{
        for (int f = 0; f < body->fixtures.size(); f++) {
            Editor::FixtureT *fixtureT = body->fixtures[f].get();
            PhysicsShape *shape = createShapeFromFixture(fixtureT);
            physicsBody->addShape(shape);
        }
    }



    return physicsBody;
}


