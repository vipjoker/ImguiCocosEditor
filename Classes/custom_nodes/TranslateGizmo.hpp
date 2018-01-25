//
//  TranslateGizmo.hpp
//  SpritebuilderIOS
//
//  Created by Oleh on 10/28/17.
//

#ifndef TranslateGizmo_hpp
#define TranslateGizmo_hpp
#include "Gizmo.hpp"
class Gizmo;
class TranslateGizmo:public Gizmo{
public:
    virtual void redraw() override;
    static TranslateGizmo *create(BaseModel *model);
    TranslateGizmo(BaseModel *model):Gizmo(model){};

};
#endif /* TranslateGizmo_hpp */
