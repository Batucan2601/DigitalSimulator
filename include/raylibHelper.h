#ifndef RAYLIBHELPER_H
#define RAYLIBHELPER_H

#include "GUI/GUIManager.h"
#include "LogicElements.h"
#include "raylib.h"

#include <common_types.h>
#include <functional>

class RaylibHelper
{
  public:
    static void Init(int screenWidth, int screenHeight, int targetFps, const char* title);
    static bool ShouldClose();
    static void BeginFrame();
    static void EndFrame();
    static void Draw2D(const Camera2D& camera, const std::function<void()>& drawFn);
    static void DrawGUI(SP_Circuit circuit);
    static void Update(SP_Circuit circuit);
    static void Show(int index);
    static void Hide(int index);


    static void Close();

    static GUI::BaseWindow* getGUIWindow(const std::string& title)
    {
        for (auto& window : imguiManager->windows)
        {
            if (window->GetTitle() == title)
            {
                return window.get();
            }
        }
        return nullptr;
    }

  private:
    static std::shared_ptr<GUIManager> imguiManager;  // Manages ImGui logic
};

#endif  // RAYLIBHELPER_H