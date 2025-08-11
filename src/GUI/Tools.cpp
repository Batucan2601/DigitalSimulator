#include "GUI/Tools.h"

#include "LogicElements.h"
#include "ComponentTextures.h"

#include <imgui.h>
#include <raylib.h>
#include <Util/Utils.h>

namespace GUI
{
    GUIToolsDragDrop dragDrop = {DragDropState::IDLE, CircuitElements::ComponentType::NONE};

    void Tools::Draw(std::shared_ptr<CircuitController> circuitController )
    {
        (void)circuitController;
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
                for (const auto& gateInfo : *LogicElements::componentInfoList)
                {
                    // Render each gate button
                    RenderGateButton(gateInfo.name, gateInfo);
                }
                ImGui::TreePop();
            }

            if (ImGui::TreeNodeEx("Input/Output", node_flags))
            {
                // Get the gate info where CircuitElements::ComponentType is INPUT
                auto it = std::find_if(LogicElements::componentInfoList->begin(),
                                       LogicElements::componentInfoList->end(),
                                       [](const CircuitElements::ComponentInfo& gate)
                                       {
                                           return gate.type == CircuitElements::ComponentType::INPUT;
                                       });

                if (it != LogicElements::componentInfoList->end())  // If found, render the button
                {
                    RenderGateButton(it->name, *it);
                }
                ImGui::TreePop();  // ✅ Correctly closing this node
            }
        }
        ImGui::End();
    }
    Vector2 mouse_pos;
    void Tools::Update(std::shared_ptr<CircuitController> circuitController)
    {
        if (GUI::dragDrop.state == GUI::DragDropState::DRAGGING)
        {
            mouse_pos = AppSettings::appSettings.mousePos;
            Rectangle rec = {mouse_pos.x, mouse_pos.y, 0, 0};
            Vector2 pos = Utils::SnapToNearestGrid(rec);
            circuitController->getCircuit()->selected_wires.wire_hovering = pos;
            circuitController->getCircuit()->is_GUIdragdragging = true;
        }
        if (circuitController->getCircuit()->is_GUIdragdragging && GUI::dragDrop.state == GUI::DragDropState::IDLE)
        {
            circuitController->getCircuit()->is_GUIdragdropped = true;
            circuitController->getCircuit()->is_GUIdragdragging = false;

            // add the new circuit
            std::string new_gate = "or_gate_logger";
            auto gate = LogicElements::LogicElementFactory::createComponent(GUI::dragDrop.componentType, new_gate);
            //circuit->addGate(gate);
            circuitController->addComponent(gate);
            if (GUI::dragDrop.componentType != CircuitElements::ComponentType::NONE)
            {
                
                //Vector2 newpos = {circuitController->getCircuit()->selected_wires.wire_hovering.x,
                //circuitController->getCircuit()->selected_wires.wire_hovering.y};
                //circuitController->moveComponent(circuitController->getCircuit()->gates
                //[circuitController->getCircuit()->gates.size() - 1],  ,  );

                circuitController->getCircuit()->gates[circuitController->getCircuit()->gates.size() - 1]->setPosition(
                    circuitController->getCircuit()->selected_wires.wire_hovering.x,
                    circuitController->getCircuit()->selected_wires.wire_hovering.y);
                GUI::dragDrop.componentType = CircuitElements::ComponentType::NONE;
            }
        }
    }
    void Tools::RenderGateButton(const std::string& gateName, CircuitElements::ComponentInfo gateInfo)
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
                                      sizeof(CircuitElements::ComponentType));

            // Show the image as a preview while dragging.
            ImGui::Image(textureID, ImVec2(100, 100));
            ImGui::Text("Dragging: %s", gateName.c_str());
            ImGui::EndDragDropSource();

            dragDrop.componentType = gateInfo.type;
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
