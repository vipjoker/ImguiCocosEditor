#include "MainScene.h"
#include "b2Sprite.h"
#include "CastUtil.h"
bool ImGuiEditor::init() {
    if (!Layer::init()) {
        return false;
    }


    canvasNode = LayerColor::create(Color4B(255, 255, 255, 100));
    canvasNode->setContentSize({360, 640});
    canvasNode->setAnchorPoint(cocos2d::Point::ANCHOR_MIDDLE);
    canvasNode->setPosition(Director::getInstance()->getVisibleSize() / 2 - cocos2d::Size(360, 640) / 2);
    addChild(canvasNode, 5);




    fileManager.loadFiles("/");
    resourceManager.addTextureCache("ui/btn_grey.png", "default_btn");
    resourceManager.addTextureCache("ui/sel-frame.png", "frame");
    resourceManager.addTextureCache("triangle.png", "play");
    resourceManager.addTextureCache("stop.png", "stop");
    resourceManager.addTextureCache("ui/rounded_rectangle.png","rrect");

    resourceManager.addTextureCache("HelloWorld.png","helloworld");

    const char *fontPath = FileUtils::getInstance()->fullPathForFilename("fonts/round.otf").c_str();
    ImGui::GetIO().Fonts->AddFontFromFileTTF(fontPath, 15.f);
    CCIMGUI::getInstance()->addImGUI([this]() {
        if (showLog) logger.Draw("Logger", &showLog);
        setupMenu();
        drawTreeView();
        showEditWindow();
        drawCreateView();
        drawToolbar();
        drawHiararchyEditor();
        fileManager.draw();
        resourceManager.draw();
        if (showTest)ImGui::ShowTestWindow(&showTest);
    }, "demoid");


    EventListenerTouchOneByOne *listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = CC_CALLBACK_2(ImGuiEditor::onTouchBegin, this);
    listener->onTouchMoved = CC_CALLBACK_2(ImGuiEditor::onTouchMove, this);
    listener->onTouchEnded = CC_CALLBACK_2(ImGuiEditor::onToucnEnd, this);

    EventListenerKeyboard *keyboard = EventListenerKeyboard::create();
    keyboard->onKeyPressed = CC_CALLBACK_2(ImGuiEditor::keyBoardPressed, this);
    keyboard->onKeyReleased = CC_CALLBACK_2(ImGuiEditor::keyBoardReleased, this);
    getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
    getEventDispatcher()->addEventListenerWithSceneGraphPriority(keyboard, this);
    scheduleUpdate();


    auto userDef = UserDefault::getInstance();
    std::string file = userDef->getStringForKey(FileManager::FILE_PARAM, "");
    std::string dir = userDef->getStringForKey(FileManager::DIR_PARAM, "");
    std::string path = dir + "/" + file;
    std::cout << "init" << std::endl;
    printf("File %s\n", file.c_str());
    printf("Dir %s\n", dir.c_str());
    printf("Path %s\n", path.c_str());
//
//    if(!file.empty() && !dir.empty()){
//        fileManager.init(file,dir);
//        onFileLoaded(dir + "/" + file);
//    }


    return true;
}


bool ImGuiEditor::onTouchBegin(Touch *touch, Event *unused_event) {


    Vec2 lastTouch = canvasNode->convertTouchToNodeSpace(touch);

    if (!ctrlPressed)selectionManager.clearSelection();

    for (Node *n : canvasNode->getChildren()) {
        if (n->getBoundingBox().containsPoint(lastTouch)) {
            selectionManager.addSelection(n);
            return true;
        }
    }
    return true;
}


void ImGuiEditor::onTouchMove(Touch *touch, Event *unused_event) {
    if (dragEnable)
        this->setPosition(this->getPosition() + touch->getDelta());
    else if (!selectionManager.getNodes().empty())
        for (Node *selected:selectionManager.getNodes())
            selected->setPosition(selected->getPosition() + touch->getDelta());


}

void ImGuiEditor::onToucnEnd(Touch *touch, Event *unused_event) {


    //selectedNodes.clear();
}

