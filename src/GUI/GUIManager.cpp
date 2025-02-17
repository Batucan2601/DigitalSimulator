#include "GUI/GUIManager.h"
#include "GUI/GUIStyle.h"
#include "GUI/GUIMenuBar.h"
#include "GUI/GUILogic.h"
#include <rlImGui.h>
#include <imgui.h>
#include <GUI/GUITools.h>

void GUIManager::Init()
{
    rlImGuiSetup(true); // Initialize ImGui
    GUIStyle_init();    // Set up custom ImGui styles
}

void GUIManager::Draw()
{
    rlImGuiBegin();

    // Draw individual components
    // GUIMenuBar::Draw();
    guiMenuBar.Draw();
    GUITools_Display();
    // GUILogic::Draw();

    rlImGuiEnd();
}

void GUIManager::Cleanup()
{
    rlImGuiShutdown(); // Clean up ImGui resources if necessary
}
