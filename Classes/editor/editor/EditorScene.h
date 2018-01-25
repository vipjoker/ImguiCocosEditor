//
// Created by omak on 07.09.17.
//

#ifndef MYGAME_EDITORSCENE_H
#define MYGAME_EDITORSCENE_H

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "BaseAction.hpp"
#include "CreateAction.hpp"
#include "EditAction.hpp"
#include "Box2D/Box2D.h"
#include "b2DebugLayer.h"
#include "BaseModel.hpp"
#include "MathUtil.hpp"
USING_NS_CC;


enum class DrawAction{
    SELECT,CREATE 
};





class EditorScene : public Layer{
    
    b2World *world;
    bool isRunning;
    ui::Text *text,*tvAction;
    ui::Layout *toolbar;
    ui::ListView *listView;
    DrawNode *drawNode;
    DrawAction dAction;
    BaseAction *baseAction;
    BaseModel *currentRect;
    std::vector<BaseModel*> rects;
    Vector<BaseAction*> baseActions;
    Rect canvasRect;
    Vec2 pointer;
    ClippingRectangleNode *clippingNode;
    
    
    Vector<Node*> gizmos;
    
    ui::Layout *getToolbar();
    void setupAction(int actionPosition);
    
public:
    bool init();
    CREATE_FUNC(EditorScene);
    static Scene *createScene();
    void update(float dt);
    void redraw();
    void createBox2dObjects();
    void clearGizmos();
    void clearBox2dObjects();
    void play(bool isStart);

};


#endif //MYGAME_EDITORSCENE_H
