#include "GUI/GUILogicSetting.h"
#include "LogicElements.h"
#include <imgui.h>
#include <raylib.h>

namespace GUILogicSetting
{
    // Global or static variables for the UI state and texture.
    bool is_shown = false; // Basic Logic Display flag.
    std::shared_ptr<LogicElements::LogicGate> gateInfo;// Basic Logic Display flag.
    static void GUITools_BasicLogicDisplay_draw();
    void display()
    {
        GUITools_BasicLogicDisplay_draw();
    }
    static void GUITools_BasicLogicDisplay_draw()
    {
        if (!is_shown)
        {
            return;
        }

        // Draw interactive windows first.
        ImGui::Begin("Logic Settings", &is_shown);
        
        ImGui::End();


    }
}
