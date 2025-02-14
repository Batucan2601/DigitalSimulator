#include "raylibHelper.h"
#include <rlImGui.h>
#include <imgui.h>

void RaylibHelper::Init(int screenWidth, int screenHeight, int targetFps, const char* title)
{
    InitWindow(screenWidth, screenHeight, title);
    SetTargetFPS(targetFps);
    rlImGuiSetup(true); 	// sets up ImGui with ether a dark or light default theme

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
    
    // this should be removed
    rlImGuiBegin();
    ImGui::Begin("win1");
    float d;
	ImGui::InputFloat("test", &d);
    ImGui::End();

    ImGui::Begin("win2");
	ImGui::InputFloat("test", &d);
    ImGui::End();
    rlImGuiEnd();
}

void RaylibHelper::DrawTextOverlay(const char* text, int x, int y, int fontSize, Color color)
{
    DrawText(text, x, y, fontSize, color);
}

void RaylibHelper::Close()
{
    CloseWindow();
}