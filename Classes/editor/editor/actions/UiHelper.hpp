//
//  UiHelper.hpp
//  SpritebuilderIOS
//
//  Created by Oleh on 10/9/17.
//

#ifndef UiHelper_hpp
#define UiHelper_hpp

#include <stdio.h>

#include "cocos2d.h"
#include "ui/CocosGUI.h"
USING_NS_CC;

namespace helper {
    ui::LinearLayoutParameter *getButtonLayoutParam();
    ui::Button *getTextButton(std::string name);
    ui::Button *getSymbolButton(std::string path);
}



#endif /* UiHelper_hpp */
