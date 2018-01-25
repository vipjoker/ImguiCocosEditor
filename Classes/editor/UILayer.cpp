//
//  UILayer.cpp
//  Box2dEditor
//
//  Created by Oleh Mahobey on 8/27/17.
//
//

#include "UILayer.hpp"

void setupButton(ui::Button &btn, Vec2 anchPoint, Vec2 pos){
    btn.setScale(.3);
    btn.setOpacity(200);
    btn.setAnchorPoint(anchPoint);
    btn.setPosition(pos);
}



bool UILayer::init(){
    if(!Layer::init()){
        return false;
    }
    Size size = Director::getInstance()->getVisibleSize();
    
    backBtn = ui::Button::create("arrow_back.png");
    
    setupButton(*backBtn,Point::ANCHOR_TOP_LEFT,Vec2(10,size.height - 10));
    
    backBtn->addClickEventListener([](Ref *ref){
     //   Director::getInstance()->replaceScene(MainScene::createScene());
    });
    
    rightBtn = ui::Button::create("right.png");
    
    setupButton(*rightBtn,Point::ANCHOR_BOTTOM_LEFT, Vec2(20 + 0.3 * rightBtn->getContentSize().width ,10));
    
    leftBtn = ui::Button::create("left.png");
    setupButton(*leftBtn, Point::ANCHOR_BOTTOM_LEFT, Vec2(10,10));
    
    downBtn = ui::Button::create("down.png");
    setupButton(*downBtn, Point::ANCHOR_BOTTOM_RIGHT, Vec2(size.width - 10,10));
    
    
    upBtn = ui::Button::create("up.png");
    setupButton(*upBtn,Point::ANCHOR_BOTTOM_RIGHT,Vec2(size.width -10,20 +( downBtn->getContentSize().height)* 0.3));
    
   
    addChild(leftBtn);
    addChild(rightBtn);
    addChild(upBtn);
    addChild(downBtn);
    addChild(backBtn);
    
    return true;
}
