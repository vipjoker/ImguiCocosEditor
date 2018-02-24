#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "Logger.h"
#include "RessourceManager.h"
#include "FileManager.h"
#include "ModelLoader.h"
#include "NodeBuilder.h"
#include "EditNodeBuilder.h"
#include "NanoVgNode.h"
#include "SelectionAction.h"
#include "b2Scene.h"
#include "b2Utils.hpp"
#include "EditorAction.h"
#include "DragNDropAction.h"
#include "DragAction.h"
#include "CameraAction.h"
#include "b2Sprite.h"
#include "CastUtil.h"
#include "EditorExtensions.h"


USING_NS_CC;
using namespace Editor;
class ImGuiEditor : public cocos2d::Layer {

    float color[3];
    bool showTest = false;
    bool showLog = false;
    int precission = 0;
    b2Scene *scene;
    cocos2d::Label *info;
    cocos2d::Vec2 canvasPosition;
    ResourceManager resourceManager;
    FileManager fileManager;
    NodeBuilder nodeBuilder;
    EditNodeBuilder editNodeBuilder;

    DragNDropAction dragNDropAction;
    DragAction dragAction;
    CameraAction cameraAction;

    LayerColor *canvasNode;

    bool dragEnable = false;
    bool ctrlPressed = false;
    bool c_pressed = false;
    bool no_button_pressed = true;


    bool play = false;
    SelectionManager selectionManager;
    Logger logger;

    std::vector<EditorAction*> editorActions;
    cocos2d::Vector<cocos2d::Node*> flatNodes;

public:

    virtual bool init();

    CREATE_FUNC(ImGuiEditor);

    void setupMenu();

    void drawTreeView();

    void drawCreateView();

    void onFileSaved(std::string path);

    void onFileLoaded(std::string path);

    void onResourceSelected(std::string resource);

    void drawHiararchyEditor();



    void close();

    void showEditWindow();

    void update(float dt) override;

    void onEnter() override;

    void drawToolbar();

    bool onTouchBegin(Touch *touch, Event *unused_event);

    void  onTouchMove(Touch *touch, Event *unused_event);

    void  onToucnEnd(Touch *touch, Event *unused_event);

    void keyBoardPressed(EventKeyboard::KeyCode keyCode, Event *event);

    void keyBoardReleased(EventKeyboard::KeyCode keyCode, Event *event);

};

#endif // __HELLOWORLD_SCENE_H__
