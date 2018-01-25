//
//  OpeglShader.cpp
//  SpritebuilderIOS
//
//  Created by Oleh on 10/29/17.
//

#include "OpeglShader.hpp"

bool OpenGlShader::init(){
    if(!Layer::init()){
        return false;
    }
    auto listener = EventListenerCustom::create(constants::RESIZE_EVENT, CC_CALLBACK_1(OpenGlShader::updateUI, this));
    getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
    
    toolbar = ToolbarNode::create();
    botomBar = ToolbarNode::create();
    propertyNode = PropertyNode::create();
    addChild(propertyNode);
    addChild(toolbar);
    addChild(botomBar);
    setupActionsList();
    setupCanvas();
    updateUI(nullptr);
    return true;
}

void OpenGlShader::setupCanvas(){
    canvas = CanvasNode::create();
    addChild(canvas,4);
    Label *label = Label::create();
    label->setSystemFontSize(20);
    FileUtils *file = FileUtils::getInstance();
    std::string str =StringUtils::format("Writable path %s",file->getWritablePath().c_str());
    
    std::vector<std::string> list = file->listFiles("/");
    for(std::string s: list){
        str += "\n"  + s ;
    }
    
    label->setString(str);
    label->setTextColor(Color4B::GREEN);
    canvas->addCanvasNode(label);
}

void OpenGlShader::setupActionsList(){
    menuList = ui::ListView::create();
    menuList->setContentSize(Size(120,200));
    for(std::string str : FileUtils::getInstance()->listFiles("/")){
        menuList->addChild(ListItem::createWithString(std::string(str)));
       // propertyNode->addChild(ListItem::createWithString(str));
    }
    propertyNode->addChild(ListItem::createWithString("Hello world",ListType::EDITTEXT));
    propertyNode->addChild(ListItem::createWithString("Hello world",ListType::EDITTEXT));
    addChild(menuList,3);
    
}


void OpenGlShader::updateUI(EventCustom* event) {
    Size size;
    if(event){
        Size *p = static_cast<Size*>(event->getUserData());
        size = *p;
        delete(p);
    }else{
         size = Director::getInstance()->getOpenGLView()->getVisibleSize();
    }

    int toolbarH = 50;
    int menuW = 170;
    Rect leftMenu = Rect(0,0,menuW,size.height- toolbarH);
    Rect rightMenu = Rect(Vec2(size.width -menuW,0),Size(menuW,size.height - toolbarH));
    Rect canvasRect = Rect(menuW,toolbarH, size.width - 2*menuW,size.height - 2*toolbarH);
    Rect toolbarRect = Rect(Vec2(0,size.height-toolbarH),Size(size.width,toolbarH));
    Rect botomRect = Rect(Vec2(menuW,0),Size(size.width - 2*menuW,toolbarH));
    
    menuList->setContentSize(leftMenu.size);
    menuList->setPosition(leftMenu.origin);
    canvas->setContentSize(canvasRect.size);
    canvas->setPosition(canvasRect.origin);
    toolbar->setContentSize(toolbarRect.size);
    toolbar->setPosition(toolbarRect.origin);
    botomBar->setPosition(botomRect.origin);
    botomBar->setContentSize(botomRect.size);
    propertyNode->setPosition(rightMenu.origin);
    propertyNode->setContentSize(rightMenu.size);
    
}

Scene *OpenGlShader::createScene(){
    auto scene = Scene::create();
    scene->addChild(OpenGlShader::create());
    return scene;
}
