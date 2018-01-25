//
//  b2Utils.cpp
//  Box2dEditor
//
//  Created by Oleh Mahobey on 8/26/17.
//
//

#include "b2Utils.hpp"


namespace helper {
    
    
    
    Vec2 toVec2(b2Vec2 &vec){
        return Vec2(vec.x,vec.y) * B2D_RATIO;
    }
    b2Vec2 tob2Vec(Vec2 vec){
        vec *= 1/B2D_RATIO;
        b2Vec2 v(vec.x,vec.y) ;
        return v;
    }
    
    
    enum _entityCategory {
        BALLS =          0x0001,
        BOUNDARIES =     0x0002
        
    };
    
    
    b2Body *createSquare(b2World &world,Vec2 pos,Vec2 *points,int count){
        b2Vec2 array[count];
        
        for(int i = 0; i < count; i++){
            Vec2 v = points[i]/30;
            array[i].Set(v.x, v.y);
        }
        
        
        b2PolygonShape shape;
        shape.Set(array, count);
        b2BodyDef def ;
        pos = pos/30;
        def.position.Set(pos.x, pos.y);
        def.type = b2BodyType::b2_dynamicBody;
        
        b2Body *b = world.CreateBody(&def);
        b->CreateFixture(&shape,1);
        return b;
    }
    
    
    b2Body *createGround(b2World &world){
        
        b2ChainShape shape;
        
        
        b2Vec2 points[4];
        points[0].Set(-10,2);
        points[1].Set(-10,1);
        points[2].Set(40,1);
        points[3].Set(40,2);
        
        shape.CreateChain(points, 4);
        
        b2BodyDef def;
        def.type = b2BodyType::b2_staticBody;
        auto body = world.CreateBody(&def);
        body->CreateFixture(&shape,1);
        return body;
        
        
    }
    
    b2Body *createCircle(b2World &world, float radius, Vec2 pos ,float friction ,float density,float restitution){
        b2CircleShape shape;
        shape.m_radius  = radius;
        b2BodyDef bodyDef;
        
        bodyDef.type = b2BodyType::b2_dynamicBody;
        bodyDef.position.Set(pos.x, pos.y);
        
        auto body = world.CreateBody(&bodyDef);
        
        b2FixtureDef fixtureDef;
        fixtureDef.friction = friction;
        fixtureDef.density = density;
        fixtureDef.restitution = restitution;
        fixtureDef.shape = &shape;
        
        
        body->CreateFixture(&fixtureDef);
        return body;
    }
    
    void createCell(b2World &world){
        b2BodyDef def;
        def.position.Set(1,5);
        b2PolygonShape shape;
        shape.SetAsBox(3, .1);
        b2FixtureDef boundDef;
        boundDef.filter.categoryBits = BOUNDARIES;
        boundDef.shape = &shape;
        world.CreateBody(&def)->CreateFixture(&boundDef);
        def.position += b2Vec2(0,5);
        world.CreateBody(&def)->CreateFixture(&boundDef);
        def.angle = MATH_DEG_TO_RAD(90);
        def.position -= b2Vec2(2.5,2.5);
        world.CreateBody(&def)->CreateFixture(&boundDef);
        def.position += b2Vec2(5,0);
        world.CreateBody(&def)->CreateFixture(&boundDef);
        b2CircleShape circle;
        def.type = b2BodyType::b2_dynamicBody;
        b2FixtureDef fixtureDef;
        for(int i = 0; i < 30; i++){
            circle.m_radius = 0.1 + 0.4 * rand_0_1();
            fixtureDef.shape = &circle;
            def.position.Set(-1 + rand_0_1() * 4 , 6 + rand_0_1() * 4);
            auto b = world.CreateBody(&def);
            fixtureDef.filter.maskBits = BOUNDARIES;
            fixtureDef.filter.categoryBits = BALLS;
            b->CreateFixture(&fixtureDef);
        }
    }
    
    b2Body *createBike(b2World &world){
        b2BodyDef bodyDef;
        
        b2PolygonShape polyShape;
        bodyDef.type  = b2BodyType::b2_dynamicBody;
        b2FixtureDef fixDef ;
        fixDef.shape = &polyShape;
        b2Vec2 array[3];
        array[0] = b2Vec2(1,0);
        array[1] = b2Vec2(-0.6,1);
        array[2] = b2Vec2(-1,0);
        polyShape.Set(array, 3);
        auto b = world.CreateBody(&bodyDef);
        b->CreateFixture(&fixDef);
        b2WheelJointDef wheelJoint;
        b2WheelJointDef backJoint;
        
        
        auto frontWheel = helper::createCircle(world, .3,Vec2(1.5,0));
        auto backWheel = helper::createCircle(world, .3,Vec2(-1.5,0));
        wheelJoint.Initialize(b, frontWheel, b2Vec2(1,-0.5), b2Vec2(0,1));
        backJoint.Initialize(b, backWheel, b2Vec2(-1,-0.5), b2Vec2(0,1));
        
        wheelJoint.localAnchorB = b2Vec2(0,0);
        
        wheelJoint.maxMotorTorque = 50;
        wheelJoint.motorSpeed = 10;
        backJoint.localAnchorB = b2Vec2(0,0);
        world.CreateJoint(&wheelJoint);
        world.CreateJoint(&backJoint); 
        return b;
        
    }
}
