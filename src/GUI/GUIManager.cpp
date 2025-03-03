#include <GUI/GUIManager.h>
#include <GUI/include.h>
#include <imgui.h>
#include <rlImGui.h>

bool GUIManager::showDemoWindow = false;

void GUIManager::Init()
{
    rlImGuiSetup(true);  // Initialize ImGui
    GUIStyle::init();    // Set up custom ImGui styles
    windows.clear();     // Clear any existing windows

    GUI::Settings settings = GUI::Settings();                 // Create a settings window
    GUI::LogicGateInfo logicGateInfo = GUI::LogicGateInfo();  // Create a logic gate info window
    GUI::SaveLoad saveLoad = GUI::SaveLoad();                 // Create a save/load window
    GUI::Tools tools = GUI::Tools();                          // Create a tools window
    GUI::Editor editor = GUI::Editor();                       // Create an editor window
    editor.Init(appSettings.screenWidth, appSettings.screenHeight);

    windows.push_back(std::make_unique<GUI::Settings>(settings));
    windows.push_back(std::make_unique<GUI::LogicGateInfo>(logicGateInfo));
    windows.push_back(std::make_unique<GUI::SaveLoad>(saveLoad));
    windows.push_back(std::make_unique<GUI::Tools>(tools));
    windows.push_back(std::make_unique<GUI::Editor>(editor));

    guiMenuBar.SetWindowList(windows);
}

void GUIManager::Draw(SP_Circuit circuit)
{
    for (auto& window : windows)
    {
        window->Draw(circuit);
    }
    DrawDemoWindow();

    DrawMainMenu(circuit);
}

void GUIManager::DrawMainMenu(SP_Circuit circuit)
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
    if (appSettings.showDemoWindow)
        ImGui::ShowDemoWindow(&appSettings.showDemoWindow);
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
