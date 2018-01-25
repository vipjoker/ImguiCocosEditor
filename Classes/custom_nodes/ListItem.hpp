//
//  ListItem.hpp
//  SpritebuilderIOS
//
//  Created by Oleh on 11/4/17.
//

#ifndef ListItem_hpp
#define ListItem_hpp
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "Res.h"
USING_NS_CC;
enum class ListType {
    TEXT,EDITTEXT,MENUITEM
};
class ListItem :public ui::Layout {
    ListType type;
    CC_SYNTHESIZE(std::string, itemName, ItemName);
    public :
    static ListItem *createWithString(std::string name ,ListType ltype = ListType::TEXT);
    bool init();
    bool initMenuItem();
    bool initEditText();
    bool initTextView();
    ListItem(std::string name,ListType type);
    ~ListItem();
};
#endif /* ListItem_hpp */
