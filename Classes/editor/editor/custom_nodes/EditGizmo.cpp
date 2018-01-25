//
//  EditGizmo.cpp
//  SpritebuilderIOS
//
//  Created by Oleh on 10/28/17.
//

#include "EditGizmo.hpp"
EditGizmo *EditGizmo::create(BaseModel *model){
    EditGizmo *gizmo = new(std::nothrow) EditGizmo(model);
    if(gizmo){
        gizmo->init();
        gizmo->autorelease();
    }else{
        CC_SAFE_DELETE(gizmo);
        gizmo = nullptr;
    }
    return gizmo;
}

void EditGizmo::redraw(){
    
}
