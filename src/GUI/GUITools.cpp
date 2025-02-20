#include "GUI/GUITools.h"
#include "LogicElements.h"
#include <imgui.h>
#include <raylib.h>

namespace GUITools
{
    // Global or static variables for the UI state and texture.
    bool is_BLD_shown = false; // Basic Logic Display flag.
    // UI state variables (persistent across frames).
    static void GUITools_BasicLogicDisplay_draw();
    GUIToolsDragDrop dragDrop = { DragDropState::IDLE , LogicElements::GateType::NONE };
    void GUITools_BasicLogicDisplay()
    {
        is_BLD_shown = true;
    }
    void GUITools_DragDrop(LogicElements::GateType type, std::string type_name)
    {
        // Make sure the texture is loaded before using it.
        // Properly cast the texture ID for ImGui.
        ImGuiViewport* viewport = ImGui::GetMainViewport();

        if (ImGui::Button(type_name.c_str()))
        {
            // Button action.
        }
        
        if (ImGui::BeginDragDropSource())
        {
            const char* payload = "Hello, ImGui!";
            ImGui::SetDragDropPayload("IMAGE_DRAG", payload, strlen(payload) + 1);

            // Show the image as a preview while dragging.
            ImGui::Image((ImTextureID)&LogicElements::logicElementTextures[type], ImVec2(100, 100));
            ImGui::Text("Dragging Image");
            ImGui::EndDragDropSource();

            dragDrop.gateType = type;
            dragDrop.state = DragDropState::DRAGGING;
        }
        if (dragDrop.state == DragDropState::DROPPED)
        {
            dragDrop.state == DragDropState::IDLE;
        }
        if (!ImGui::IsMouseDragging(0) && dragDrop.state == DragDropState::DRAGGING)
        {
            dragDrop.state = DragDropState::DROPPED;
        }
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
        ImGui::Begin("Basic Logics", &is_BLD_shown, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoMove);

        // Prevent interactions behind the window
        if (ImGui::IsWindowHovered(ImGuiHoveredFlags_AnyWindow))
        {
            ImGui::SetNextFrameWantCaptureMouse(true);
        }
        if (ImGui::CollapsingHeader("Basic Gates"))
        {
            GUITools_DragDrop(LogicElements::GateType::AND, "AND Gate");
            GUITools_DragDrop(LogicElements::GateType::OR, "OR Gate");
            GUITools_DragDrop(LogicElements::GateType::NOT, "NOT Gate");
            GUITools_DragDrop(LogicElements::GateType::XAND, "XAND Gate");
            GUITools_DragDrop(LogicElements::GateType::XOR, "XOR Gate");
            GUITools_DragDrop(LogicElements::GateType::INPUT, "INPUT Gate");
        }

        ImGui::End();


    }

}
