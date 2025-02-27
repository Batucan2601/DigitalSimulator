#include "GUI/GUIEditor.h"

#include <rlImGui.h>
namespace GUIEditor
{

    struct Editor
    {
        RenderTexture renderTexture;
        EditorWindow window;
    };

    static Editor editor;
    void Init(int width, int height)
    {
        editor.renderTexture = LoadRenderTexture(width, height);
    }

    void Draw() {}

    void RenderScene(std::shared_ptr<CircuitElements::Circuit> circuit)
    {
        if (IsWindowResized())
        {
            // Unload the old framebuffer
            UnloadRenderTexture(editor.renderTexture);

            // Get the new window size and recreate the framebuffer accordingly
            unsigned int fbWidth = GetScreenWidth();
            unsigned int fbHeight = GetScreenHeight();
            editor.renderTexture = LoadRenderTexture(fbWidth, fbHeight);
        }
        if (ImGui::Begin("Editor", nullptr, ImGuiWindowFlags_NoScrollbar))
        {
            ImGui::Image((ImTextureID)&editor.renderTexture.texture,
                         ImVec2((float)editor.renderTexture.texture.width,
                                (float)editor.renderTexture.texture.height),
                         ImVec2(0, 1), ImVec2(1, 0));  // Adjust UVs if necessary
            // update editor
            ImVec2 windowPos = ImGui::GetWindowPos();
            ImVec2 windowSize = ImGui::GetWindowSize();
            ImVec2 imageMin =
                ImGui::GetItemRectMin();  // top-left of the drawn image in screen space
            ImVec2 imageMax = ImGui::GetItemRectMax();
            editor.window.window = {windowPos.x, windowPos.y, windowSize.x, windowSize.y};
            editor.window.borderWidth = ImGui::GetStyle().WindowBorderSize;
            editor.window.ImageMin = {imageMin.x, imageMin.y};
            editor.window.ImageMax = {imageMax.x, imageMax.y};
        }
        ImGui::End();
        BeginTextureMode(editor.renderTexture);
        ClearBackground(settings.theme == AppSettings::Theme::DarkMode ? WHITE : GRAY);

        // Activate the camera's 2D mode so that all drawing inside is affected by the camera
        RaylibHelper::Draw2D(Controls::Controls_get_camera(),
                             [circuit]()
                             {
                                 LogicElementsDraw::DrawCircuit(circuit);
                                 // You can draw additional world elements here.
                             });
        RaylibHelper::Draw2D(Controls::Controls_get_camera(),
                             []()
                             {
                                 // Draw a grid to visualize the 2D world.
                                 Color color = settings.theme == AppSettings::Theme::DarkMode
                                                   ? LIGHTGRAY
                                                   : WHITE;
                                 DrawGrid2D(SLICE_SIZE, SPACING_SIZE, GRID_POINT_SIZE, color);
                                 // You can draw additional world elements here.
                             });
        EndTextureMode();
    }

    EditorWindow Window()
    {
        return editor.window;
    }
}  // namespace GUIEditor