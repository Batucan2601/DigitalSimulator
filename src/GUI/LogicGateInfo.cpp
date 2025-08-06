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

        IInputHandler* handler = InputResolver::getSelectedHandler();
        GUITools_BasicLogicDisplay_draw(handler);
    }
    void LogicGateInfo::Update(std::shared_ptr<CircuitController> circuit)
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
                    bool is_change_connection_name = change_InOut_name(logicGate, inputs.name, buf);
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
                
                ImGui::SameLine();
                //ImGui::InputInt("Bus size", &inputs.val[0].width);
                int busSize = inputs.val.size();  // Start with current size
                std::string busSizeLabel = "Bus size##" + std::to_string(i);
                ImGui::InputInt(busSizeLabel.c_str(), &busSize);

                if (busSize < 0)
                    busSize = 0;  // Prevent negative size

                inputs.val.resize(busSize);
                
                i++;
            }
            if (dynamic_cast<LogicElements::LogicGate*>(logicGate)) 
            {
                for(int i = 0; i < (int)logicGate->inputs.size()-1; i++)
                {
                    if(logicGate->inputs[i].val.size() != 
                    logicGate->inputs[i+1].val.size() )
                    {
                        ImGui::TextColored({1.0f, 0.0f, 0.0f, 1.0f}, "Bus size mismatch!");
                        //logicGate->inputs[i].val.resize(logicGate->inputs[i+1].val.size());
                    }
                }
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
    //void LogicGateInfo::draw_Connection(Component* connection)
    //{
    //    //std::string source = connection->
    //    //ImGui::Text()
//
    //}
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
                    bool is_change_connection_name = change_InOut_name(logicGate, outputs.name, buf);
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

                int busSize = outputs.val.size();  // Start with current size
                std::string busSizeLabel = "Bus size##" + std::to_string(i);
                ImGui::InputInt(busSizeLabel.c_str(), &busSize);

                if (busSize < 0)
                    busSize = 0;  // Prevent negative size

                outputs.val.resize(busSize);

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

    bool LogicGateInfo::change_InOut_name(Component* logicGate, const std::string& oldName, const std::string& newName)
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
    void LogicGateInfo::GUITools_BasicLogicDisplay_draw(IInputHandler* component)
    {
        if (auto comp = dynamic_cast<Component*>(component))
        {
            float pos[2] = {comp->bd.x, comp->bd.y};
            ImGui::Begin("Logic Settings", &visible);
            
            draw_name(comp);
            ImGui::InputFloat2("Position", pos);

            if (dynamic_cast<InputElement*>(component)) {
                draw_Outputs(comp);
            }
            else if (dynamic_cast<LogicElements::LogicGate*>(component)) {
                draw_Inputs(comp);
                draw_Outputs(comp);
            }
            else if (dynamic_cast<SubcircuitComponent*>(component)) {
                draw_Inputs(comp);
                draw_Outputs(comp);
            }

            ImGui::End();

            comp->bd.x = pos[0];
            comp->bd.y = pos[1];
        }
        else if (auto connection = dynamic_cast<CircuitElements::Connection*>(component))
        {
            if( connection->targetGate.get() == nullptr ||
                connection->sourceGate.get() == nullptr)
            {
                return;  // If the connection is not valid, do not draw the settings.
            }
            ImGui::Begin("Connection Settings", &visible);
            ImGui::Text("Source: %s", connection->sourceGate->m_name.c_str());
            ImGui::Text("Source Output: %s", connection->sourceLogic.c_str());
            ImGui::Text("Target: %s", connection->targetGate->m_name.c_str());
            ImGui::Text("Target Input: %s", connection->targetLogic.c_str());
            int inputIndex = connection->sourceGate->getOutputByName(connection->sourceLogic); 
            int outputIndex = connection->targetGate->getInputByName(connection->targetLogic);
            int inputSize = connection->targetGate->inputs[outputIndex].val.size();
            int outputSize = connection->sourceGate->outputs[inputIndex].val.size();
            if (inputIndex < 0 || outputIndex < 0)
            {
                ImGui::TextColored({1.0f, 0.0f, 0.0f, 1.0f}, "Invalid connection!");
                ImGui::End();
                return; 
            } 
            else if(inputSize != outputSize )
            {
                ImGui::TextColored({1.0f, 0.0f, 0.0f, 1.0f}, "Input and Output sizes do not match!");
                ImGui::End();
                return; 
            }
            ImGui::Text("Bus Size: %d", inputSize);
            //ImGui::Text("Bus value: %s", connection->targetLogic.c_str());
            std::string s = connection->sourceGate->outputs[inputIndex].toString();
            ImGui::Text("Connection Value: %s", s.c_str());
            // Draw settings for connection...
            ImGui::End();
        }
        
    }

}  // namespace GUI
