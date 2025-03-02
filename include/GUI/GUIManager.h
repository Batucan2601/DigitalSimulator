#ifndef GUIMANAGER_H
#define GUIMANAGER_H

#include "GUI/BaseWindow.h"
#include "LogicElements.h"
class GUIManager
{
  public:
    void Init();                    // Initialize ImGui styles and other GUI components
    void Draw(SP_Circuit circuit);  // Draw all GUI elements, including menu bar and logic
    void Cleanup();                 // Cleanup resources if necessary

    template<typename T, typename... Args>
    void AddWindow(Args&&... args);  // Add a new window to the GUI

    void Draw2(SP_Circuit);

    void DrawGUI(SP_Circuit circuit);

    std::vector<std::unique_ptr<GUI::BaseWindow>> windows;

  private:
    void DrawDemoWindow();
    void DrawDockingSpace();                // Draw the parent screen for the dockspace
    void DrawMainMenu(SP_Circuit circuit);  // Calls GUIMenuBar
    void DrawEditor(SP_Circuit circuit);    // Calls GUIEditor

  private:
    static bool showDemoWindow;
};

#endif  // GUIMANAGER_H
