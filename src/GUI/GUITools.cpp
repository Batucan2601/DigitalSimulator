#include "GUI/GUITools.h"

#include "LogicElements.h"

#include <imgui.h>
#include <raylib.h>

namespace GUITools
{

    // Global or static variables for the UI state and texture.
    bool is_BLD_shown = false;  // Basic Logic Display flag.
    // UI state variables (persistent across frames).
    static void GUITools_BasicLogicDisplay_draw();

    GUIToolsDragDrop dragDrop = {DragDropState::IDLE, LogicElements::GateType::NONE};
    static void RenderGateButton(const std::string& gateName, LogicElements::GateInfo gateInfo);

    void GUITools_BasicLogicDisplay()
    {
        is_BLD_shown = !is_BLD_shown;
    }

    void GUITools_Display()
    {
        GUITools_BasicLogicDisplay_draw();
    }

    static void GUITools_BasicLogicDisplay_draw()
    {
        if (!is_BLD_shown)
        {
            return;
        }
        // Then, draw the drop area overlay on top if needed (and only during a drag operation).

        // Draw interactive windows first.
        ImGui::Begin("Components", &is_BLD_shown);
        {
            static ImGuiTreeNodeFlags base_flags = ImGuiTreeNodeFlags_OpenOnArrow |
                                                   ImGuiTreeNodeFlags_OpenOnDoubleClick |
                                                   ImGuiTreeNodeFlags_SpanAvailWidth;

            ImGuiTreeNodeFlags node_flags = base_flags;

            if (ImGui::TreeNodeEx("Logic Gates", node_flags))
            {
                for (const auto& gateInfo : *LogicElements::gateInfoList)
                {
                    RenderGateButton(gateInfo.name, gateInfo);
                }
                ImGui::TreePop();
            }

            if (ImGui::TreeNodeEx("Input/Output", node_flags))
            {
                // Get the gate info where GateType is INPUT
                auto it = std::find_if(LogicElements::gateInfoList->begin(),
                                       LogicElements::gateInfoList->end(),
                                       [](const LogicElements::GateInfo& gate)
                                       {
                                           return gate.type == LogicElements::GateType::INPUT;
                                       });

                if (it != LogicElements::gateInfoList->end())  // If found, render the button
                {
                    RenderGateButton(it->name, *it);
                }
                ImGui::TreePop();  // ✅ Correctly closing this node
            }
        }
        ImGui::End();
    }

    static void RenderGateButton(const std::string& gateName, LogicElements::GateInfo gateInfo)
    {
        float icon_size = 50.0f;

        // Get vertical alignment offsets
        float text_height = ImGui::GetTextLineHeight();
        float button_height = icon_size;
        float vertical_offset = (button_height - text_height) * 0.5f;

        // Align Text
        ImGui::SetCursorPosY(ImGui::GetCursorPosY() + vertical_offset);
        ImGui::Text("%s", gateName.c_str());

        // Keep on the same line
        ImGui::SameLine();

        // Reset Y position for ImageButton to maintain alignment
        ImGui::SetCursorPosY(ImGui::GetCursorPosY() - vertical_offset);

        ImTextureID textureID = (ImTextureID)gateInfo.filledTexture;

        // ✅ Fix: Generate unique button ID
        std::string button_id = "##button_" + gateName;
        if (ImGui::ImageButton(button_id.c_str(), textureID, ImVec2(icon_size, icon_size))) {}

        if (ImGui::BeginDragDropSource())
        {
            ImGui::SetDragDropPayload("IMAGE_DRAG", &gateInfo.type,
                                      sizeof(LogicElements::GateType));

            // Show the image as a preview while dragging.
            ImGui::Image(textureID, ImVec2(100, 100));
            ImGui::Text("Dragging: %s", gateName.c_str());
            ImGui::EndDragDropSource();

            dragDrop.gateType = gateInfo.type;
            dragDrop.state = DragDropState::DRAGGING;
        }
        // Handle Drag State
        if (dragDrop.state == DragDropState::DROPPED)
        {
            dragDrop.state = DragDropState::IDLE;
        }
        if (!ImGui::IsMouseDragging(0) && dragDrop.state == DragDropState::DRAGGING)
        {
            dragDrop.state = DragDropState::DROPPED;
        }
    }

}  // namespace GUITools
