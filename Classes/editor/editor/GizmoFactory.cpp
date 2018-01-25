//
//  GizmoFactory.cpp
//  SpritebuilderIOS
//
//  Created by Oleh on 10/28/17.
//

#include "GizmoFactory.hpp"

Gizmo *factory::createGizmo(EditMode mode,BaseModel *baseModel){
    switch (mode) {
        case EditMode::EDIT:
            return EditGizmo::create(baseModel);
        case EditMode::ROTATE:
            return RotateGizmo::create(baseModel);
        case EditMode::TRANSLATE:
            return TranslateGizmo::create(baseModel);
        case EditMode::NOT_SET:
            break;
    }
    return nullptr;
}

Node *factory::createNode(BaseModel *model){
    DrawNode *drawNode = DrawNode::create();
    switch (model->type) {
        case CIRCLE:
            drawNode->drawSolidCircle(Vec2::ZERO,model->points[0].distance(model->points[1]),30,32,1,1,Color4F::RED);
            break;
        case SQUARE:{
            std::vector<Vec2> poly;
            for(Vec2 v : model->points){
                poly.push_back(v);
            }
            drawNode->drawSolidPoly(poly.data(), poly.size(), Color4F::YELLOW);
        }
            break;
        case LINE:
            drawNode->drawPoly(model->points.data(), model->points.size(), false, Color4F::MAGENTA);
    }
    return drawNode;
    
}



// switch (rect->type) {
//            case CIRCLE:
//                drawNode->drawSolidCircle(rect->pos,rect->points[0].distance(rect->points[1]),30,32,1,1,Color4F::RED);
//                break;
//            case SQUARE:{
//                std::vector<Vec2> poly;
//                for(Vec2 v : rect->points){
//                    poly.push_back(v + rect->pos);
//                }
//                drawNode->drawSolidPoly(poly.data(), poly.size(), Color4F::YELLOW);
//
//                }
//                break;
//            case LINE:
//                drawNode->drawPoly(rect->points.data(), rect->points.size(), false, Color4F::MAGENTA);
//        }
