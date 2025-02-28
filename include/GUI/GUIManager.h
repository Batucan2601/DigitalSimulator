#ifndef GUIMANAGER_H
#define GUIMANAGER_H
#include "LogicElements.h"
class GUIManager
{
  public:
    static void Init();  // Initialize ImGui styles and other GUI components
    static void Draw(std::shared_ptr<CircuitElements::Circuit>
                         circuit);  // Draw all GUI elements, including menu bar and logic
    static void Cleanup();          // Cleanup resources if necessary

  private:
    static void DrawDemoWindow();
    static void DrawDockingSpace();  // Draw the parent screen for the dockspace
    static void
        DrawMainMenu(std::shared_ptr<CircuitElements::Circuit> circuit);        // Calls GUIMenuBar
    static void DrawEditor(std::shared_ptr<CircuitElements::Circuit> circuit);  // Calls GUIEditor
    static void DrawSaveDialog();  // Calls GUISaveSystem
    static void DrawTools();       // Calls GUITools
    static void DrawSettings();

  private:
    static bool showDemoWindow;
};

#endif  // GUIMANAGER_H
