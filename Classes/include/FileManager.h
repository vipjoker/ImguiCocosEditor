//
// Created by oleh on 24.11.17.
//

#ifndef MYGAME_FILEMANAGER_H
#define MYGAME_FILEMANAGER_H

#include "CCIMGUI.h"
#include "external/tinydir/tinydir.h"

#include <functional>
#include "cocos2d.h"

#include <iostream>
#include <fstream>
#include <ctime>
USING_NS_CC;
typedef tinydir_file TFile;

using namespace std;
class FileManager {

    vector<TFile> files;

    string loadedFile = "";
    string currentDir;

//    char newFile[256];

    function<void(string)> loadFilesCallback;
    function<void(string)> saveFilesCallback;
public:
    const static char* DIR_PARAM;
    const static char* FILE_PARAM;
    void init(string dir,string path);
    inline const std::string getCurrentDir(){return currentDir;}
    void loadFile(function<void(string)> callback);
    void saveFile(function<void(string)> callback);
    void loadFiles(string path);


    void showLoadPopup();
    void showSavePopup();
    bool validateFileName();
    void copyFile(std::string sourcepath,std::string destpath);
    void draw();


    inline bool ends_with(string const & value, string const & ending)
    {
        if (ending.size() > value.size()) return false;
        return equal(ending.rbegin(), ending.rend(), value.rbegin());
    }
};


#endif //MYGAME_FILEMANAGER_H