void ImGuiEditor::setupMenu() {
    static bool createPopup = false;
    static bool openPopup = false;
    static bool openPopupSave = false;
    if (ImGui::BeginMainMenuBar()) {
        if (ImGui::BeginMenu("File")) {
            if (ImGui::MenuItem("Create new"))createPopup = true;
            if (ImGui::MenuItem("Open")) openPopup = true;
            if (ImGui::MenuItem("Save")) openPopupSave = true;
            if (ImGui::MenuItem("Exit")) close();
            ImGui::EndMenu();
        }

        if (ImGui::BeginMenu("View")) {
            if (ImGui::MenuItem("Show console   ")) showLog = true;
            if (ImGui::MenuItem("Show resources ")) resourceManager.setShowWindow(true);
            if (ImGui::MenuItem("Show examples  ")) showTest = true;

            ImGui::EndMenu();
        }
        ImGui::EndMainMenuBar();
    }


    if (createPopup) {
//        editorRoot = new EditorRootT();
        fileManager.saveFile(std::bind(&ImGuiEditor::onFileSaved, this, placeholders::_1));
        createPopup = false;
    }

    if (openPopupSave) {
        fileManager.saveFile(std::bind(&ImGuiEditor::onFileSaved, this, placeholders::_1));
        openPopupSave = false;
    }

    if (openPopup) {
        fileManager.loadFile(std::bind(&ImGuiEditor::onFileLoaded, this, placeholders::_1));
        openPopup = false;
    }
}

void ImGuiEditor::drawTreeView() {


    ImGui::SetNextWindowSize(ImVec2(300, 300), ImGuiSetCond_Once);


    ImGui::SetNextWindowPos(ImVec2(0, 520), ImGuiSetCond_Once);

    ImGui::Begin("Hierarchy");
    if (ImGui::TreeNode("Nodes")) {
        ImGui::Indent();
        int counter = 1;
        for (Node *n: canvasNode->getChildren()) {

            ImGui::PushID(counter++);
            if (ImGui::Selectable(n->getName().empty() ? "Empty" : n->getName().c_str())) {
                selectionManager.clearSelection();
                selectionManager.addSelection(n);
            }


            ImGui::PopID();
        }
        ImGui::Unindent();
        ImGui::TreePop();

    }

    ImGui::End();
}

void ImGuiEditor::close() {
    Director::getInstance()->end();

}

