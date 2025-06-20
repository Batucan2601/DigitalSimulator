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
                std::cout << "Delete clicked" << std::endl;
            }

            ImGui::EndPopup();
        }
    }
    void ContextMenu::Update(SP_Circuit circuit)
    {
        circuit->m_logger.info("ContextMenu Update called");
    }
}
