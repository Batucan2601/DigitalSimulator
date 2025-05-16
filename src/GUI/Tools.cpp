#include "GUI/Tools.h"

#include "LogicElements.h"

#include <imgui.h>
#include <raylib.h>
#include <Util/utils.h>

namespace GUI
{
    GUIToolsDragDrop dragDrop = {DragDropState::IDLE, LogicElements::GateType::NONE};

    void Tools::Draw(SP_Circuit circuit)
    {
        (void)circuit;
        if (!visible)
        {
            return;
        }
        // Then, draw the drop area overlay on top if needed (and only during a drag operation).

        // Draw interactive windows first.
        ImGui::Begin(title.c_str(), &visible);
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
    void Tools::Update(SP_Circuit circuit)
    {
        if (GUI::dragDrop.state == GUI::DragDropState::DRAGGING)
        {
            //Vector2 mouse_pos = GetMousePosition();
            //ConvertMouseCoord(mouse_pos);
            //
            //Rectangle rec = {mouse_pos.x, mouse_pos.y, 0, 0};
            //Vector2 pos = Utils::SnapToNearestGrid(rec);
            //circuit->selected_wires.wire_hovering = pos;
            circuit->is_GUIdragdragging = true;
        }
        if (circuit->is_GUIdragdragging && GUI::dragDrop.state == GUI::DragDropState::IDLE)
        {
            circuit->is_GUIdragdropped = true;
            circuit->is_GUIdragdragging = false;

            // add the new circuit
            std::string new_gate = "or_gate_logger";
            std::shared_ptr<LogicElements::LogicGate> gate;
            gate = LogicElements::LogicElementFactory::createGate(GUI::dragDrop.gateType, new_gate);
            circuit->addGate(gate);

            if (GUI::dragDrop.gateType != LogicElements::GateType::NONE)
            {
                circuit->gates[circuit->gates.size() - 1]->setPosition(
                    circuit->selected_wires.wire_hovering.x,
                    circuit->selected_wires.wire_hovering.y);
                GUI::dragDrop.gateType = LogicElements::GateType::NONE;
            }
        }
    }
    void Tools::RenderGateButton(const std::string& gateName, LogicElements::GateInfo gateInfo)
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

}  // namespace GUI
