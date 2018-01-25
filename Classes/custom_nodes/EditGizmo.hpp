//
//  EditGizmo.hpp
//  SpritebuilderIOS
//
//  Created by Oleh on 10/28/17.
//

#ifndef EditGizmo_hpp
#define EditGizmo_hpp

#include "Gizmo.hpp"
class EditGizmo:public Gizmo{
public:
    virtual void redraw() override;
    static EditGizmo *create(BaseModel *model);
    EditGizmo(BaseModel *model):Gizmo(model){}
};
#endif /* EditGizmo_hpp */
