#include "GUI/GUIEditor.h"

#include <rlImGui.h>
namespace GUI
{

    void Editor::Init(int width, int height)
    {
        m_editor_render.renderTexture = LoadRenderTexture(width, height);
        visible = true;
    }

    void Editor::Draw(SP_Circuit circuit)
    {
        if (!visible)
        {
            return;
        }

        if (IsWindowResized())
        {
            // Unload the old framebuffer
            UnloadRenderTexture(m_editor_render.renderTexture);

            // Get the new window size and recreate the framebuffer accordingly
            unsigned int fbWidth = GetScreenWidth();
            unsigned int fbHeight = GetScreenHeight();
            m_editor_render.renderTexture = LoadRenderTexture(fbWidth, fbHeight);
        }
        if (ImGui::Begin("Editor", nullptr, ImGuiWindowFlags_NoScrollbar))
        {
            ImGui::Image((ImTextureID)&m_editor_render.renderTexture.texture,
                         ImVec2((float)m_editor_render.renderTexture.texture.width,
                                (float)m_editor_render.renderTexture.texture.height),
                         ImVec2(0, 1), ImVec2(1, 0));  // Adjust UVs if necessary
            // update editor
            ImVec2 windowPos = ImGui::GetWindowPos();
            ImVec2 windowSize = ImGui::GetWindowSize();
            ImVec2 imageMin =
                ImGui::GetItemRectMin();  // top-left of the drawn image in screen space
            ImVec2 imageMax = ImGui::GetItemRectMax();
            m_editor_render.window.window = {windowPos.x, windowPos.y, windowSize.x, windowSize.y};
            m_editor_render.window.borderWidth = ImGui::GetStyle().WindowBorderSize;
            m_editor_render.window.ImageMin = {imageMin.x, imageMin.y};
            m_editor_render.window.ImageMax = {imageMax.x, imageMax.y};
        }
        ImGui::End();
        BeginTextureMode(m_editor_render.renderTexture);
        ClearBackground(AppSettings::appSettings.theme == AppSettings::Theme::DarkMode ? GRAY : WHITE);

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
                                 Color color = AppSettings::appSettings.theme == AppSettings::Theme::DarkMode
                                                   ? LIGHTGRAY
                                                   : BLACK;
                                 DrawGrid2D(AppSettings::appSettings.SLICE_SIZE, AppSettings::appSettings.SPACING_SIZE,
                                            AppSettings::appSettings.GRID_POINT_SIZE, color);
                                 // You can draw additional world elements here.
                             });
        EndTextureMode();
    }
    void Editor::Update(SP_Circuit circuit)
    {
	(void)circuit;
    }
    Editor::EditorWindow Editor::getWindow()
    {
        return m_editor_render.window;
    }
}  // namespace GUI
