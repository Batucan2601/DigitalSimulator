#include "GUI/Settings.h"

namespace GUI
{
    void Settings::Draw(std::shared_ptr<CircuitController> circuitController )
    {
        (void)circuitController;
        if (!visible)
        {
            return;
        }

        ImGui::Begin(title.c_str(), &visible, ImGuiWindowFlags_NoCollapse);
        {
            ImGui::Text("General Settings:");
            ImGui::Separator();

            // Checkbox: Draw Boundary Box
            ImGui::Checkbox("Draw Boundary Box", &AppSettings::appSettings.isDrawingBoundaryBox);

            // Checkbox: Show Demo Window
            ImGui::Checkbox("Show Demo Window", &AppSettings::appSettings.showDemoWindow);

            ImGui::NewLine();
            ImGui::Text("Grid Spacing:");
            ImGui::Separator();
            int spacingOptions[] = {5, 25, 50};
            static int selectedSpacing = AppSettings::appSettings.SPACING_SIZE;

            for (int i = 0; i < 3; ++i)
            {
                if (ImGui::RadioButton(std::to_string(spacingOptions[i]).c_str(), &selectedSpacing,
                                       spacingOptions[i]))
                {
                    AppSettings::appSettings.SPACING_SIZE = spacingOptions[i];
                    AppSettings::appSettings.MOUSE_SELECTION_OFFSET = AppSettings::appSettings.SPACING_SIZE / 2;

                    // Ensure the grid remains the same size visually
                    AppSettings::appSettings.SLICE_SIZE =
                        (500 / AppSettings::appSettings.SPACING_SIZE);  // Keeping total grid area constant

                    // Adjust grid point size based on spacing
                    AppSettings::appSettings.GRID_POINT_SIZE = (AppSettings::appSettings.SPACING_SIZE == 5)    ? 1
                                                  : (AppSettings::appSettings.SPACING_SIZE == 25) ? 3
                                                                                     : 5;
                }
                ImGui::SameLine();
            }
            ImGui::NewLine();  // Ensure layout consistency
            ImGui::End();
        }
    }

    void Settings::Update(std::shared_ptr<CircuitController> circuit)  
    {
        (void)circuit;
    }

}  // namespace GUI