//
//  OpeglShader.hpp
//  SpritebuilderIOS
//
//  Created by Oleh on 10/29/17.
//

#ifndef OpeglShader_hpp
#define OpeglShader_hpp
#include "Res.h"
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "ListItem.hpp"
#include "CanvasNode.hpp"
#include "ToolbarNode.hpp"
#include "PropertyNode.hpp"

USING_NS_CC;
class OpenGlShader:public Layer{
    
    ui::ListView *menuList;
    ui::Text *text;
    CanvasNode *canvas;
    ToolbarNode *toolbar;
    ToolbarNode *botomBar;
    PropertyNode *propertyNode;
public:
    bool init() override;
    CREATE_FUNC(OpenGlShader);
    static Scene *createScene();
    void setupActionsList();
    void setupCanvas();
    void updateUI(EventCustom *event);
};

#endif /* OpeglShader_hpp */
