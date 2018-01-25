//
//  UILayer.hpp
//  Box2dEditor
//
//  Created by Oleh Mahobey on 8/27/17.
//
//

#ifndef UILayer_hpp
#define UILayer_hpp

#include "cocos2d.h"
#include "ui/CocosGUI.h"
//#include "MainScene.h"
USING_NS_CC;
class UILayer:public Layer{
    CC_SYNTHESIZE(ui::Button*, backBtn, BackBtn);
    CC_SYNTHESIZE(ui::Button*, leftBtn,LeftBtn)
    CC_SYNTHESIZE(ui::Button*, rightBtn, RightBtn);
    CC_SYNTHESIZE(ui::Button*, upBtn, UpBtn);
    CC_SYNTHESIZE(ui::Button*, downBtn, DownBtn);
public:
    CREATE_FUNC(UILayer);
    bool init() override;
};

#endif /* UILayer_hpp */
