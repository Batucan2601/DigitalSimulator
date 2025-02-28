#include "GUI/GUILogicSetting.h"
#include "Component.h"
#include "LogicElements.h"
#include "Component.h"
#include <imgui.h>
#include <misc/cpp/imgui_stdlib.h>
#include <raylib.h>

namespace GUILogicSetting
{
    static void draw_Inputs(LogicElements::LogicGate* logicGate);
    static void draw_Outputs(LogicElements::LogicGate* logicGate);
    static void change_connection_name(LogicElements::LogicGate*  logicGate, bool is_input , std::string newName);

    
    static std::string new_input_name = "";
    static std::string new_output_name = "";
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
    static void draw_Inputs(LogicElements::LogicGate* logicGate)
    {
        if (ImGui::TreeNodeEx("Inputs"))
        {
            int i = 0;
            for (auto& inputs : logicGate->inputs)
            {
                // Create a unique identifier that doesn't show in the UI.
                std::string label = "##xx" + std::to_string(i);
                // Directly pass the reference to the string.
                if (ImGui::InputText(label.c_str(), &inputs.name))
                {
                    change_connection_name(logicGate , true ,  inputs.name);
                }
                ImGui::SameLine();
                label = "X" + label ;
                if( ImGui::Button(label.c_str()) ) 
                {
                    logicGate->inputs.erase(logicGate->inputs.begin() + i);
                    logicGate->setPosition(logicGate->bd.x, logicGate->bd.y);
                }
                i++;
            }
            ImGui::InputText("Name", &new_input_name);
            if (ImGui::Button("Insert"))
            {
                Signal s(new_input_name);
                logicGate->inputs.push_back(s);
                logicGate->setPosition(logicGate->bd.x, logicGate->bd.y);
                new_input_name = "";
            }
            ImGui::TreePop();
        }
    }
    static void draw_Outputs(LogicElements::LogicGate* logicGate)
    {
        if (ImGui::TreeNodeEx("Outputs"))
        {
            int i = 1;
            for (auto& outputs : logicGate->outputs)
            {
                // Create a unique identifier that doesn't show in the UI.
                std::string label = "##xx" + std::to_string(i);
                // Directly pass the reference to the string.
                if (ImGui::InputText(label.c_str(), &outputs.name))
                {
                    change_connection_name(logicGate, false, outputs.name);
                }
                i++;
            }
            ImGui::InputText("Name", &new_output_name);
            if (ImGui::Button("Insert"))
            {
                Signal s(new_output_name);
                logicGate->outputs.push_back(s);
                logicGate->setPosition(logicGate->bd.x, logicGate->bd.y);
                new_output_name = "";
            }
            ImGui::TreePop();
        }
    }
    static void GUITools_BasicLogicDisplay_draw(LogicElements::LogicGate* logicGate)
    {
        // Draw interactive windows first.
        float pos[2] = { logicGate->bd.x, logicGate->bd.y };
        ImGui::Begin("Logic Settings", &is_shown);
        ImGui::InputFloat2("Position", pos);
        draw_Inputs(logicGate);
        draw_Outputs(logicGate);
        ImGui::End();

        logicGate->bd.x = pos[0];
        logicGate->bd.y = pos[1];


    }

    static void change_connection_name(LogicElements::LogicGate* logicGate, bool is_input, std::string newName)
    {
        for (size_t i = 0; i < logicGate->circuit->connections.size(); i++)
        {
            if (logicGate->circuit->connections[i].sourceGate.get() == logicGate)
            {
                if (!is_input) //output
                {
                    logicGate->circuit->connections[i].sourceLogic = newName;
                }
            }
            if (logicGate->circuit->connections[i].targetGate.get() == logicGate)
            {
                if (is_input) //output
                {
                    logicGate->circuit->connections[i].targetLogic= newName;
                }
            }
        }
    }
}
