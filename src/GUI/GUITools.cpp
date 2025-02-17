#include "GUI/GUITools.h"
#include "LogicElements.h"
#include <imgui.h>
#include <raylib.h>

// Global or static variables for the UI state and texture.
bool is_BLD_shown = false; // Basic Logic Display flag.
static Texture image = { 0 };  // Initialize to zero.
static bool textureLoaded = false;

// UI state variables (persistent across frames).
static bool enableFeature = false;
static float parameter = 0.0f;

static void GUITools_BasicLogicDisplay_draw();

void GUITools_BasicLogicDisplay()
{
    is_BLD_shown = true;
}
void GUITools_DragDrop(LogicElements::GateType type, std::string type_name)
{
        // Make sure the texture is loaded before using it.
        // Properly cast the texture ID for ImGui.
        if (ImGui::Button(type_name.c_str()))
        {
            // Button action.
        }
        // Begin the drag source from the image.
        if (ImGui::BeginDragDropSource())
        {
            ImGui::SetDragDropPayload("IMAGE_DRAG", nullptr, 0);

            // Show the image as a preview while dragging.
            ImGui::Image((ImTextureID)&LogicElements::logicElementTextures[type], ImVec2(100, 100));
            ImGui::Text("Dragging Image");
            ImGui::EndDragDropSource();
        }
        // Drop target: This area will accept the dragged item.
        ImGui::Text("Drop Here to create something:");
        ImGui::BeginChild("DropArea", ImVec2(200, 100), true);
        {
            if (ImGui::BeginDragDropTarget())
            {
                if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("IMAGE_DRAG"))
                {
                    ImGui::Text("Dragging 'Drag Me'");
                }
                ImGui::EndDragDropTarget();
            }
        }
        ImGui::EndChild();

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

    ImGui::Begin("Basic Logics", &is_BLD_shown);
    if (ImGui::CollapsingHeader("Basic Gates"))
    {
        GUITools_DragDrop(LogicElements::GateType::AND , "AND Gate");
        GUITools_DragDrop(LogicElements::GateType::OR , "OR Gate");
        GUITools_DragDrop(LogicElements::GateType::NOT , "NOT Gate");
        GUITools_DragDrop(LogicElements::GateType::XAND , "XAND Gate");
        GUITools_DragDrop(LogicElements::GateType::XOR, "XOR Gate");
    }
    ImGui::End();
}
