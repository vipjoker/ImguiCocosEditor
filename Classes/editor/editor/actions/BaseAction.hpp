//
//  BaseAction.hpp
//  SpritebuilderIOS
//
//  Created by Oleh on 10/9/17.
//

#ifndef BaseAction_hpp
#define BaseAction_hpp

#include "cocos2d.h"
#include "ui/CocosGUI.h"

USING_NS_CC;
class BaseAction :public Ref{
public:
    virtual void setupToolbar(ui::Layout &layout) = 0;
    virtual bool onTouchBegin(EventMouse *event) = 0;
    virtual void onTouchMove(EventMouse *event) = 0;
    virtual void onTouchEnd(EventMouse *event) = 0;
    virtual std::string getName() = 0;
};

#endif /* BaseAction_hpp */