void ImGuiEditor::showEditWindow() {

    ImGuiIO &io = ImGui::GetIO();
    ImVec2 size = io.DisplaySize;

    int width = 500;
    ImGui::SetNextWindowPos(ImVec2(size.x - width, 20), ImGuiSetCond_Once);
    ImGui::SetNextWindowSize(ImVec2(width, 400), ImGuiSetCond_Once);


    ImGui::Begin("Properties");


    if (ImGui::CollapsingHeader("Global properties")) {


        if (ImGui::InputInt("Precission", &this->precission, 5)) {

        }
        if (ImGui::ColorEdit3("Background color", color)) {
            float r = color[0];
            float g = color[1];
            float b = color[2];
            canvasNode->setColor(Color3B(Color4F(r, g, b, 1)));
        }
    }

    if (selectionManager.getNodes().size() == 1) {

        Node *selectedNode = selectionManager.getNodes().at(0);
        if (ImGui::CollapsingHeader("Node properties")) {
            ImGui::Text(selectedNode->getName().empty() ? "Unknown" : selectedNode->getName().c_str());


            char buff[64];
            const char *orig = selectedNode->getName().c_str();
            strcpy(buff, orig);
            ImGui::InputText("Name", buff, 64);
            selectedNode->setName(string(buff));
            Vec2 position = selectedNode->getPosition();
            if (ImGui::DragFloat2("Position", &position.x))selectedNode->setPosition(position);

            Vec2 anchor = selectedNode->getAnchorPoint();
            if (ImGui::DragFloat2("Anchor", &anchor.x, 0.1f, 0, 1))selectedNode->setAnchorPoint(anchor);

            cocos2d::Size conntentSize = selectedNode->getContentSize();
            if (ImGui::DragFloat2("Size", &conntentSize.width))selectedNode->setContentSize(conntentSize);

            Vec2 vec2(selectedNode->getScaleX(), selectedNode->getScaleY());
            if (ImGui::DragFloat2("Scale", &vec2.x, 0.01))selectedNode->setScale(vec2.x, vec2.y);


//            Color4F color4F(editableNodeTree->color->r(), editableNodeTree->color->g(),
//                            editableNodeTree->color->b(), editableNodeTree->color->a());
//
////                colorArray[0] = color4F.r;
////                colorArray[1] = color4F.g;
////                colorArray[2] = color4F.b;
//
//
//            if (ImGui::ColorEdit3("Color", colorArray)) {
//                Color4F c(colorArray[0], colorArray[1], colorArray[2], colorArray[3]);
//                editableNodeTree->color.reset(new Vec4f(c.a, c.r, c.g, c.b));
//            }

            int rotation = selectedNode->getRotation();
            if (ImGui::DragInt("Rotation", &rotation)) {
                selectedNode->setRotation(rotation);
            }

            int zOrder = selectedNode->getLocalZOrder();
            ImGui::InputInt("Z order", &zOrder);
            selectedNode->setLocalZOrder(zOrder);

            //ImGui::Checkbox("Enable physics", &editableNodeTree->enablePhysics);


        }


        if(CastUtil::getType(selectedNode) == CastType::LABEL) {
            if (ImGui::CollapsingHeader("Label properties")) {
                cocos2d::Label *l = dynamic_cast<cocos2d::Label *>(selectedNode);

                char buff[64];
                const char *label = l->getString().c_str();
                strcpy(buff, label);
                if(ImGui::InputText("Name", buff, 64)) l->setString(string(buff));


                l->getTextAlignment()




            }
        }

        if(CastUtil::getType(selectedNode) == CastType::SPRITE){
            if(ImGui::CollapsingHeader("Sprite properties")){


            }
        }



//
//        if (ImGui::CollapsingHeader("Physics")) {
//
//
//            if (editableNodeTree && editableNodeTree->enablePhysics) {
//                const char *items[] = {
//                        "Static", "Dynamic", "Kinematic"
//                };
//
//
//                if (!editableNodeTree->physics) {
//                    editNodeBuilder.createDefaultPhysics(editableNodeTree);
//                }
//
//                BodyT *body = editableNodeTree->physics.get();
//                int type = body->type;
//                //static int position = 0;
//                if (ImGui::Combo("Types", &type, items, 3)) body->type = BodyType(type);
//
//
//                Vec2 pos(body->pos->x(), body->pos->y());
//                if (ImGui::DragFloat2("Body position", &pos.x))body->pos.reset(new Vec2f(pos.x, pos.y));
//
//                ImGui::Text("Points");
//
//
//                for (int i = 0; i < body->fixtures.size(); i++) {
//
//                    if (ImGui::TreeNode(StringUtils::format("Fixture %d", i).c_str())) {
//
//
//                        FixtureT *fixtureT = body->fixtures[i].get();
//
//
//                        const char *fixtureTypes[] = {
//                                "Polygon", "Circle", "Line"
//                        };
//                        int fixtureType = fixtureT->type;
//                        if (ImGui::Combo("Fixture type", &fixtureType, fixtureTypes, 3))
//                            fixtureT->type = FixtureType(fixtureType);
//
//
//                        for (int j = 0; j < fixtureT->points.size(); j++) {
//                            const char *label = StringUtils::format("Point %d", j).c_str();
//                            Vec2 fixPos(fixtureT->points[j].x(), fixtureT->points[j].y());
//                            if (ImGui::DragFloat2(label, &fixPos.x))fixtureT->points[j] = Vec2f(fixPos.x, fixPos.y);
//                            ImGui::SameLine();
//                            ImGui::PushID(j);
//                            if (ImGui::Button("x")) {
//                                fixtureT->points.erase(fixtureT->points.begin() + j);
//                            }
//                            ImGui::PopID();
//                        }
//
//                        if (ImGui::Button("Add point")) {
//                            fixtureT->points.push_back(Vec2f(0, 0));
//                        }
//
//                        ImGui::TreePop();
//                    }
//                }
//            }
//        }

    }

    ImGui::End();

}

