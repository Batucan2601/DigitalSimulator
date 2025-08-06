#include "GUIContextMenu.h"
#include <imgui.h>
#include <raylibHelper.h>
#include <imgui_internal.h>

namespace GUI
{
    static void unregister_active_wire(SP_Circuit circuit)
    {
        for (auto it = InputResolver::handlers.begin(); it != InputResolver::handlers.end(); ++it)
        {
            if (*it == &circuit->active_wire)
            {
                InputResolver::UnregisterHandler(*it);
            }
        }
    }
    bool is_popup_open = false; // Global variable to track popup state
    void ContextMenu::Draw(SP_Circuit circuit)
    {
        circuit->m_logger.info("ContextMenu Draw called");
        if (visible) // only true on the frame right-click happens
        {
            ImGui::OpenPopup("ComponentContextMenu");
            unregister_active_wire(circuit);
            visible = false; // reset immediately after opening
        }
        if (ImGui::BeginPopup("ComponentContextMenu"))
        {
            //InputResolver::Block();
            is_popup_open = true; 

            if (ImGui::MenuItem("Edit")) {
            }

            if (ImGui::MenuItem("Properties")) {
                RaylibHelper::Show(1);
            }

            if (ImGui::MenuItem("Delete")) {
                IInputHandler* selectedHandler = InputResolver::getSelectedHandler();
                if(dynamic_cast<Component*>(selectedHandler))
                {
                    // remove the gate
                    for (size_t i = 0; i < circuit->connections.size(); i++)
                    {
                        if (circuit->connections[i].sourceGate.get() == selectedHandler ||
                            circuit->connections[i].targetGate.get() == selectedHandler)
                        {
                            circuit->connections.erase(circuit->connections.begin() + i);
                            i--;
                        }
                    }
                    for (size_t i = 0; i < circuit->gates.size(); i++)
                    {
                        if (circuit->gates[i].get() == selectedHandler)
                        {
                            circuit->gates.erase(circuit->gates.begin() + i);
                            i--;
                        }
                    }
                    InputResolver::UnregisterHandler(selectedHandler);
                }
                else if (dynamic_cast<CircuitElements::Connection*>(selectedHandler))
                {
                    // remove the connection
                    for (size_t i = 0; i < circuit->connections.size(); i++)
                    {

                        if (&circuit->connections[i] == selectedHandler )
                        {
                            circuit->connections.erase(circuit->connections.begin() + i);
                            InputResolver::UnregisterHandler(selectedHandler);
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
        circuitController->getCircuit()->m_logger.info("ContextMenu Update called");
    }
}
