#ifndef GUIMANAGER_H
#define GUIMANAGER_H
#include "LogicElements.h"
class GUIManager
{
public:
    static void Init();    // Initialize ImGui styles and other GUI components
    static void Draw(std::shared_ptr<CircuitElements::Circuit> circuit , RenderTexture& renderTexture );    // Draw all GUI elements, including menu bar and logic
    static void Cleanup(); // Cleanup resources if necessary

private:
    static void DrawMenuBar(); // Helper function for menu bar
    static void DrawLogic();   // Helper function for GUI logic
};

#endif // GUIMANAGER_H
