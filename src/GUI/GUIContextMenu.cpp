#include "GUIContextMenu.h"
#include "common_types.h"
#include <imgui.h>
#include <Application.h>
#include <imgui_internal.h>

namespace GUI
{
    bool is_popup_open = false; // Global variable to track popup state
    void ContextMenu::Draw(std::shared_ptr<CircuitController> circuitController)
    {
        if (visible) // only true on the frame right-click happens
        {
            ImGui::OpenPopup("ComponentContextMenu");
            InputResolver::UnregisterHandler(circuitController->getCircuit()->active_wire->getInstance());
            visible = false; // reset immediately after opening
        }
        if (ImGui::BeginPopup("ComponentContextMenu"))
        {
            //InputResolver::Block();
            is_popup_open = true; 

            if (ImGui::MenuItem("Edit")) {
            }

            if (ImGui::MenuItem("Properties")) {
                
                Application::Show(GUIWindowType::LogicGateInfo);
            }
            SP_Circuit circuit = circuitController->getCircuit();
            if (ImGui::MenuItem("Delete")) {
                std::vector<std::weak_ptr<IInputHandler>> selectedHandlerVec = InputResolver::getSelectedHandler();
                std::shared_ptr<IInputHandler> selectedHandler; 
                if(selectedHandlerVec.size() == 1  )
                {
                    selectedHandler = selectedHandlerVec[0].lock();
                }
                if(dynamic_cast<Component*>(selectedHandler.get()))
                {
                    // remove the gate
                    for (size_t i = 0; i < circuit->connections.size(); i++)
                    {
                        if (circuit->connections[i].get()->sourceGate.get() == selectedHandler.get() ||
                            circuit->connections[i].get()->targetGate.get() == selectedHandler.get())
                        {
                            circuit->connections.erase(circuit->connections.begin() + i);
                            i--;
                        }
                    }
                    for (size_t i = 0; i < circuit->gates.size(); i++)
                    {
                        if (circuit->gates[i].get() == selectedHandler.get())
                        {
                            circuit->gates.erase(circuit->gates.begin() + i);
                            i--;
                        }
                    }
                    InputResolver::UnregisterHandler(selectedHandler);
                }
                else if (dynamic_cast<CircuitElements::Connection*>(selectedHandler.get()))
                {
                    // remove the connection
                    for (size_t i = 0; i < circuit->connections.size(); i++)
                    {

                        if (circuit->connections[i].get() == selectedHandler.get() )
                        {
                            CircuitController::getInstance()->removeConnection(circuit->connections[i]);
                            break; 
                        }
                    }
                }
            }
            ImGui::EndPopup();
        }
        else
        {
            if( is_popup_open)
            {
                is_popup_open = false;
                InputResolver::Unblock();
                //InputResolver::setSelectedHandler(nullptr); // Reset the selected handler
            }
        }
       
    }
    void ContextMenu::Update(std::shared_ptr<CircuitController> circuitController)            
    {
        (*circuitController);
    }
}
