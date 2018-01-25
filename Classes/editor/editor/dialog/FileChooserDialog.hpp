//
//  FileChooserDialog.hpp
//  SpritebuilderIOS
//
//  Created by Oleh on 11/5/17.
//

#ifndef FileChooserDialog_hpp
#define FileChooserDialog_hpp
#include "cocos2d.h"
#include "ui/CocosGUI.h"
USING_NS_CC;
class FileChooserDialog:public ui::Layout{
public:
    bool init();
    CREATE_FUNC(FileChooserDialog);
};

#endif /* FileChooserDialog_hpp */
