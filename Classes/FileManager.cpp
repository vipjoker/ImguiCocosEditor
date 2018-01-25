//
// Created by oleh on 24.11.17.
//

#include "include/FileManager.h"

const char *FileManager::DIR_PARAM = "lastFileDirectory";;
const char *FileManager::FILE_PARAM = "lastFilePath";


void FileManager::init(string dir, string path) {
    this->currentDir = dir;
    this->loadedFile = path;
    loadFiles(dir);
}

void FileManager::draw() {
    showLoadPopup();
    showSavePopup();
}

void FileManager::showLoadPopup() {
    if (ImGui::BeginPopupModal("Load file", NULL)) {
        ImGui::BeginChild("##header",
                          ImVec2(0, ImGui::GetTextLineHeightWithSpacing() + ImGui::GetStyle().ItemSpacing.y));
        ImGui::Columns(2);
        ImGui::Text("Name");
        ImGui::NextColumn();
        ImGui::Text("Path");
        ImGui::NextColumn();
        ImGui::Columns(1);
        ImGui::Separator();
        ImGui::EndChild();
        ImGui::BeginChild("##scrollingregion", ImVec2(500, 300));
        ImGui::Columns(2);

        for (int i = 0; i < files.size(); i++) {
            TFile &f = files[i];
            if (f.name[0] == '.')continue;
            if (ImGui::Selectable(f.name, false, ImGuiSelectableFlags_DontClosePopups)) {
                if (f.is_dir)loadFiles(f.path);
                else loadedFile = f.name;

            }
            ImGui::NextColumn();
            ImGui::Text(f.path);
            ImGui::NextColumn();
        }
        ImGui::Columns(1);
        ImGui::EndChild();;
        ImGui::Separator();
        ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(0, 0));
        ImGui::TextColored(ImVec4(1, 1, 0, 1), currentDir.c_str());

        ImGui::Text(loadedFile.empty() ? "No file selected" : loadedFile.c_str());
        ImGui::PopStyleVar();
        if (ImGui::Button("Load", ImVec2(120, 0))) {
            if (!loadedFile.empty()) {

                auto preferences = cocos2d::UserDefault::getInstance();
                preferences->setStringForKey(DIR_PARAM, currentDir);
                preferences->setStringForKey(FILE_PARAM, loadedFile);

                if (loadFilesCallback)loadFilesCallback(std::string(currentDir + "/" + loadedFile).c_str());
                ImGui::CloseCurrentPopup();
            } else {
                ImGui::TextColored(ImVec4(1, 0, 0, 1), "Failed to load file");
            }
        }
        ImGui::SameLine();
        if (ImGui::Button("Cancel", ImVec2(120, 0))) { ImGui::CloseCurrentPopup(); }
        ImGui::EndPopup();
    }
}

void FileManager::showSavePopup() {
    if (ImGui::BeginPopupModal("Save file", NULL)) {
        ImGui::BeginChild("##header",
                          ImVec2(0, ImGui::GetTextLineHeightWithSpacing() + ImGui::GetStyle().ItemSpacing.y));
        ImGui::Columns(2);
        ImGui::Text("Name");
        ImGui::NextColumn();
        ImGui::Text("Path");
        ImGui::NextColumn();
        ImGui::Columns(1);
        ImGui::Separator();
        ImGui::EndChild();
        ImGui::BeginChild("##scrollingregion", ImVec2(500, 300));
        ImGui::Columns(2);
        for (int i = 0; i < files.size(); i++) {

            TFile &f = files[i];
            if (f.name[0] == '.' || !f.is_dir)continue;

            if (ImGui::Selectable(f.name, false, ImGuiSelectableFlags_DontClosePopups)) {
                loadFiles(f.path);
                // currentDir = f.path;
            }

            ImGui::NextColumn();
            ImGui::Text(f.path);
            ImGui::NextColumn();
        }
        ImGui::Columns(1);
        ImGui::EndChild();;
        ImGui::Separator();
        ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(0, 0));
        ImGui::TextColored(ImVec4(1, 1, 0, 1), currentDir.c_str());
        ImGui::Separator();
        const char *loadedChars = loadedFile.c_str();
        char buff[256];
        strcpy(buff, loadedChars);
        ImGui::InputText("New file name", buff, 256);
        if (!currentDir.empty()) ImGui::Text("File dir %s  %s", currentDir.c_str(), buff);

        bool isValid = validateFileName();
        loadedFile = buff;

        if (!isValid)ImGui::TextColored(ImVec4(1, 0, 0, 1), "Wrong file name");
        else ImGui::TextColored(ImVec4(0, 1, 0, 1), "Correct name");
        ImGui::PopStyleVar();
        if (ImGui::Button("Save", ImVec2(120, 0))) {
            std::string path = currentDir + "/" + loadedFile;
            if (saveFilesCallback)saveFilesCallback(path);
            //   FileUtils::getInstance()->writeStringToFile("Message from editor", path);
            ImGui::CloseCurrentPopup();
        }
        ImGui::SameLine();
        if (ImGui::Button("Cancel", ImVec2(120, 0))) { ImGui::CloseCurrentPopup(); }
        ImGui::EndPopup();
    }
}

void FileManager::loadFiles(std::string path) {
    //this->files = FileUtils::getInstance()->listFiles(path);
    currentDir = path;
    CCLOG("OPEN path %s", path.c_str());
    this->files.clear();
    tinydir_dir dir;
    tinydir_open(&dir, path.c_str());
    if (path != "/") {
        TFile back;
        unsigned long index = path.rfind("/");
        std::string parent = path.substr(0, index);
        strcpy(back.path, parent.c_str());
        strcpy(back.name, "<-");
        files.push_back(back);
    }
    while (dir.has_next) {
        TFile f;
        tinydir_readfile(&dir, &f);
        files.push_back(f);
        tinydir_next(&dir);
    }
}

bool FileManager::validateFileName() {
    if (loadedFile.size() < 6)return false;
    return ends_with(loadedFile, ".fbb");
}

void FileManager::loadFile(std::function<void(std::string)> callback) {
    this->loadFilesCallback = callback;
    ImGui::OpenPopup("Load file");
}

void FileManager::saveFile(std::function<void(std::string)> callback) {
    this->saveFilesCallback = callback;
    ImGui::OpenPopup("Save file");
}

void FileManager::copyFile(std::string sourcepath, std::string destpath) {

    using namespace std;


    clock_t start, end;
    start = clock();

    ifstream source("from.ogv", ios::binary);
    ofstream dest("to.ogv", ios::binary);

    dest << source.rdbuf();

    source.close();
    dest.close();

    end = clock();

    cout << "CLOCKS_PER_SEC " << CLOCKS_PER_SEC << "\n";
    cout << "CPU-TIME START " << start << "\n";
    cout << "CPU-TIME END " << end << "\n";
    cout << "CPU-TIME END - START " << (long) end - (long) start << "\n";
    cout << "TIME(SEC) " << static_cast<long>(end - start) / CLOCKS_PER_SEC << "\n";

}

