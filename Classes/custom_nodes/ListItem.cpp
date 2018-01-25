//
//  ListItem.cpp
//  SpritebuilderIOS
//
//  Created by Oleh on 11/4/17.
//

#include "ListItem.hpp"
ListItem::ListItem(std::string name,ListType _type){
    setItemName(name);
    type = _type;
}

ListItem *ListItem::createWithString(std::string name ,ListType type){
    ListItem *item = new(std::nothrow) ListItem(name,type);
    if(item){
        item->init();
        item->autorelease();
    }else{
        CC_SAFE_DELETE(item);
        item = nullptr;
    }
    return item;
}

bool ListItem::init(){
    CCLOG("ITEM created %s" , getItemName().c_str());
    
    Size size = Size(200,70);
    setContentSize(size);
    switch (type) {
        case ListType::TEXT:
           return initTextView();
            
        case ListType::EDITTEXT:
            return initEditText();
        case ListType::MENUITEM:
            return initMenuItem();
    }
    
//    setBackGroundColorType(cocos2d::ui::Layout::BackGroundColorType::GRADIENT);
//    setBackGroundColorVector(Vec2(0,1));
//    setBackGroundColor(Color3B(30,30,30), Color3B::WHITE);
//    setBackGroundColorOpacity(130);
   
    
    
    return true;
}


bool ListItem::initEditText(){
    setBackGroundImage(res::back_button);
    setBackGroundImageScale9Enabled(true);
    ui::EditBox *editBox = ui::EditBox::create(Size(100,40), res::btn_grey);
    editBox->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
    editBox->setFontSize(18);
    editBox->setInputMode(cocos2d::ui::EditBox::InputMode::SINGLE_LINE);
    editBox->setFontColor(Color3B::BLACK);
    
    
    editBox->setMaxLength(6);

    editBox->setTextHorizontalAlignment(cocos2d::TextHAlignment::CENTER);
    editBox->setPosition(Vec2(10,35));
    
    auto btn  = ui::Button::create(res::btn_grey);
    btn->setColor(Color3B::GRAY);
    btn->setAnchorPoint(Vec2::ANCHOR_MIDDLE_RIGHT);
    btn->setPosition(Vec2(190,35));
    addChild(btn);
    addChild(editBox);
    return true;
}
bool ListItem::initTextView(){
    setBackGroundImage(res::back_button);
    setBackGroundImageScale9Enabled(true);
    ui::Text *text = ui::Text::create();
    text->setString(getItemName());
    text->setTextColor(Color4B::BLACK);
    text->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
    text->setPosition(Vec2(20,50));
    addChild(text);

    return true;
}

bool ListItem::initMenuItem(){
    
    setBackGroundImage(res::back_button);
    setBackGroundImageScale9Enabled(true);
    ui::Text *text = ui::Text::create();
    text->setString(getItemName());
    text->setTextColor(Color4B::BLACK);
    text->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
    text->setPosition(Vec2(20,50));
    
    ui::ImageView *imageView = ui::ImageView::create(res::doc_node);
    
    imageView->setAnchorPoint(Point::ANCHOR_MIDDLE_RIGHT);
    imageView->setContentSize(Size(50,50));
    imageView->setScale9Enabled(true);
    imageView->setPosition(Vec2(100,50));
    addChild(imageView);
    addChild(text);
    
    return true;
}

ListItem::~ListItem(){
    
}
