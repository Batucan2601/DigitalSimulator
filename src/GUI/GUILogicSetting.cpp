#include "GUI/GUILogicSetting.h"
#include "Component.h"
#include "LogicElements.h"
#include <imgui.h>
#include <raylib.h>

namespace GUILogicSetting
{
    // Global or static variables for the UI state and texture.
    bool is_shown = false; // Basic Logic Display flag.
    static void GUITools_BasicLogicDisplay_draw(LogicElements::LogicGate* logicGate);
    void Draw()
    {
        if (LogicElements::LogicGate* d1 = dynamic_cast<LogicElements::LogicGate*>(InputResolver::getSelectedHandler()))
        {
            GUITools_BasicLogicDisplay_draw(d1);
        }
    }
    static void GUITools_BasicLogicDisplay_draw(LogicElements::LogicGate* logicGate)
    {
        // Draw interactive windows first.
        float pos[2] = { logicGate->bd.x, logicGate->bd.y };
        ImGui::Begin("Logic Settings", &is_shown);
        ImGui::InputFloat2("Position", pos);
        ImGui::End();

        logicGate->bd.x = pos[0];
        logicGate->bd.y = pos[1];


    }
}
