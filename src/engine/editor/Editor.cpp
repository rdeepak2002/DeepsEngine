//
// Created by Deepak Ramalingam on 9/7/22.
//

#include "Editor.h"
#include "Application.h"

void Editor::init() {
    ImGui::StyleColorsDark();
}

void Editor::draw(unsigned int textureColorbuffer) {
    ImGui::NewFrame();

    ///

    auto& colors = ImGui::GetStyle().Colors;
    colors[ImGuiCol_WindowBg] = ImVec4{ 0.1f, 0.105f, 0.11f, 1.0f };

    // Headers
    colors[ImGuiCol_Header] = ImVec4{ 0.2f, 0.205f, 0.21f, 1.0f };
    colors[ImGuiCol_HeaderHovered] = ImVec4{ 0.3f, 0.305f, 0.31f, 1.0f };
    colors[ImGuiCol_HeaderActive] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };

    // Buttons
    colors[ImGuiCol_Button] = ImVec4{ 0.2f, 0.205f, 0.21f, 1.0f };
    colors[ImGuiCol_ButtonHovered] = ImVec4{ 0.3f, 0.305f, 0.31f, 1.0f };
    colors[ImGuiCol_ButtonActive] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };

    // Frame BG
    colors[ImGuiCol_FrameBg] = ImVec4{ 0.2f, 0.205f, 0.21f, 1.0f };
    colors[ImGuiCol_FrameBgHovered] = ImVec4{ 0.3f, 0.305f, 0.31f, 1.0f };
    colors[ImGuiCol_FrameBgActive] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };

    // Tabs
    colors[ImGuiCol_Tab] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };
    colors[ImGuiCol_TabHovered] = ImVec4{ 0.38f, 0.3805f, 0.381f, 1.0f };
    colors[ImGuiCol_TabActive] = ImVec4{ 0.28f, 0.2805f, 0.281f, 1.0f };
    colors[ImGuiCol_TabUnfocused] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };
    colors[ImGuiCol_TabUnfocusedActive] = ImVec4{ 0.2f, 0.205f, 0.21f, 1.0f };

    // Title
    colors[ImGuiCol_TitleBg] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };
    colors[ImGuiCol_TitleBgActive] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };
    colors[ImGuiCol_TitleBgCollapsed] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };

    ///

    if (defaultFont) {
        ImGui::PushFont(defaultFont);
    }

    ImGuiDockNodeFlags dockspaceFlags = ImGuiDockNodeFlags_None;
    ImGuiID dockspaceID = ImGui::GetID("DeepsEngine");

    if (!ImGui::DockBuilderGetNode(dockspaceID)) {
        ImGui::DockBuilderRemoveNode(dockspaceID);
        ImGui::DockBuilderAddNode(dockspaceID, ImGuiDockNodeFlags_None);
//        ImGui::DockBuilderSetNodePos(dockspaceID, ImVec2(0.0f, 0.0f));
//        ImGui::DockBuilderSetNodeSize(dockspaceID, ImGui::GetIO().DisplaySize);

        ImGuiID dock_main_id = dockspaceID;
        ImGuiID dock_left_id = ImGui::DockBuilderSplitNode(dock_main_id, ImGuiDir_Left, 0.2f, nullptr, &dock_main_id);
        ImGuiID dock_right_id = ImGui::DockBuilderSplitNode(dock_main_id, ImGuiDir_Right, 0.2f, nullptr, &dock_main_id);
        ImGuiID dock_up_id = ImGui::DockBuilderSplitNode(dock_main_id, ImGuiDir_Up, 0.05f, nullptr, &dock_main_id);
        ImGuiID dock_down_id = ImGui::DockBuilderSplitNode(dock_main_id, ImGuiDir_Down, 0.2f, nullptr, &dock_main_id);

        ImGui::DockBuilderDockWindow("Renderer", dock_main_id);
        ImGui::DockBuilderDockWindow("Scene", dock_left_id);
        ImGui::DockBuilderDockWindow("Inspector", dock_right_id);
        ImGui::DockBuilderDockWindow("Actions", dock_up_id);
        ImGui::DockBuilderDockWindow("Console", dock_down_id);

        // Disable tab bar for custom toolbar
        ImGuiDockNode* node = ImGui::DockBuilderGetNode(dock_up_id);
        node->LocalFlags |= ImGuiDockNodeFlags_NoTabBar;

        ImGui::DockBuilderFinish(dock_main_id);
    }

    ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
    ImGuiWindowFlags host_window_flags = 0;
    host_window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoDocking;
    host_window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
    ImGui::SetNextWindowPos(ImVec2(0.0f, 0.0f));
    ImGui::SetNextWindowSize(ImGui::GetIO().DisplaySize);
    ImGui::Begin("DeepsEngine", nullptr, host_window_flags);
    ImGui::PopStyleVar(3);
    ImGui::DockSpace(dockspaceID, ImGui::GetIO().DisplaySize, dockspaceFlags);
    ImGui::End();

    ImGuiWindowFlags scene_window_flags = 0;
    scene_window_flags |= ImGuiWindowFlags_NoCollapse;
    if(ImGui::Begin("Scene", nullptr, scene_window_flags)) {
        if(ImGui::BeginChild("Test")) {
            ImGui::Text("txt");
            ImGui::EndChild();
        }
        ImGui::End();
    }

    ImGuiWindowFlags actions_window_flags = 0;
    actions_window_flags |= ImGuiWindowFlags_NoCollapse;
    if(ImGui::Begin("Actions", nullptr, actions_window_flags)) {
        if (Application::getInstance().playing) {
            if (ImGui::Button("Stop")) { // Buttons return true when clicked (most widgets return true when edited/activated)
                Application::getInstance().setCursorMode(DeepsEngine::Cursor::CURSOR_NORMAL);
                Application::getInstance().playing = false;
            }
        } else {
            if (ImGui::Button("Play")) { // Buttons return true when clicked (most widgets return true when edited/activated)
                Application::getInstance().setCursorMode(DeepsEngine::Cursor::CURSOR_DISABLED);
                Application::getInstance().playing = true;
            }
        }
        ImGui::End();
    }

    ImGuiWindowFlags renderer_window_flags = 0;
    renderer_window_flags |= ImGuiWindowFlags_NoScrollbar;
    if(ImGui::Begin("Renderer", nullptr, renderer_window_flags))
    {
        ImVec2 vMin = ImGui::GetWindowContentRegionMin();
        ImVec2 vMax = ImGui::GetWindowContentRegionMax();

        vMin.x += ImGui::GetWindowPos().x;
        vMin.y += ImGui::GetWindowPos().y;
        vMax.x += ImGui::GetWindowPos().x;
        vMax.y += ImGui::GetWindowPos().y;

        float width = vMax.x - vMin.x;
        float height = vMax.y - vMin.y;
        Application::getInstance().resizeWindow(width, height);
        ImGui::Image(reinterpret_cast<ImTextureID>(textureColorbuffer), ImVec2(width, height), ImVec2(0, 1), ImVec2(1, 0));
        ImGui::End();
    }

    if(ImGui::Begin("Inspector")) {
        if(ImGui::BeginChild("Test")) {
            ImGui::Text("txt");
            ImGui::EndChild();
        }
        ImGui::End();
    }

    if(ImGui::Begin("Console")) {
        if(ImGui::BeginChild("Test")) {
            ImGui::Text("txt");
            ImGui::EndChild();
        }
        ImGui::End();
    }

    if (defaultFont) {
        ImGui::PopFont();
    }

    // Render dear imgui into screen
    ImGui::Render();
}

void Editor::setDefaultEditorFont(ImFont* font) {
    this->defaultFont = font;
}