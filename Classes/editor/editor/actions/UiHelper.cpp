//
//  UiHelper.cpp
//  SpritebuilderIOS
//
//  Created by Oleh on 10/9/17.
//

#include "UiHelper.hpp"


ui::LinearLayoutParameter *helper::getButtonLayoutParam(){
    auto layoutPar = ui::LinearLayoutParameter::create();
    layoutPar->setGravity(cocos2d::ui::LinearLayoutParameter::LinearGravity::CENTER_VERTICAL);
    layoutPar->setMargin(ui::Margin(5,0,5,0));
    return layoutPar;
}

ui::Button *helper::getTextButton(std::string name){
    auto btn = ui::Button::create("button.png");
    btn->setLayoutParameter(getButtonLayoutParam());
    
    auto lbl = Label::createWithTTF(name, "fonts/arial.ttf", 12);
    lbl->setAlignment(cocos2d::TextHAlignment::CENTER);
    lbl->setVerticalAlignment(cocos2d::TextVAlignment::CENTER);
    btn->setZoomScale(1.1);
    btn->setTitleLabel(lbl);
    btn->setScale9Enabled(true);
    btn->setContentSize({70,20});
    btn->setAnchorPoint(Point::ANCHOR_MIDDLE);
    return btn;
}

ui::Button *helper::getSymbolButton(std::string path){
    auto button = ui::Button::create(path);
    button->setLayoutParameter(getButtonLayoutParam());
    return button;
}
