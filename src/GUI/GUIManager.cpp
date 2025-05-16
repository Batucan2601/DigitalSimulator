#include <GUI/GUIManager.h>
#include <GUI/include.h>
#include <imgui.h>
#include <rlImGui.h>
#include "appSettings.h"

void GUIManager::Init()
{
    // Initialize ImGui and apply custom styles
    rlImGuiSetup(true);
    GUIStyle::init();

    // Clear existing windows
    windows.clear();

    // Create and add windows to the list
    windows.push_back(std::make_unique<GUI::Settings>());
    windows.push_back(std::make_unique<GUI::LogicGateInfo>());
    windows.push_back(std::make_unique<GUI::SaveLoad>());
    windows.push_back(std::make_unique<GUI::Tools>());

    // Initialize and add the editor window
    auto editor = std::make_unique<GUI::Editor>();
    editor->Init(AppSettings::appSettings.screenWidth, AppSettings::appSettings.screenHeight);
    windows.push_back(std::move(editor));  // Move to maintain ownership

    // Add the menu bar
    auto menuBar = std::make_unique<GUI::GUIMenuBar>();
    menuBar->Init();
    windows.push_back(std::move(menuBar));

    // Register windows in the menu bar
    auto* guiMenuBar = dynamic_cast<GUI::GUIMenuBar*>(windows.back().get());
    if (guiMenuBar)
    {
        guiMenuBar->SetWindowList(windows);
    }
    else
    {
        std::cerr << "Error: Failed to retrieve GUIMenuBar instance." << std::endl;
    }
}

void GUIManager::Draw(SP_Circuit circuit)
{
    for (auto& window : windows)
    {
        window->Draw(circuit);
    }
    DrawDemoWindow();
}

void GUIManager::Update(SP_Circuit circuit)
{
    for (auto& window : windows)
    {
        window->Update(circuit);
    }
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
    if (AppSettings::appSettings.showDemoWindow)
        ImGui::ShowDemoWindow(&AppSettings::appSettings.showDemoWindow);
}

template<typename T, typename... Args>
void GUIManager::AddWindow(Args&&... args)
{
    static_assert(std::is_base_of<GUI::BaseWindow, T>::value, "T must inherit from GUIWindow");
    windows.push_back(std::make_unique<T>(std::forward<Args>(args)...));
}

void GUIManager::DrawGUI(SP_Circuit circuit)
{
    rlImGuiBegin();
    DrawDockingSpace();

    Draw(circuit);

    rlImGuiEnd();
}

void GUIManager::Cleanup()
{
    rlImGuiShutdown();  // Clean up ImGui resources if necessary
}
