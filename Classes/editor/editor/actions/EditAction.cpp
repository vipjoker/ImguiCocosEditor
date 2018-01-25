//
//  EditAction.cpp
//  SpritebuilderIOS
//
//  Created by Oleh on 10/9/17.
//

#include "EditAction.hpp"


int pnpoly(int count, float *vertx, float *verty, float testx, float testy)
{
    int i, j, c = 0;
    for (i = 0, j = count-1; i < count; j = i++) {
        
        if ( ((verty[i] > testy) != (verty[j] > testy)) &&
            (testx < (vertx[j] - vertx[i]) * (testy - verty[i]) / (verty[j] - verty[i]) + vertx[i]) )
            c = !c;
    }
    return c;
}

bool EditAction::_contains(BaseModel &model,Vec2 point,DrawType drawType){
    switch (drawType) {
        case CIRCLE:
        {
            float radius = model.points[0].distance(model.points[1]);
         //   for(BaseModel *m : *rects){
                float distance = model.pos.distance(point);
                if(distance < radius)return true;
           // }
            
        }
            break;
        case SQUARE:{
            
        }
            break;
            
        case LINE:{
            
        }
        
    }
    return false;
}

EditAction *EditAction::create(EditorScene *editorScene,std::vector<BaseModel*> *rects){
    EditAction *action = new (std::nothrow)EditAction(editorScene,rects);
    if(action){
        action->autorelease();
        return action;
    }else{
        CC_SAFE_DELETE(action);
        return nullptr;
    }
}

EditAction::EditAction(EditorScene *editorScene,std::vector<BaseModel*> *_rects){
    this->editor = editorScene;
    this->rects = _rects;
}

void handleButtonOpacity(Ref *ref){
    ui::Button *btn = dynamic_cast<ui::Button*>(ref);
    btn->getNormalFile().file = "stop.png";
    if(btn->getOpacity() == 255){
        btn->setOpacity(100);
    }else{
        btn->setOpacity(255);
    }
}

void EditAction::setupToolbar(ui::Layout &layout){
    auto btnPlay = helper::getSymbolButton("triangle.png");
     btnTranslate = helper::getTextButton("Translate");
     btnEdit = helper::getTextButton("Edit");
     btnRotate = helper::getTextButton("Rotate");
    btnPlay->addClickEventListener(std::bind(&EditAction::onStart, this,std::placeholders::_1));
    btnEdit->addClickEventListener(std::bind(&EditAction::onEdit, this,std::placeholders::_1));
    btnTranslate->addClickEventListener(std::bind(&EditAction::onTranslate, this,std::placeholders::_1));
    btnRotate->addClickEventListener(std::bind(&EditAction::onRotate, this,std::placeholders::_1));
    layout.addChild(btnPlay);
    layout.addChild(btnEdit);
    layout.addChild(btnTranslate);
    layout.addChild(btnRotate);
}

void EditAction::onStart(Ref *ref){
    
    handleButtonOpacity(ref);
    editor->play(true);
}

void EditAction::onTranslate(Ref *ref){
    resetButtons();
    mode = EditMode::TRANSLATE;
    handleButtonOpacity(ref);
}

void EditAction::onRotate(Ref *ref){
    resetButtons();
    mode = EditMode::ROTATE;
    handleButtonOpacity(ref);
}

void EditAction::onEdit(Ref *ref){
    resetButtons();
    mode = EditMode::EDIT;
    handleButtonOpacity(ref);
}


bool EditAction::onTouchBegin(EventMouse *event){
//    for(int i = 0 ; i < rects->size();i++){
//        BaseModel *m = (*rects)[i];
//        if(_contains(*m, event->getLocation(), m->type)){
//           
//            clearGizmos();
//            auto bm = Gizmo::create(m);
//            gizmos.pushBack(bm);
//            editor->addChild(bm);
//        }
//    }
    return true;
}
void EditAction::onTouchMove(EventMouse *event){
    
}
void EditAction::onTouchEnd(EventMouse *event){
    
}

void EditAction::resetButtons(){
    for(auto btn : {btnTranslate,btnEdit,btnRotate}){
        btn->setOpacity(255);
    }
}

void EditAction::clearGizmos(){
    for(Gizmo *gizmo:gizmos){
        gizmo->removeFromParent();
    }
}

std::string EditAction::getName(){
    return "Edit";
}
