//
// Created by omak on 07.09.17.
//


#include "b2Utils.hpp"
#include <vector>
#include "EditorScene.h"
bool EditorScene::init() {
    if (!Layer::init()) {
        return false;
    }
    
    CCLOG("CREATED");
    isRunning = false;
    world = new b2World(b2Vec2(0,-10));
    auto layer = b2DebugLayer::create(world, 30);
    Size size = Director::getInstance()->getVisibleSize();
    BaseModel b(CIRCLE,size/2);
    
    
    
    layer->setContentSize({500,500});
    addChild(layer,5);
    
    baseActions.pushBack(EditAction::create(this,&rects));
    baseActions.pushBack(CreateAction::create(this,&rects));
    
    
    
    currentRect = nullptr;
    
    listView = ui::ListView::create();
    
    
    
    listView->setLayoutType(ui::Layout::Type::HORIZONTAL);
    
    listView->setContentSize({100, size.height});
    
    //listView->setPropagateTouchEvents(true);
    listView->setSwallowTouches(true);
    listView->setDirection(ui::ListView::Direction::VERTICAL);
    canvasRect.setRect(100, 0, 750, 600);
    
    clippingNode = ClippingRectangleNode::create(canvasRect);
    
    
    drawNode = DrawNode::create();
    auto layerColor = LayerColor::create(Color4B(21,48,103,255));
    clippingNode->addChild(drawNode,2);
    clippingNode->addChild(layerColor,1);
    addChild(clippingNode);
    
    
    dAction = DrawAction::SELECT;
    
    
    for (auto action:baseActions) {
        
        auto layerColor = ui::Layout::create();
        layerColor->setTouchEnabled(true);
        layerColor->setContentSize({100, 40});
        layerColor->setBackGroundImageScale9Enabled(true);
        layerColor->setBackGroundImage("list_back.png");
        
        
        auto text = ui::Text::create(action->getName(), "fonts/Monaco_Linux.ttf", 15);
        text->setTextColor(Color4B::BLACK);
        layerColor->addChild(text);
        text->setAnchorPoint(Point::ANCHOR_MIDDLE);
        text->setPosition({50, 20});
        
        listView->pushBackCustomItem(layerColor);
    }
    toolbar = getToolbar();
    /// LISTVIEW
    listView->addEventListener([this](Ref *ref ,ui::ListView::EventType event){
        ui::ListView *listView = dynamic_cast<ui::ListView*>(ref);
        int index= listView->getCurSelectedIndex();
        setupAction(index);
        
    });
    
    
    addChild(listView);
    
    
    auto layout = ui::VBox::create();
    layout->setBackGroundColorType(ui::Layout::BackGroundColorType::SOLID);
    layout->setBackGroundColor(Color3B::BLACK);
    layout->setContentSize({150,size.height});
    
    layout->setAnchorPoint(Point::ANCHOR_BOTTOM_RIGHT);
    layout->setPosition({size.width,0});
    
    
    text = ui::Text::create("Text","fonts/arial.ttf", 150);
    tvAction = ui::Text::create("Action","fonts/arial.ttf",10);
   
    
//    auto lbl = Label::createWithTTF("HELLO", "fonts/arial.ttf",10);
//    lbl->getFontAtlas()->setAliasTexParameters();
//    lbl->setPosition(size/2);
//
//    addChild(lbl,5);
    
    
    layout->addChild(text);
    layout->addChild(tvAction);
    
    addChild(layout);
    
    addChild(toolbar);
    
    setupAction(0);
    
    auto mouseListener = EventListenerMouse::create();
    
    
    
    mouseListener->onMouseDown = [this](EventMouse *event){
        CCLOG("EDITOR DOWN");
       // event->stopPropagation();
        Size size = Director::getInstance()->getOpenGLView()->getFrameSize();
        
        
        auto location = event->getLocation();
        // get the location of the touch relative to your button
        auto nodeSpaceLocation = clippingNode->getParent()->convertToNodeSpace(location);
        // check if touch is inside node's bounding box
        
        if(Rect(100,0,750,600).containsPoint(nodeSpaceLocation)){
            baseAction->onTouchBegin(event);
            redraw();
            return false;
        }
        
        
        return false;
    };
    
    mouseListener->onMouseMove = [this](EventMouse *mouse){
       /// CCLOG("EDITOR MOVE");
        pointer = mouse->getLocation();
        baseAction->onTouchMove(mouse);
        
    };
    
    mouseListener->onMouseUp = [this](EventMouse *mouse){
        baseAction->onTouchEnd(mouse);
        
    };
    
    
    
    
    
    
    
    ///listener
    
    auto listener = EventListenerCustom::create("game_custom_event1", [=](EventCustom* event){
        std::string *buf = static_cast<std::string*>(event->getUserData());
        CCLOG((*buf).c_str());
    });
    
    //  getEventDispatcher()->addEventListenerWithFixedPriority(listener, 1);
    
    
    
    
    
    
    
    
    
    
    
    
    clippingNode->getEventDispatcher()->addEventListenerWithSceneGraphPriority(mouseListener,clippingNode);
    //  scheduleUpdate();
    return true;
}

Scene *EditorScene::createScene() {
    Scene *scene = Scene::createWithPhysics();
    scene->addChild(EditorScene::create());
    return scene;
}

ui::Layout *EditorScene::getToolbar(){
    Size size = Director::getInstance()->getVisibleSize();
    auto toolbar = ui::HBox::create();
    toolbar->setContentSize({size.width - 150 -100,30});
    toolbar->setAnchorPoint(Point::ANCHOR_TOP_LEFT);
    toolbar->setPosition({100,size.height});
    toolbar->setBackGroundColor(Color3B(255,255,200));
    toolbar->setBackGroundColorType(ui::Layout::BackGroundColorType::SOLID);
    return toolbar;
}