void ImGuiEditor::update(float dt) {
    Node::update(dt);

//    if (play) {
//        getScene()->getPhysicsWorld()->step(dt);
//    }


//    else if (editorRoot) {
//        canvasNode->removeAllChildren();
//        placeholderOverlay->removeAllChildren();
//        nodeBuilder.buildNode(editorRoot, canvasNode, editableNodeTree);
//
//
//        for (int i = 0; i < editorRoot->nodes.size(); i++) {
//            NodeTreeT *node = editorRoot->nodes.at(i).get();
//
//            if (editableNodeTree == node) {
//
//                cocos2d::Size size(
//                        node->size->width() == 0 ? cocos2d::Size(100, 100) : cocos2d::Size(node->size->width() + 10,
//                                                                                           node->size->height() + 10));
//
//                cocos2d::Vec2 position(node->position->x(), node->position->y());
//
//            }
//        }
//    }
}

void ImGuiEditor::onFileSaved(std::string path) {
    EditorRootPointer editorRootPointer = editNodeBuilder.saveNode(canvasNode);

    ModelLoader::saveModel(path, editorRootPointer);
    LOGI("Saved %s\n", path.c_str());
}

void ImGuiEditor::onFileLoaded(std::string path) {


    resourceManager.loadPath(fileManager.getCurrentDir(),
                             std::bind(&ImGuiEditor::onResourceSelected, this, placeholders::_1));

    EditorRootPointer editorRoot = ModelLoader::loadModel(path);
    nodeBuilder.buildNode(editorRoot, canvasNode);


    LOGI("Loaded %s\n", path.c_str());

    for (std::string s:editorRoot->textures) {
        LOGI("Texture found %s\n", s.c_str());
    }
}

void ImGuiEditor::onResourceSelected(std::string resource) {

    cocos2d::Sprite *sprt = cocos2d::Sprite::createWithSpriteFrameName(resource);
    canvasNode->addChild(sprt);


}

void ImGuiEditor::drawCreateView() {

    ImGui::SetNextWindowSize(ImVec2(300, 500), ImGuiSetCond_Once);


    ImGui::SetNextWindowPos(ImVec2(0, 20), ImGuiSetCond_Once);
    ImGui::Begin("Create");


    ImGui::TextColored(ImColor(60, 186, 116), "Nodes");
    ImGui::PushStyleColor(ImGuiCol_Button, ImColor(60, 186, 116));
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImColor(67, 215, 137));
    ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImColor(53, 155, 92));


    if(ImGui::Button("Layout")){
      cocos2d::ui::Layout *layout=  cocos2d::ui::Layout::create();
        layout->setContentSize(cocos2d::Size(100, 100));
        layout->setBackGroundColorType(cocos2d::ui::Layout::BackGroundColorType::SOLID);
        layout->setBackGroundColor(Color3B::WHITE);
        layout->setBackGroundColorOpacity(100);
        canvasNode->addChild(layout);

    }
    if (ImGui::IsItemHovered())
        ImGui::SetTooltip("Creates new button node");
    ImGui::SameLine();

    if(ImGui::Button("Sprite")){
        cocos2d::Sprite *sprite = cocos2d::Sprite::createWithSpriteFrameName("helloworld");
        canvasNode->addChild(sprite);
    }
    if (ImGui::IsItemHovered())
        ImGui::SetTooltip("Creates new sprite node");

    ImGui::SameLine();
    if(ImGui::Button("Label")){
        cocos2d::Label *label = cocos2d::Label::createWithTTF("Hello world","fonts/round.otf",30);
        canvasNode->addChild(label);
    }
    if (ImGui::IsItemHovered())
        ImGui::SetTooltip("Creates new label node");


    ImGui::PopStyleColor(3);


    ImGui::Separator();
    ImGui::TextColored(ImColor(209, 35, 89), "Physics");
    ImGui::PushStyleColor(ImGuiCol_Button, ImColor(209, 35, 89));
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImColor(221, 35, 89));
    ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImColor(199, 34, 81));
    ImGui::Button("Body");
    if (ImGui::IsItemHovered())
        ImGui::SetTooltip("Creates new body");

    ImGui::SameLine();
    ImGui::Button("Fixture");
    if (ImGui::IsItemHovered())
        ImGui::SetTooltip("Creates new fixture");


    ImGui::SameLine();
    ImGui::Button("Joint");
    if (ImGui::IsItemHovered())
        ImGui::SetTooltip("Creates new joint");


    ImGui::PopStyleColor(3);


    ImGui::Separator();
    ImGui::TextColored(ImColor(154, 58, 143), "User interface");
    ImGui::PushStyleColor(ImGuiCol_Button, ImColor(154, 58, 143));
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImColor(168, 60, 157));
    ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImColor(151, 58, 140));
    ImGui::Button("Layout");
    if (ImGui::IsItemHovered())
        ImGui::SetTooltip("Creates new body");

    ImGui::SameLine();
    ImGui::Button("ListView");
    if (ImGui::IsItemHovered())
        ImGui::SetTooltip("Creates new fixture");


    ImGui::SameLine();

    ImGui::Button("ScrollView");
    if (ImGui::IsItemHovered())
        ImGui::SetTooltip("Creates new joint");


    ImGui::PopStyleColor(3);


    ImGui::End();
}

