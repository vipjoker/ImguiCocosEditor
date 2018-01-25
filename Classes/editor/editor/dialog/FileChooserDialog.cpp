//
//  FileChooserDialog.cpp
//  SpritebuilderIOS
//
//  Created by Oleh on 11/5/17.
//

#include "FileChooserDialog.hpp"
bool FileChooserDialog::init(){
    if(!ui::Layout::init()){
        return false;
    }
    return true;
}
