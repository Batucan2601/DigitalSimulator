#ifndef RAYLIBHELPER_H
#define RAYLIBHELPER_H

#include "raylib.h"

#include <functional>
#include "GUI/GUIManager.h"
#include "LogicElements.h"

class RaylibHelper
{
  public:
    static void Init(int screenWidth, int screenHeight, int targetFps, const char* title);
    static bool ShouldClose();
    static void BeginFrame();
    static void EndFrame();
    static void Draw2D(const Camera2D& camera, const std::function<void()>& drawFn);
    static void DrawGUI(std::shared_ptr<CircuitElements::Circuit> circuit, RenderTexture& renderTexture);
    static void DrawTextOverlay(const char* text, int x = 10, int y = 10, int fontSize = 20,
                                Color color = DARKGRAY);
    static void Close();
    private:
  static GUIManager imguiManager; // Manages ImGui logic

};

#endif  // RAYLIBHELPER_H