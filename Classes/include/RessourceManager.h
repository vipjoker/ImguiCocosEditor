//
// Created by oleh on 24.11.17.
//

#ifndef MYGAME_RESSOURCEMANAGER_H
#define MYGAME_RESSOURCEMANAGER_H

#include <string>
#include "cocos2d.h"
#include "CCIMGUI.h"
#include <iostream>
#include <map>
USING_NS_CC;
using namespace std;
class ResourceManager {

    bool showResourcesWindow = true;

    ImVec2 vecSize = {50,50};

    map<string,string> imagesMap;

    function<void(string)>callback;

    public:

    void setShowWindow(bool showWindow){

        this->showResourcesWindow = showWindow;
    }

    void draw();

    void loadPath(string path,function<void(string)>callback);

    void addTextureCache(std::string path,std::string name);

    inline bool ends_with(string const & value, string const & ending)
    {
        if (ending.size() > value.size()) return false;
        return equal(ending.rbegin(), ending.rend(), value.rbegin());
    }
};


#endif //MYGAME_RESSOURCEMANAGER_H
