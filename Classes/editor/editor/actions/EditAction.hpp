//
//  EditAction.hpp
//  SpritebuilderIOS
//
//  Created by Oleh on 10/9/17.
//

#ifndef EditAction_hpp
#define EditAction_hpp


#include "BaseAction.hpp"
#include "UiHelper.hpp"
#include "EditorScene.h"
#include "BaseModel.hpp"
#include "ui/CocosGUI.h"
#include "cocos2d.h"
#include "GizmoFactory.hpp"
USING_NS_CC;
class EditorScene;


class EditAction:public BaseAction{
    EditorScene *editor;
    std::vector<BaseModel*> *rects;
    Vector<Gizmo*> gizmos;
    
    
    ui::Button *btnTranslate,*btnEdit,*btnRotate;
    EditMode mode = EditMode::NOT_SET;
    
    bool _contains(BaseModel &model,Vec2 point,DrawType drawType);
public:
    EditAction(EditorScene *editorScene,std::vector<BaseModel*> *rects);
    static EditAction *create(EditorScene *editorScene,std::vector<BaseModel*> *rects);
    virtual void setupToolbar(ui::Layout &layout);
    
    virtual bool onTouchBegin(EventMouse *event);
    virtual void onTouchMove(EventMouse *event);
    virtual void onTouchEnd(EventMouse *event);
    
    virtual std::string getName();
    void resetButtons();
    void clearGizmos();
    
    void onStart(Ref *ref);
    void onTranslate(Ref *ref);
    void onRotate(Ref *ref);
    void onEdit(Ref *ref);
    
    
};
#endif /* EditAction_hpp */