void ImGuiEditor::drawToolbar() {

    ImGuiIO &io = ImGui::GetIO();
    ImVec2 size = io.DisplaySize;
    ImVec2 cursor_pos = io.MousePos;


    ImGui::SetNextWindowPos(ImVec2(300, 20), ImGuiSetCond_Once);

    ImGui::Begin("Toolbar", nullptr, ImGuiWindowFlags_AlwaysAutoResize);

    ImGui::Text("Window size %f %f ", size.x, size.y);
//    ImGui::InputInt("Precisson",)


    std::string settings = cocos2d::UserDefault::getInstance()->getStringForKey("UserSettings");
    char buff[64];
    strcpy(buff, settings.c_str());

    if (ImGui::InputText("User settings ", buff, 64)) {
        cocos2d::UserDefault::getInstance()->setStringForKey("UserSettings", std::string(buff));
    }

    if (ImGui::ImageButton(ImVec2(20, 20), "play", play)) {
        play = true;
    }
    ImGui::SameLine();
    if (ImGui::ImageButton(ImVec2(20, 20), "stop", !play)) {
        play = false;
    }


    ImGui::End();

}

void ImGuiEditor::keyBoardPressed(EventKeyboard::KeyCode keyCode, Event *event) {
    if (keyCode == EventKeyboard::KeyCode::KEY_SPACE) {
        this->dragEnable = true;
    } else if (keyCode == EventKeyboard::KeyCode::KEY_CTRL) {
        this->ctrlPressed = true;
    }

}

void ImGuiEditor::keyBoardReleased(EventKeyboard::KeyCode keyCode, Event *event) {
    if (keyCode == EventKeyboard::KeyCode::KEY_SPACE) {
        this->dragEnable = false;
    } else if (keyCode == EventKeyboard::KeyCode::KEY_CTRL) {
        this->ctrlPressed = false;
    }
}

void ImGuiEditor::drawHiararchyEditor() {
    //Draggable list
//
//
//    // User state
    const int COUNT = 5;
    static const char *items_data[COUNT] = {"Item One", "Item Two", "Item Three", "Item Four", "Item Five"};
    static int items_list[COUNT] = {0, 1, 2, 3, 4};

// Render + dragging
    for (int n = 0; n < COUNT; n++) {
        int item_no = items_list[n];
        ImGui::Selectable(items_data[item_no]);

        if (ImGui::IsItemActive() && !ImGui::IsItemHovered()) {
            float drag_dy = ImGui::GetMouseDragDelta(0).y;
            LOGI("Delta %f \n", drag_dy);
            if (drag_dy < 0.0f && n > 0) {
                items_list[n] = items_list[n - 1];
                items_list[n - 1] = item_no;
                ImGui::ResetMouseDragDelta();
            } else if (drag_dy > 0.0f && n < COUNT - 1) {
                items_list[n] = items_list[n + 1];
                items_list[n + 1] = item_no;
                ImGui::ResetMouseDragDelta();
            }
        }
    }
}

void ImGuiEditor::onEnter() {
    Node::onEnter();

    b2Sprite *sprite = b2Sprite::create();
    sprite->initWithFile("stop.png");
    sprite->setPosition(200, 200);
    addChild(sprite);

}





