#include "GUI/GUIManager.h"
#include "GUI/GUIStyle.h"
#include "GUI/GUIMenuBar.h"
#include "GUI/GUILogic.h"
#include "GUI/GUISaveSystem.h"
#include <rlImGui.h>
#include <imgui.h>
#include <GUI/GUITools.h>

void GUIManager::Init()
{
    rlImGuiSetup(true); // Initialize ImGui
    GUIStyle::init();    // Set up custom ImGui styles
}
static void draw_parent_screen()
{
    // Get IO for display size
    ImGuiIO& io = ImGui::GetIO();
    // Determine your menubar height (e.g., using ImGui's frame height)
    float menuBarHeight = ImGui::GetFrameHeight();

    // Offset the dockspace window to start after the menubar
    ImGui::SetNextWindowPos(ImVec2(0, menuBarHeight));
    ImGui::SetNextWindowSize(ImVec2(io.DisplaySize.x, io.DisplaySize.y - menuBarHeight));

    // Configure window flags for an invisible window
    ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoTitleBar |
        ImGuiWindowFlags_NoResize |
        ImGuiWindowFlags_NoMove |
        ImGuiWindowFlags_NoCollapse |
        ImGuiWindowFlags_NoBackground |
        ImGuiWindowFlags_NoBringToFrontOnFocus;

    ImGui::Begin("InvisibleDockSpace", nullptr, window_flags);

    // Create the dockspace (adjust flags as needed)
    ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
    ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), ImGuiDockNodeFlags_PassthruCentralNode);

    ImGui::End();
}
; // this is acutally needed for save and load purposes 
void GUIManager::Draw(std::shared_ptr<CircuitElements::Circuit> circuit, RenderTexture& renderTexture)
{
    rlImGuiBegin();
    draw_parent_screen();
    if (ImGui::Begin("Raylib Scene"))
    {
        ImGui::Image((ImTextureID)&renderTexture.texture,
        ImVec2((float)renderTexture.texture.width, (float)renderTexture.texture.height),
        ImVec2(0, 0), ImVec2(1, 1));  // Adjust UVs if necessary
        ImGui::End();
     }
    // Draw individual components
    // GUIMenuBar::Draw();
    guiMenuBar.Draw(circuit);
    GUITools::GUITools_Display();
    GUISaveSystem::draw();
    // GUILogic::Draw();
    rlImGuiEnd();
}

void GUIManager::Cleanup()
{
    rlImGuiShutdown(); // Clean up ImGui resources if necessary
}
