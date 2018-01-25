//
// Created by Oleh on 11/18/17.
//

#include "include/ModelLoader.h"

EditorRootPointer ModelLoader::loadModel(string path) {

    Data data = FileUtils::getInstance()->getDataFromFile(path);
    flatbuffers::FlatBufferBuilder builder;
    auto flatEditor = Editor::GetEditorRoot(data.getBytes());
    EditorRootPointer root =flatEditor->UnPack();
    return root;
}

void ModelLoader::saveModel(std::string path, EditorRootPointer editorRootPointer) {

    flatbuffers::FlatBufferBuilder builder;

    flatbuffers::Offset<Editor::EditorRoot> root = Editor::EditorRoot::Pack(builder, editorRootPointer);
    builder.Finish(root);
    cocos2d::Data data;
    data.copy(builder.GetBufferPointer(), builder.GetSize());
    FileUtils::getInstance()->writeDataToFile(data, path);

}
