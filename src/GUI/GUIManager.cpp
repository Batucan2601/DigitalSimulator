#include "GUI/GUIManager.h"

#include "GUI/GUILogic.h"
#include "GUI/GUIMenuBar.h"
#include "GUI/GUISaveSystem.h"
#include "GUI/GUISettings.h"
#include "GUI/GUIStyle.h"

#include <GUI/GUIEditor.h>
#include <GUI/GUILogicSetting.h>
#include <GUI/GUITools.h>
#include <imgui.h>
#include <rlImGui.h>

bool GUIManager::showDemoWindow = false;

void GUIManager::Init()
{
    rlImGuiSetup(true);  // Initialize ImGui
    GUIStyle::init();    // Set up custom ImGui styles
}

void GUIManager::Draw(std::shared_ptr<CircuitElements::Circuit> circuit)
{
    rlImGuiBegin();
    DrawDockingSpace();

    DrawEditor(circuit);

    DrawMainMenu(circuit);

    DrawTools();

    DrawSettings();

    DrawSaveDialog();

    DrawDemoWindow();

    DrawLogicSetting();

    // if(GUIEditor::isEditorShown)
    // {
    //     GUIEditor::Draw();
    // }

    rlImGuiEnd();
}

void GUIManager::DrawTools()
{
    GUITools::GUITools_Display();
}

void GUIManager::DrawSettings()
{
    GUISettings::DisplaySettings();
}

void GUIManager::DrawLogicSetting()
{
    GUILogicSetting::Draw();
}

void GUIManager::DrawSaveDialog()
{
    GUISaveSystem::draw();
}

void GUIManager::DrawEditor(std::shared_ptr<CircuitElements::Circuit> circuit)
{
    GUIEditor::Draw(circuit);
}

void GUIManager::DrawMainMenu(std::shared_ptr<CircuitElements::Circuit> circuit)
{
    guiMenuBar.Draw(circuit);
}

void GUIManager::DrawDockingSpace()
{
    // Get IO for display size
    ImGuiIO& io = ImGui::GetIO();
    // Determine your menubar height (e.g., using ImGui's frame height)
    float menuBarHeight = ImGui::GetFrameHeight();

    // Offset the dockspace window to start after the menubar
    ImGui::SetNextWindowPos(ImVec2(0, menuBarHeight));
    ImGui::SetNextWindowSize(ImVec2(io.DisplaySize.x, io.DisplaySize.y - menuBarHeight));

    // Configure window flags for an invisible window
    ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize |
                                    ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse |
                                    ImGuiWindowFlags_NoBackground |
                                    ImGuiWindowFlags_NoBringToFrontOnFocus;

    ImGui::Begin("InvisibleDockSpace", nullptr, window_flags);

    // Create the dockspace (adjust flags as needed)
    ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
    ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), ImGuiDockNodeFlags_PassthruCentralNode);

    ImGui::End();
};  // this is acutally needed for save and load purposes

void GUIManager::DrawDemoWindow()
{
    if (settings.showDemoWindow)
        ImGui::ShowDemoWindow(&settings.showDemoWindow);
}

void GUIManager::Cleanup()
{
    rlImGuiShutdown();  // Clean up ImGui resources if necessary
}
