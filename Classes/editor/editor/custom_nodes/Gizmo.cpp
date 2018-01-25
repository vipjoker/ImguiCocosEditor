//
//  Gizmo.cpp
//  SpritebuilderIOS
//
//  Created by Oleh on 10/21/17.
//

#include "Gizmo.hpp"


//int pnpoly(int size, float *vertx, float *verty, float targetX, float targetY)
//{
//    int i, j, c = 0;
//    for (i = 0, j = size-1; i < size; j = i++) {
//        if ( ((verty[i]>targetY) != (verty[j]>targetY)) &&
//            (targetX < (vertx[j]-vertx[i]) * (targetY-verty[i]) / (verty[j]-verty[i]) + vertx[i]) )
//            c = !c;
//    }
//    return c;
//}


bool Gizmo::init(){
    
    drawNode = DrawNode::create(5);
    addChild(drawNode);
    isPressed = false;
    setPosition(basemodel->pos);
    
    
    
    
    touchableArea.setRect(-20, -20, 40, 40);
    std::string posMsg = StringUtils::format("Position x = %f y = %f \n bounding box w = %f h = %f",getPosition().x,getPosition().y,getBoundingBox().size.width,getBoundingBox().size.height);
    
    auto label = Label::createWithTTF(posMsg, "fonts/arial.ttf", 10);
     label->getFontAtlas()->setAliasTexParameters();
    label->setPosition(Vec2(0,-20));
    addChild(label);
    
    EventListenerMouse *listener = EventListenerMouse::create();
    
    listener->onMouseDown = [this](EventMouse *event){
        
        CCLOG("GIZMO DOWN");
        Vec2 pos =convertToNodeSpace (event->getLocation());
        offset.set(pos.x, pos.y);
        CCLOG("Event location %f %f",event->getLocation().x,event->getLocation().y);
        CCLOG("Event converted location %f %f",pos.x,pos.y);
        
        if(touchableArea.containsPoint(pos)){
            isPressed = true;
            
        }else{
            isPressed = false;
           
        }
        redraw();
        
        EventCustom e("game_custom_event1");
        auto msg = new std::string("hello");

        e.setUserData(msg);

        getEventDispatcher()->dispatchEvent(&e);

    };
    
    listener->onMouseMove = [&](EventMouse *event){
        
        if(isPressed){
            
            Vec2 delta = event->getLocation()  - event->getPreviousLocation();
            

            CCLOG("Loc %f %f",event->getLocation().x,event->getLocation().y);
            this->setPosition(event->getLocation() - offset);
        }
        
      //  CCLOG("GIZMO MOVE");
        
      
    };
    
    listener->onMouseUp = [this](EventMouse *event){
        isPressed = false;
        redraw();
    };
    
   
    
    redraw();
    getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
    CCLOG("dispatchers %d",getEventDispatcher()->getReferenceCount());
    
    return true;
}


