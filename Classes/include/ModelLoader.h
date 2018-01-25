//
// Created by Oleh on 11/18/17.
//

#ifndef MYGAME_MODELLOADER_H
#define MYGAME_MODELLOADER_H

#include "cocos2d.h"
#include "EditorRoot_generated.h"
#include "iostream"
USING_NS_CC;
using namespace std;
//typedef  std::unique_ptr<Editor::EditorRootT> EditorRootPointer;
typedef  Editor::EditorRootT* EditorRootPointer;
class ModelLoader {
public:
    static EditorRootPointer loadModel(string path);
    static void saveModel(string path ,EditorRootPointer editorRootPointer);
};


#endif //MYGAME_MODELLOADER_H
