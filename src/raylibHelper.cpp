#include "raylibHelper.h"

void RaylibHelper::Init(int screenWidth, int screenHeight, int targetFps, const char* title)
{
    InitWindow(screenWidth, screenHeight, title);
    SetTargetFPS(targetFps);
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

void RaylibHelper::DrawTextOverlay(const char* text, int x, int y, int fontSize, Color color)
{
    DrawText(text, x, y, fontSize, color);
}

void RaylibHelper::Close()
{
    CloseWindow();
}