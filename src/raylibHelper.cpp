#include "raylibHelper.h"

#include <imgui.h>
#include <rlImGui.h>

std::shared_ptr<GUIManager> RaylibHelper::imguiManager = std::make_shared<GUIManager>();

void RaylibHelper::Init(int screenWidth, int screenHeight, int targetFps, const char* title)
{
    InitWindow(screenWidth, screenHeight, title);
    // set exit key to 'q'
    SetExitKey(KEY_Q);
    SetTargetFPS(targetFps);
    imguiManager->Init();
}

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

void RaylibHelper::DrawGUI(SP_Circuit circuit)
{
    imguiManager->DrawGUI(circuit);
}
void RaylibHelper::Update(SP_Circuit circuit)
{
    imguiManager->Update(circuit);
}
void RaylibHelper::Close()
{
    imguiManager->Cleanup();
    CloseWindow();
}
void RaylibHelper::Show(int index)
{
    imguiManager->Show(index);
}
void RaylibHelper::Hide(int index)
{
    imguiManager->Hide(index);

}