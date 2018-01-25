//
//  GizmoFactory.hpp
//  SpritebuilderIOS
//
//  Created by Oleh on 10/28/17.
//

#ifndef GizmoFactory_hpp
#define GizmoFactory_hpp

#include <stdio.h>
#include "Gizmo.hpp"
#include "BaseModel.hpp"
#include "EditGizmo.hpp"
#include "TranslateGizmo.hpp"
#include "RotateGizmo.hpp"

enum class EditMode{
    EDIT,TRANSLATE,ROTATE,NOT_SET
};

namespace factory {
    Gizmo *createGizmo(EditMode drawType,BaseModel *model);
    Node *createNode(BaseModel *model);
};


#endif /* GizmoFactory_hpp */
