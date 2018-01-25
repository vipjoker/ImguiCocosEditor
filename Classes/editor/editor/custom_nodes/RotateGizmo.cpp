//
//  RotateGizmo.cpp
//  SpritebuilderIOS
//
//  Created by Oleh on 10/28/17.
//

#include "RotateGizmo.hpp"


RotateGizmo *RotateGizmo::create(BaseModel *model){
    RotateGizmo *gizmo = new(std::nothrow) RotateGizmo(model);
if(gizmo){
    gizmo->init();
    gizmo->autorelease();
}else{
    CC_SAFE_DELETE(gizmo);
    gizmo = nullptr;
}
return gizmo;
}



void RotateGizmo::redraw(){
    
}
