//
// Created by oleh on 24.11.17.
//

#include "include/RessourceManager.h"

void ResourceManager::draw()
{
    if (showResourcesWindow)
    {
        ImGui::Begin("Resources", &showResourcesWindow,ImGuiWindowFlags_AlwaysAutoResize);
        map<string, string>::iterator it;
        int counter = 0;
        for (it = imagesMap.begin(); it != imagesMap.end(); it++, counter++)
        {

            ImGui::PushID(counter);
            if (ImGui::ImageButton(vecSize, it->first.c_str()))
            {
                callback(it->first);
            }
            if ((counter % 4) < 3) ImGui::SameLine();
            ImGui::PopID();
        }
        ImGui::End();
    }
}

void ResourceManager::loadPath(string path,function<void(string)>callback)
{
    this->callback = callback;
    vector<string> files = FileUtils::getInstance()->listFiles(path);
    for (string s : files)
    {
        if (ends_with(s, ".png"))
        {
            string fileName = s.substr(s.rfind("/") + 1);

            imagesMap.insert(pair<string, string>(fileName, s));
        }
    }

    map<string, string>::iterator it;
    for (it = imagesMap.begin(); it != imagesMap.end(); it++)
    {
        addTextureCache(it->second,it->first);
        cout << it->first << " : "<< it->second<< endl;
    }
}

void ResourceManager::addTextureCache(std::string path,std::string name) {
    Texture2D *texture2d = Director::getInstance()->getTextureCache()->addImage(path);
    SpriteFrame *frame = SpriteFrame::createWithTexture(texture2d, cocos2d::Rect(Vec2::ZERO, texture2d->getContentSize()));
    SpriteFrameCache::getInstance()->addSpriteFrame(frame, name);

}



