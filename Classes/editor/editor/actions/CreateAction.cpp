//
//  DrawAction.cpp
//  SpritebuilderIOS
//
//  Created by Oleh on 10/9/17.
//

#include "CreateAction.hpp"

CreateAction *CreateAction::create(EditorScene *editorScene,std::vector<BaseModel*> *rects){
    CreateAction *action = new (std::nothrow)CreateAction(editorScene,rects);
    if(action){
        action->autorelease();
       
        return action;
    }else{
        CC_SAFE_DELETE(action);
        return nullptr;
    }
}

CreateAction::CreateAction(EditorScene *editorScene,std::vector<BaseModel*> *rects){
    editor = editorScene;
    this->rects = rects;
     currentModel = nullptr;
}

void CreateAction::setupToolbar(ui::Layout &layout){
     btnCircle = helper::getSymbolButton("circle.png");
     btnRect =helper::getSymbolButton("rect.png");
     btnLine = helper::getSymbolButton("line.png");
    
    resetButtons();
    btnCircle->addClickEventListener(std::bind(&CreateAction::onCreateCircle, this,std::placeholders::_1));
    btnRect->addClickEventListener(std::bind(&CreateAction::onCreateSquare, this,std::placeholders::_1));
    btnLine->addClickEventListener(std::bind(&CreateAction::onCreateLine,this,std::placeholders::_1));
    layout.addChild(btnCircle);
    layout.addChild(btnRect);
    layout.addChild(btnLine);
    onCreateCircle(nullptr);
}

void CreateAction::onCreateCircle(Ref *ref){
    resetButtons();
    btnCircle->setColor(Color3B::GREEN);
    type = DrawType::CIRCLE;
    
}

void CreateAction::onCreateSquare(Ref *ref){
    resetButtons();
    btnRect->setColor(Color3B::GREEN);
    type = DrawType::SQUARE;
}

void CreateAction::onCreateLine(Ref *ref){
    resetButtons();
    btnLine->setColor(Color3B::GREEN);
    type = DrawType::LINE;
}


bool CreateAction::onTouchBegin(EventMouse *event){
    Vec2 loc = event->getLocation();
    switch (type) {
        case CIRCLE:{
            
            BaseModel *b = new BaseModel(CIRCLE,loc);
            b->points.push_back(Vec2::ZERO);
            b->points.push_back(Vec2(10,0));
            rects->push_back(b);
          
            break;
        }
        case SQUARE:{
            
            BaseModel *c = new BaseModel(SQUARE,loc);
            c->points.push_back(Vec2(10,10));
            c->points.push_back(Vec2(10,-10));
            c->points.push_back(Vec2(-10,-10));
            c->points.push_back(Vec2(-10,10));
            rects->push_back(c);
            break;
        }
        case LINE:
            if(currentModel == nullptr){
                currentModel = new BaseModel(LINE,loc);
                currentModel->points.push_back(loc);
                rects->push_back(currentModel);
                
            }else{
                currentModel->points.push_back(event->getLocation());
                if(event->getMouseButton() == EventMouse::MouseButton::BUTTON_RIGHT){
                    currentModel = nullptr;
                }
            }
            break;
    }
    
    
    return true;
}

void CreateAction::onTouchMove(EventMouse *event){
    
}
void CreateAction::onTouchEnd(EventMouse *event){
    
}

void CreateAction::resetButtons(){
    
    for(auto btn:{btnLine,btnCircle,btnRect}){
        btn->setColor(Color3B::WHITE);
    }
}

std::string CreateAction::getName(){
    return "Create";
}
