//
// Created by Deepak Ramalingam on 9/7/22.
//

#ifndef DEEPSENGINE_EDITOR_H
#define DEEPSENGINE_EDITOR_H

#include <imgui.h>
#include <imgui_impl_opengl3.h>
#include <imgui_impl_glfw.h>
#include <imgui_internal.h>

class Editor {
public:
    static Editor& getInstance()
    {
        static Editor instance;
        return instance;
    }
    void init();
    void draw(unsigned int textureColorbuffer);
    void setDefaultEditorFont(ImFont* font);
private:
    Editor() {

    }
    ImFont* defaultFont = nullptr;
public:
    Editor(Editor const&)  = delete;
    void operator=(Editor const&)  = delete;
};


#endif //DEEPSENGINE_EDITOR_H
