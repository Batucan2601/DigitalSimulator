#include "Controls.h"
#include "raylib.h"
#include <memory>
#include "LogicElements.h"
#include <iostream>
static auto selected_circuit = std::make_shared<Circuit>();
std::vector<std::shared_ptr<LogicGate>> selected_logic_gate(1);
static Camera2D camera = {};

void Controls_set_camera(unsigned int screen_width , unsigned int screen_height  )
{
    camera.target = { 0.0f, 0.0f };                       // Camera looks at the origin initially
    camera.offset = { screen_width / 2.0f, screen_height / 2.0f }; // Offset to center the camera in the window
    camera.rotation = 0.0f;                                         // No rotation
    camera.zoom = 1.0f;                                             // Default zoom
}

void Controls_update(std::shared_ptr<Circuit> circuit)
{
    // Drag camera with the left mouse button
    if (IsMouseButtonDown(MOUSE_RIGHT_BUTTON))
    {
        // Get the mouse movement since the last frame
        Vector2 mouseDelta = GetMouseDelta();
        // Adjust the camera target (dividing by camera.zoom for consistent movement at different zoom levels)
        camera.target.x -= mouseDelta.x / camera.zoom;
        camera.target.y -= mouseDelta.y / camera.zoom;
    }

    // Zoom in/out using the mouse wheel
    float wheel = GetMouseWheelMove();
    if (wheel != 0)
    {
        camera.zoom += wheel * 0.1f;  // Adjust the zoom sensitivity as needed
        if (camera.zoom < 0.1f) camera.zoom = 0.1f; // Prevent zoom from becoming too small (or negative)
    }

    //get data
    selected_circuit = circuit;

    Controls_Mouse_click();
}
Camera2D Controls_get_camera()
{
    return camera;
}
static bool is_dragging = false; 
Vector2 offset;
void Controls_Mouse_click()
{
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
    {
        Vector2 mousePosition = GetScreenToWorld2D(GetMousePosition(), camera);  // Get mouse position
        for (size_t i = 0; i < selected_circuit->gates.size(); i++)
        {
            if (CheckCollisionPointRec(mousePosition, selected_circuit->gates[i]->bd))
            {
                selected_logic_gate[0] = selected_circuit->gates[i];
                offset.x = mousePosition.x - selected_logic_gate[0]->bd.x;
                offset.y = mousePosition.y - selected_logic_gate[0]->bd.y;
            }
        }
    }
    if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
    {
        Vector2 mousePosition = GetScreenToWorld2D(GetMousePosition(),camera );  // Get mouse position
        for (size_t i = 0; i < selected_circuit->gates.size(); i++)
        {
            if (CheckCollisionPointRec(mousePosition, selected_circuit->gates[i]->bd))
            {
                is_dragging = true; 
                selected_logic_gate[0] = selected_circuit->gates[i];
            }
        }
        if (is_dragging)
        {

            selected_logic_gate[0]->bd.x = mousePosition.x - offset.x;
            selected_logic_gate[0]->bd.y = mousePosition.y - offset.y;

            std::cout << selected_logic_gate[0]->bd.x << std::endl;
        }
    }
    if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
    {
        is_dragging = false; 
    }
}

