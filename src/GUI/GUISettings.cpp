#include "GUI/GUISettings.h"

extern AppSettings::Settings settings;

namespace GUISettings
{
    bool isSettingsShown = false;

    void ToggleSettingsVisibility()
    {
        isSettingsShown = !isSettingsShown;
    }

    void DisplaySettings()
    {
        draw();
    }

    void draw()
    {
        if (!isSettingsShown)
        {
            return;
        }

        ImGui::Begin("Settings", &isSettingsShown, ImGuiWindowFlags_NoCollapse);
        {
            ImGui::Text("General Settings:");
            ImGui::Separator();

            // Checkbox: Draw Boundary Box
            ImGui::Checkbox("Draw Boundary Box", &settings.isDrawingBoundaryBox);

            // Checkbox: Show Demo Window
            ImGui::Checkbox("Show Demo Window", &settings.showDemoWindow);

            ImGui::NewLine();
            ImGui::Text("Grid Spacing:");
            ImGui::Separator();
            int spacingOptions[] = {5, 25, 50};
            static int selectedSpacing = settings.SPACING_SIZE;

            for (int i = 0; i < 3; ++i)
            {
                if (ImGui::RadioButton(std::to_string(spacingOptions[i]).c_str(), &selectedSpacing,
                                       spacingOptions[i]))
                {
                    settings.SPACING_SIZE = spacingOptions[i];
                    settings.MOUSE_SELECTION_OFFSET = settings.SPACING_SIZE / 2;

                    // Ensure the grid remains the same size visually
                    settings.SLICE_SIZE =
                        (500 / settings.SPACING_SIZE);  // Keeping total grid area constant

                    // Adjust grid point size based on spacing
                    settings.GRID_POINT_SIZE = (settings.SPACING_SIZE == 5)    ? 1
                                               : (settings.SPACING_SIZE == 25) ? 3
                                                                               : 5;
                }
                ImGui::SameLine();
            }
            ImGui::NewLine();  // Ensure layout consistency
            ImGui::End();
        }
    }

}  // namespace GUISettings