void EditorScene::setupAction(int actionPosition){
    auto layout = dynamic_cast<ui::Layout*>(listView->getItem(actionPosition));
    
    switch (actionPosition) {
        case 0:
            dAction = DrawAction::CREATE;
            baseAction = baseActions.at(0);
            
            tvAction->setString("Create");
            break;
        case 1:
            dAction = DrawAction::SELECT;
            baseAction = baseActions.at(1);
            tvAction->setString("Select");
            break;
    }
    
    toolbar->removeAllChildren();
    baseAction->setupToolbar(*toolbar);
    for (auto& item :listView->getItems()){
        if(item == layout)
            layout->setBackGroundImageColor(Color3B::RED);
        else{
            auto l = dynamic_cast<ui::Layout*>(item);
            l->setBackGroundImageColor(Color3B::WHITE);
        }
    }
    CCLOG("Item pressed %d",index);
}

void EditorScene::play(bool isStart){
    isRunning = !isRunning;
    if(isRunning){
        createBox2dObjects();
        this->scheduleUpdate();
    }else{
        clearBox2dObjects();
        this->unscheduleUpdate();
        redraw();
    }
    
}

void EditorScene::redraw(){
    auto color = Color4F(1,1,1,.2);
    drawNode->clear();
    Vec2 top(0,canvasRect.getMaxY());
    Vec2 bottom(0,canvasRect.getMinY());
    for(int i = 25;i < canvasRect.getMaxX();i+=25){
        top+= {25,0};
        bottom+={25,0};
        drawNode->drawLine(top,bottom,color);
    }
    Vec2 left(canvasRect.getMinX(),0);
    Vec2 right(canvasRect.getMaxX(),0);
    for(int i = 25; i < canvasRect.getMaxY();i+=25){
        left+={0,25};
        right+={0,25};
        drawNode->drawLine(left,right,color);
    }
    drawNode->drawDot(pointer, 5, Color4F(1,0,0,1));
    pointer = math::getSnappedPoint(pointer,50);
    drawNode->drawDot(pointer, 5, Color4F(1,0,0,.4));
    
  //  drawNode->drawSolidRect(<#const cocos2d::Vec2 &origin#>, <#const cocos2d::Vec2 &destination#>, Color4F::RED);
    //    drawNode->clear();
    //    Size size = Director::getInstance()->getOpenGLView()->getFrameSize();
    //    drawNode->drawLine(Vec2(0,size.height/2), Vec2(size.width,size.height/2), Color4F::RED);
    // clearGizmos();
    //    for(int i = 0 ; i < rects.size();i++){
    //        auto gizmo = Gizmo::create(rects[i]);
    //        gizmos.pushBack(gizmo);
    //        addChild(gizmo,2);
    ////        BaseModel *rect = rects[i];
    //        switch (rect->type) {
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
    //    }
}

void EditorScene::createBox2dObjects(){
    
    for(int i = 0 ; i < rects.size();i++){
        
        BaseModel *rect = rects[i];
        switch (rect->type) {
            case CIRCLE:{
                Vec2 first = rect->points[0] /30;
                Vec2 second = rect->points[1] /30;
                helper::createCircle(*world, first.distance(second),rect->pos/30);
                // drawNode->drawSolidCircle(rect->points[0],rect->points[0].distance(rect->points[1]),30,32,1,1,Color4F::RED);
            }
                break;
            case SQUARE:
                //helper::create(*world, *rect->points.data(),rect->points.size()) ;
                
                
                helper::createSquare(*world, rect->pos, rect->points.data(), rect->points.size());
                // drawNode->drawSolidPoly(rect->points.data(), rect->points.size(), Color4F::YELLOW);
                break;
            case LINE:
                
                //drawNode->drawPoly(rect->points.data(), rect->points.size(), false, Color4F::MAGENTA);
                break;
        }
    }
}


void EditorScene::clearBox2dObjects(){
    b2Body *b  = world->GetBodyList();
    while (b){
        b2Body *temp = b->GetNext();
        world->DestroyBody(b);
        b = temp;
    }
}

void EditorScene::clearGizmos(){
    
    int count = 0;
    for(Node *n : gizmos){
        
        n->removeFromParent();
        
    }
}

void EditorScene::update(float dt) {
    drawNode->clear();
    
    world->Step(dt, 6, 3);
    
    
    
    
    //        if(rect == currentRect){
    //
    //            drawNode->drawSolidRect(rect->rect.origin,rect->rect.origin + rect->rect.size,Color4F::YELLOW);
    //            drawNode->drawSolidCircle(rect->rect.origin, 5, 20, 32, 1, 1, Color4F::MAGENTA);
    //            drawNode->drawSolidCircle(rect->rect.origin + rect->rect.size, 5, 20, 32, 1, 1, Color4F::MAGENTA);
    //            drawNode->drawSolidCircle(rect->rect.origin + Vec2(0,rect->rect.size.height), 5, 20, 32, 1, 1, Color4F::MAGENTA);
    //            drawNode->drawSolidCircle(rect->rect.origin + Vec2(rect->rect.size.width,0), 5, 20, 32, 1, 1, Color4F::MAGENTA);
    //
    //        }else{
    //           drawNode->drawSolidRect(rect->rect.origin,rect->rect.origin + rect->rect.size,Color4F::RED);
    //
    //        }
    
    
    
    //        }
    
    
    
    
}

