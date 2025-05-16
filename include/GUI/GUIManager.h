#ifndef GUIMANAGER_H
#define GUIMANAGER_H

#include "GUI/BaseWindow.h"
#include "LogicElements.h"
class GUIManager
{
  public:
    void Init();                    // Initialize ImGui styles and other GUI components
    void Draw(SP_Circuit circuit);  // Draw all GUI elements, including menu bar and logic
    void Update(SP_Circuit circuit); // Update all GUI elements.

    void Cleanup();                 // Cleanup resources if necessary

    void DrawGUI(SP_Circuit circuit);

    std::vector<std::unique_ptr<GUI::BaseWindow>> windows;

  private:
    void DrawDemoWindow();
    void DrawDockingSpace();  // Draw the parent screen for the dockspace

  private:
    template<typename T, typename... Args>
    void AddWindow(Args&&... args);  // Add a new window to the GUI
};

#endif  // GUIMANAGER_H
