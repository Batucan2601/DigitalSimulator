#include "Controls.h"
#include "LogicElements.h"
#include "LogicElementsDraw.h"
#include "common_types.h"
#include "raylib.h"
#include "raylibHelper.h"

int main(void)
{
    // Initialization
    const unsigned int screenWidth = 600;
    const unsigned int screenHeight = 600;
    const unsigned int targetFps = 60;
    RaylibHelper::Init(screenWidth, screenHeight, targetFps,
                       "raylib [core] example - 2D camera drag with zoom");
    Controls::Controls_set_camera(screenWidth, screenHeight);
    auto gate1 = std::make_shared<AndGate>();
    auto gate2 = std::make_shared<AndGate>();
    auto gate3 = std::make_shared<OrGate>();

    // Set initial inputs for gate1.
    gate1->setInput("A", true);
    gate1->setInput("B", true);

    // Set an initial input for gate2 that is independent.
    gate2->setInput("B", false);

    gate3->setInput("A", true);
    gate3->setInput("B", false);
    // Create a circuit and add both gates.
    auto circuit = std::make_shared<Circuit>();
    gate1->setPosition(100, 100);
    gate3->setPosition(-100, -100);
    circuit->addGate(gate1);
    // circuit->addGate(gate2);
    circuit->addGate(gate3);
    // Main game loop
    while (!RaylibHelper::ShouldClose())  // Detect window close button or ESC key
    {
        // Update
        Controls::Controls_update(circuit);

        // Draw
        RaylibHelper::BeginFrame();
        // Activate the camera's 2D mode so that all drawing inside is affected by the camera
        RaylibHelper::Draw2D(Controls::Controls_get_camera(),
                             [&circuit]()
                             {
                                 LogicElementsDraw::DrawCircuit(circuit);
                                 // You can draw additional world elements here.
                             });
        RaylibHelper::Draw2D(Controls::Controls_get_camera(),
                             []()
                             {
                                 // Draw a grid to visualize the 2D world.
                                 DrawGrid2D(SLICE_SIZE, SPACING_SIZE, GRID_POINT_SIZE);
                                 // You can draw additional world elements here.
                             });
        // Draw UI elements that remain in screen space
        RaylibHelper::DrawTextOverlay("Drag with the left mouse button and scroll to zoom");
        RaylibHelper::DrawTextOverlay("Use the keyboard arrows after selecting a gate to move it",
                                      10, 30, 20, RED);

        RaylibHelper::EndFrame();
    }

    // De-Initialization
    CloseWindow();
    return 0;
}
