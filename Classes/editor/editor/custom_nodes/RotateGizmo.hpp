//
//  RotateGizmo.hpp
//  SpritebuilderIOS
//
//  Created by Oleh on 10/28/17.
//

#ifndef RotateGizmo_hpp
#define RotateGizmo_hpp

#include "Gizmo.hpp"
class RotateGizmo : public Gizmo{
public:
    virtual void redraw();
    static RotateGizmo *create(BaseModel *model);
    RotateGizmo(BaseModel *model):Gizmo(model){
        
    }

    
};

#endif /* RotateGizmo_hpp */
