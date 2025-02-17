#include "GUI/GUITools.h"
#include <imgui.h>
#include <raylib.h>

// Global or static variables for the UI state and texture.
bool is_BLD_shown = false; // Basic Logic Display flag.
static Texture image = { 0 };  // Initialize to zero.
static bool textureLoaded = false;

// UI state variables (persistent across frames).
static bool enableFeature = false;
static float parameter = 0.0f;

static void GUITools_BasicLogicDisplay_draw();

void GUITools_BasicLogicDisplay()
{
    // Load the texture only once.
    if (!textureLoaded)
    {
        image = LoadTexture("D:/DigitalSimulator/assets/gates/test_and.png");
        if (image.id != 0) textureLoaded = true;
    }
    is_BLD_shown = true;
}

void GUITools_Display()
{
    GUITools_BasicLogicDisplay_draw();
}

static void GUITools_BasicLogicDisplay_draw()
{
    if (!is_BLD_shown)
    {
        return;
    }

    ImGui::Begin("Basic Logics", &is_BLD_shown);
    if (ImGui::CollapsingHeader("Basic Gates"))
    {
        // Use persistent state for the checkbox and slider.
        ImGui::Checkbox("Enable Feature", &enableFeature);
        ImGui::SliderFloat("Parameter", &parameter, 0.0f, 1.0f);

        // Make sure the texture is loaded before using it.
        if (textureLoaded)
        {
            // Properly cast the texture ID for ImGui.
            ImTextureID myTexture = (ImTextureID)(intptr_t)image.id;

            if (ImGui::Button("AND Gate"))
            {
                // Button action.
            }

            // Begin the drag source from the image.
            if (ImGui::BeginDragDropSource())
            {
                ImGui::SetDragDropPayload("IMAGE_DRAG", nullptr, 0);

                // Show the image as a preview while dragging.
                ImGui::Image((ImTextureID)&image, ImVec2((float)image.width, (float)image.height));
                ImGui::Text("Dragging Image");

                ImGui::EndDragDropSource();
            }

            // Drop target: This area will accept the dragged item.
            ImGui::Text("Drop Here to create something:");
            ImGui::BeginChild("DropArea", ImVec2(200, 100), true);
            {
                if (ImGui::BeginDragDropTarget())
                {
                    if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("IMAGE_DRAG"))
                    {
                        // React to the drop: create a new element.
                        ImGui::Text("Dragging 'Drag Me'");
                    }
                    ImGui::EndDragDropTarget();
                }
            }
            ImGui::EndChild();
        }
        else
        {
            ImGui::Text("Texture not loaded.");
        }
    }
    ImGui::End();
}
