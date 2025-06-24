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
                static char buf[128] = {0};
                strncpy(buf, inputs.name.c_str(), sizeof(buf));
                buf[sizeof(buf) - 1] = '\0';
                if (ImGui::InputText(label.c_str(), buf, sizeof(buf)))
                {
                    bool is_change_connection_name = change_InOut_name(logicGate, true, inputs.name, buf);
                    if (is_change_connection_name)
                    {
                        inputs.name = buf;  // Update the name in the inputs vector
                    }
                    else
                    {
                        ImGui::TextColored({1.0f, 0.0f, 0.0f, 1.0f}, "Name already exists!");
                        strncpy(buf, inputs.name.c_str(), sizeof(buf)); // Reset to original name
                        inputs.name[sizeof(buf) - 1] = '\0'; // Ensure null termination
                    }
                    
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
                static char buf[128] = {0};
                strncpy(buf, outputs.name.c_str(), sizeof(buf));
                buf[sizeof(buf) - 1] = '\0';
                if (ImGui::InputText(label.c_str(), buf, sizeof(buf)))
                {
                    bool is_change_connection_name = change_InOut_name(logicGate, true, outputs.name, buf);
                    if (is_change_connection_name)
                    {
                        outputs.name = buf;  // Update the name in the inputs vector
                    }
                    else
                    {
                        ImGui::TextColored({1.0f, 0.0f, 0.0f, 1.0f}, "Name already exists!");
                        strncpy(buf, outputs.name.c_str(), sizeof(buf)); // Reset to original name
                        outputs.name[sizeof(buf) - 1] = '\0'; // Ensure null termination
                    }
                    
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

    bool LogicGateInfo::change_InOut_name(Component* logicGate, bool is_input, const std::string& oldName, const std::string& newName)
    {
        // Update component's inputs or outputs
        for (auto& signal : logicGate->inputs)
        {
            if (signal.name == newName)
            {
                return false; 
            }
        }
        for (auto& signal : logicGate->outputs)
        {
            if (signal.name == newName)
            {
                return false; 
            }
        }
        // Update connections
        for (auto& conn : logicGate->circuit->connections)
        {
            if (conn.targetGate.get() == logicGate && conn.targetLogic == oldName)
            {
                conn.targetLogic = newName;
            }
            else if ( conn.sourceGate.get() == logicGate && conn.sourceLogic == oldName)
            {
                conn.sourceLogic = newName;
            }
        }

        return true;
    }
    static bool check_same_name(Component* component)
    {
        // This function checks if the names of inputs and outputs are unique.
        // If not, it returns false.
        // For now, we assume that the names are unique.
        for (size_t i = 0; i < component->circuit->gates.size(); i++)
        {
            if (component->circuit->gates[i]->m_name == component->m_name &&
                component->circuit->gates[i].get() != component)
            {
                ImGui::TextColored({1.0f, 0.0f, 0.0f, 1.0f}, "Name already exists!");
                return false;  // Name is not unique
            }
        }
        
        return true;
    }
    static void draw_name(Component* component)
    {
        static char buf[128] = {0};
        strncpy(buf, component->m_name.c_str(), sizeof(buf));
        buf[sizeof(buf) - 1] = '\0';

        if (ImGui::InputText("Component name: ", buf, sizeof(buf))) {
            
            std::string old_name = component->m_name;
            component->m_name = std::string(buf);

            if (!check_same_name(component)) {
                component->m_name = old_name;  // Revert
                strncpy(buf, old_name.c_str(), sizeof(buf));
                buf[sizeof(buf) - 1] = '\0';
            }
        }
        check_same_name(component);
    }
    // Global or static variables for the UI state and texture.
    void LogicGateInfo::GUITools_BasicLogicDisplay_draw(Component* component)
    {
        float pos[2] = {component->bd.x, component->bd.y};
        ImGui::Begin("Logic Settings", &visible);
        draw_name(component);
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
