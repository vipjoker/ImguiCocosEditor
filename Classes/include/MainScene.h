#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "CCIMGUI.h"
#include "RessourceManager.h"
#include "FileManager.h"
#include "ModelLoader.h"
#include "NodeBuilder.h"
#include "EditNodeBuilder.h"
#include "NanoVgNode.h"

#define LOGI(format, ...)      logger.AddLog(format, ##__VA_ARGS__)

USING_NS_CC;
using namespace Editor;

struct Logger {
    ImGuiTextBuffer Buf;
    ImGuiTextFilter Filter;
    ImVector<int> LineOffsets;        // Index to lines offset
    bool ScrollToBottom;

    void Clear() {
        Buf.clear();
        LineOffsets.clear();
    }

    void AddLog(const char *fmt, ...) IM_PRINTFARGS(2) {
        int old_size = Buf.size();
        va_list args;
        va_start(args, fmt);
        Buf.appendv(fmt, args);
        va_end(args);
        for (int new_size = Buf.size(); old_size < new_size; old_size++)
            if (Buf[old_size] == '\n')
                LineOffsets.push_back(old_size);
        ScrollToBottom = true;
    }

    void Draw(const char *title, bool *p_opened = NULL) {
        ImGui::SetNextWindowSize(ImVec2(500, 400), ImGuiSetCond_FirstUseEver);
        ImGui::Begin(title, p_opened);
        if (ImGui::Button("Clear")) Clear();
        ImGui::SameLine();
        bool copy = ImGui::Button("Copy");
        ImGui::SameLine();
        Filter.Draw("Filter", -100.0f);
        ImGui::Separator();
        ImGui::BeginChild("scrolling", ImVec2(0, 0), false, ImGuiWindowFlags_HorizontalScrollbar);
        if (copy) ImGui::LogToClipboard();

        if (Filter.IsActive()) {
            const char *buf_begin = Buf.begin();
            const char *line = buf_begin;
            for (int line_no = 0; line != NULL; line_no++) {
                const char *line_end = (line_no < LineOffsets.Size) ? buf_begin + LineOffsets[line_no] : NULL;
                if (Filter.PassFilter(line, line_end))
                    ImGui::TextUnformatted(line, line_end);
                line = line_end && line_end[1] ? line_end + 1 : NULL;
            }
        } else {
            ImGui::TextUnformatted(Buf.begin());
        }

        if (ScrollToBottom)
            ImGui::SetScrollHere(1.0f);
        ScrollToBottom = false;
        ImGui::EndChild();
        ImGui::End();
    }
};

class ImGuiEditor : public cocos2d::Layer {

    float color[3];
    bool showTest = false;
    bool showLog = false;
    int precission = 0;
    ResourceManager resourceManager;
    FileManager fileManager;
    NodeBuilder nodeBuilder;
    EditNodeBuilder editNodeBuilder;

    EditorRootPointer editorRoot = nullptr;
    LayerColor *canvasNode;
    Node *editorOverlay;
    Node *placeholderOverlay;
    float colorArray [3];
    Vec2 lastTouch;

    bool dragEnable = false;
    bool ctrlPressed = false;
    bool play = false;


public:
    NodeTreeT *editableNodeTree = nullptr;
    Logger logger;

    virtual bool init();

    CREATE_FUNC(ImGuiEditor);

    void setupMenu();

    void drawTreeView();

    void drawCreateView();

    void onFileSaved(std::string path);

    void onFileLoaded(std::string path);

    void onResourceSelected(std::string resource);

    void drawEditableControlls();



    void close();

    void showEditWindow();

    void update(float dt) override;

    void drawToolbar();

    bool onTouchBegin(Touch *touch, Event *unused_event);

    void  onTouchMove(Touch *touch, Event *unused_event);

    void  onToucnEnd(Touch *touch, Event *unused_event);

    void keyBoardPressed(EventKeyboard::KeyCode keyCode, Event *event);

    void keyBoardReleased(EventKeyboard::KeyCode keyCode, Event *event);
};

#endif // __HELLOWORLD_SCENE_H__
