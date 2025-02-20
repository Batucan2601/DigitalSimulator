#include "raylibHelper.h"

#include "GUI/GUIMenuBar.h"
#include "GUI/GUIStyle.h"

#include <GUI/GUILogic.h>
#include <imgui.h>
#include <rlImGui.h>

void RaylibHelper::Init(int screenWidth, int screenHeight, int targetFps, const char* title)
{
    InitWindow(screenWidth, screenHeight, title);
    // set exit key to 'q'
    SetExitKey(KEY_Q);
    SetTargetFPS(targetFps);
    imguiManager.Init();
}
/* TODO combine imgui drawing
void RaylibHelper::BeginFrame()
{
// inside your game loop, between BeginDrawing() and EndDrawing()
rlImGuiBegin();			// starts the ImGui content mode. Make all ImGui calls after this

rlImGuiEnd();			// ends the ImGui content mode. Make all ImGui calls before this
}
*/
bool RaylibHelper::ShouldClose()
{
    return WindowShouldClose();
}

void RaylibHelper::BeginFrame()
{
    BeginDrawing();
    ClearBackground(RAYWHITE);
}

void RaylibHelper::EndFrame()
{
    EndDrawing();
}

void RaylibHelper::Draw2D(const Camera2D& camera, const std::function<void()>& drawFn)
{
    BeginMode2D(camera);
    drawFn();  // Execute the drawing function
    EndMode2D();
}

void RaylibHelper::DrawGUI(std::shared_ptr<CircuitElements::Circuit> circuit)
{
    imguiManager.Draw(circuit );
}
void RaylibHelper::DrawTextOverlay(const char* text, int x, int y, int fontSize, Color color)
{
    DrawText(text, x, y, fontSize, color);
}

void RaylibHelper::Close()
{
    imguiManager.Cleanup();
    CloseWindow();
}