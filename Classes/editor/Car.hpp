//
//  Car.hpp
//  Box2dEditor
//
//  Created by Oleh Mahobey on 8/31/17.
//
//

#ifndef Car_hpp
#define Car_hpp

#include "cocos2d.h"
#include "Box2D/Box2D.h"
#include "b2Utils.hpp"

USING_NS_CC;
class Car : public Node{
    bool init() override;
    
    b2WheelJoint *backJoint;
public:
    CREATE_FUNC(Car);
    void moveForward(bool acc);
    void moveBackward(bool acc);
    void createChain(b2World &world,b2Body &body);
    void turnLeft();
    void turnRight();
    void createCar(b2World &world);
};

#endif /* Car_hpp */
