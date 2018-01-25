//
//  DrawAction.hpp
//  SpritebuilderIOS
//
//  Created by Oleh on 10/9/17.
//

#ifndef DrawAction_hpp
#define DrawAction_hpp
#include "UiHelper.hpp"
#include "BaseAction.hpp"
#include "EditorScene.h"
#include "BaseModel.hpp"
class EditorScene;

class CreateAction:public BaseAction{
    ui::Button *btnCircle,*btnLine,*btnRect;
    DrawType type;
    std::vector<BaseModel*> *rects;
    EditorScene *editor;
    BaseModel *currentModel;
public:
    CreateAction(EditorScene *editorScene,std::vector<BaseModel*> *rects);
    static CreateAction *create(EditorScene *editorScene,std::vector<BaseModel*> *rects);
    virtual void setupToolbar(ui::Layout &layout);
    
    virtual bool onTouchBegin(EventMouse *event);
    virtual void onTouchMove(EventMouse *event);
    virtual void onTouchEnd(EventMouse *event);
    
    void resetButtons();
    virtual std::string getName();

    void onCreateCircle(Ref *ref);
    void onCreateSquare(Ref *ref);
    void onCreateLine(Ref *ref);
};

#endif /* DrawAction_hpp */
