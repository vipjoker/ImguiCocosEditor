//
//  Gizmo.hpp
//  SpritebuilderIOS
//
//  Created by Oleh on 10/21/17.
//

#ifndef Gizmo_hpp
#define Gizmo_hpp

#include "cocos2d.h"
#include "BaseModel.hpp"

USING_NS_CC;

class Gizmo : public Node{
protected:
    BaseModel *basemodel;
    DrawNode *drawNode;
    Rect touchableArea;
    bool isPressed;
    Vec2 offset;
    
    
public:
    Gizmo(BaseModel *model):basemodel(model){}
    bool init();
    virtual void redraw() = 0;
};

#endif /* Gizmo_hpp */
