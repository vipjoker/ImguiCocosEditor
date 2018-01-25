//
//  TranslateGizmo.cpp
//  SpritebuilderIOS
//
//  Created by Oleh on 10/28/17.
//

#include "TranslateGizmo.hpp"
TranslateGizmo *TranslateGizmo::create(BaseModel *model){
    TranslateGizmo *gizmo = new(std::nothrow) TranslateGizmo(model);
    if(gizmo){
        gizmo->init();
        gizmo->autorelease();
    }else{
        CC_SAFE_DELETE(gizmo);
        gizmo = nullptr;
    }
    return gizmo;
}

void TranslateGizmo::redraw(){
    drawNode->clear();
    float alpha = isPressed ? 0.5 : 0.2;
    drawNode->drawTriangle(Vec2(0,60), Vec2(5,50),Vec2(-5,50), Color4F(1,0,0,alpha));
    drawNode->drawTriangle(Vec2(60,0), Vec2(50,5),Vec2(50,-5), Color4F(0,1,0,alpha));
    if(isPressed){
        drawNode->drawSolidRect(touchableArea.origin,touchableArea.origin + touchableArea.size ,Color4F(1,1,1,0.2));
        drawNode->drawRect(touchableArea.origin,touchableArea.origin + touchableArea.size ,Color4F::MAGENTA);
    }else{
        drawNode->drawSolidRect(touchableArea.origin,touchableArea.origin + touchableArea.size ,Color4F(1,1,1,.1));
        
    }
    
    drawNode->drawLine(Vec2::ZERO , Vec2(0,50), Color4F(1,0,0,alpha));
    drawNode->drawLine(Vec2::ZERO, Vec2(50,0), Color4F(0,1,0,alpha));
    
}
