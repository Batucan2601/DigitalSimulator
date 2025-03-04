#include "GUI/Settings.h"

extern AppSettings::Settings appSettings;

namespace GUI
{
    void Settings::Draw(SP_Circuit circuit)
    {
        (void)circuit;
        if (!visible)
        {
            return;
        }

        ImGui::Begin(title.c_str(), &visible, ImGuiWindowFlags_NoCollapse);
        {
            ImGui::Text("General Settings:");
            ImGui::Separator();

            // Checkbox: Draw Boundary Box
            ImGui::Checkbox("Draw Boundary Box", &appSettings.isDrawingBoundaryBox);

            // Checkbox: Show Demo Window
            ImGui::Checkbox("Show Demo Window", &appSettings.showDemoWindow);

            ImGui::NewLine();
            ImGui::Text("Grid Spacing:");
            ImGui::Separator();
            int spacingOptions[] = {5, 25, 50};
            static int selectedSpacing = appSettings.SPACING_SIZE;

            for (int i = 0; i < 3; ++i)
            {
                if (ImGui::RadioButton(std::to_string(spacingOptions[i]).c_str(), &selectedSpacing,
                                       spacingOptions[i]))
                {
                    appSettings.SPACING_SIZE = spacingOptions[i];
                    appSettings.MOUSE_SELECTION_OFFSET = appSettings.SPACING_SIZE / 2;

                    // Ensure the grid remains the same size visually
                    appSettings.SLICE_SIZE =
                        (500 / appSettings.SPACING_SIZE);  // Keeping total grid area constant

                    // Adjust grid point size based on spacing
                    appSettings.GRID_POINT_SIZE = (appSettings.SPACING_SIZE == 5)    ? 1
                                                  : (appSettings.SPACING_SIZE == 25) ? 3
                                                                                     : 5;
                }
                ImGui::SameLine();
            }
            ImGui::NewLine();  // Ensure layout consistency
            ImGui::End();
        }
    }

}  // namespace GUI