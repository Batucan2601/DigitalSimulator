#include "GUI/LogicGateInfo.h"

#include "Component.h"
#include "LogicElements.h"
#include "LogicElementBase.h"
#include <imgui.h>
#include <misc/cpp/imgui_stdlib.h>
#include <raylib.h>
#include <SubCircuit.h>

namespace GUI
{

    void LogicGateInfo::Draw(SP_Circuit circuit)
    {
        (void)circuit;
        if (!visible)
        {
            return;
        }

        if (Component* d1 = dynamic_cast<Component*>(InputResolver::getSelectedHandler()))
        {
            GUITools_BasicLogicDisplay_draw(d1);
        }
    }
    void LogicGateInfo::Update(SP_Circuit circuit)
    {
        (void)circuit;
    }
    void LogicGateInfo::draw_Inputs(Component* logicGate)
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
                    change_connection_name(logicGate, true, inputs.name);
                }
                ImGui::SameLine();
                label = "X" + label;
                if (ImGui::Button(label.c_str()))
                {
                    logicGate->inputs.erase(logicGate->inputs.begin() + i);
                    logicGate->setPosition(logicGate->bd.x, logicGate->bd.y);
                }
                
                if(inputs.type == SignalType::INTERNAL)
                {
                    ImGui::SameLine();
                    label = "Internal";
                    label  =  label + "##xx" + std::to_string(i);
                }
                else if(inputs.type == SignalType::INPUT)
                {
                    ImGui::SameLine();
                    label  = "Input";
                    label  =  label + "##xx" + std::to_string(i);
                }
                if (ImGui::Button(label.c_str()))
                {
                    if(inputs.type == SignalType::INTERNAL)
                    {
                        inputs.type = SignalType::INPUT;
                    }
                    else if(inputs.type == SignalType::INPUT)
                    {
                        inputs.type = SignalType::INTERNAL;
                    }
                }   

                i++;
            }
            static std::string new_input_name = "";
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
    void LogicGateInfo::draw_Outputs(Component* logicGate)
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
                if(outputs.type == SignalType::INTERNAL)
                {
                    ImGui::SameLine();
                    label = "Internal";
                    label  =  label + "##xx" + std::to_string(i);
                }
                else if(outputs.type == SignalType::OUTPUT)
                {
                    ImGui::SameLine();
                    label  = "Output";
                    label  =  label + "##xx" + std::to_string(i);
                }
                if (ImGui::Button(label.c_str()))
                {
                    if(outputs.type == SignalType::INTERNAL)
                    {
                        outputs.type = SignalType::OUTPUT;
                    }
                    else if(outputs.type == SignalType::OUTPUT)
                    {
                        outputs.type = SignalType::INTERNAL;
                    }
                }   
                i++;
            }
            static std::string new_output_name = "";
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

    void LogicGateInfo::change_connection_name(Component* logicGate, bool is_input,
                                               std::string newName)
    {
        for (size_t i = 0; i < logicGate->circuit->connections.size(); i++)
        {
            if (logicGate->circuit->connections[i].sourceGate.get() == logicGate)
            {
                if (!is_input)  // output
                {
                    logicGate->circuit->connections[i].sourceLogic = newName;
                }
            }
            if (logicGate->circuit->connections[i].targetGate.get() == logicGate)
            {
                if (is_input)  // output
                {
                    logicGate->circuit->connections[i].targetLogic = newName;
                }
            }
        }
    }

    // Global or static variables for the UI state and texture.

    void LogicGateInfo::GUITools_BasicLogicDisplay_draw(Component* component)
    {
        float pos[2] = {component->bd.x, component->bd.y};
        ImGui::Begin("Logic Settings", &visible);
        ImGui::InputFloat2("Position", pos);

        if (dynamic_cast<InputElement*>(component)) {
            draw_Inputs(component);
        }
        else if (dynamic_cast<LogicElements::LogicGate*>(component)) {
            draw_Inputs(component);
            draw_Outputs(component);
        }
        else if (dynamic_cast<SubcircuitComponent*>(component)) {
            draw_Inputs(component);
            draw_Outputs(component);
        }

        // Draw interactive windows first.
       
        ImGui::End();

        component->bd.x = pos[0];
        component->bd.y = pos[1];
    }

}  // namespace GUI
