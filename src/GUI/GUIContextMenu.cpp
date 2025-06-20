#include "GUIContextMenu.h"
#include <imgui.h>
#include <raylibHelper.h>
#include <imgui_internal.h>

namespace GUI
{
    void ContextMenu::Draw(SP_Circuit circuit)
    {
        circuit->m_logger.info("ContextMenu Draw called");
        if (visible) // only true on the frame right-click happens
        {
            ImGui::OpenPopup("ComponentContextMenu");
            visible = false; // reset immediately after opening
        }

        if (ImGui::BeginPopup("ComponentContextMenu"))
        {
            std::cout << "enter here" << std::endl;

            if (ImGui::MenuItem("Edit")) {
                std::cout << "Edit clicked" << std::endl;
            }

            if (ImGui::MenuItem("Properties")) {
                std::cout << "properties" << std::endl;
                RaylibHelper::Show(1);
            }

            if (ImGui::MenuItem("Delete")) {
                IInputHandler* selectedHandler = InputResolver::getSelectedHandler();
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
                }
            }

            ImGui::EndPopup();
        }
    }
    void ContextMenu::Update(SP_Circuit circuit)
    {
        circuit->m_logger.info("ContextMenu Update called");
    }
}
