#include "raylib.h"
#include "Controls.h"
#include "LogicElements.h"
#include "LogicElementsDraw.h"


int main(void)
{
    // Initialization
    const unsigned int screenWidth = 800;
    const unsigned int  screenHeight = 450;
    InitWindow(screenWidth, screenHeight, "raylib [core] example - 2D camera drag with zoom");
    Controls_set_camera(screenWidth, screenHeight);
    auto gate1 = std::make_shared<AndGate>();
    auto gate2 = std::make_shared<AndGate>();

    // Set initial inputs for gate1.
    gate1->setInput("A", true);
    gate1->setInput("B", true);

    // Set an initial input for gate2 that is independent.
    gate2->setInput("B", false);
    gate2->bd = { 20,20, 50,50 };
    // Create a circuit and add both gates.
    auto circuit = std::make_shared<Circuit>();
    circuit->addGate(gate1);
    circuit->addGate(gate2);
    SetTargetFPS(60);  // Set desired FPS
    
    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        Controls_update(circuit);

        // Draw
        BeginDrawing();
        ClearBackground(RAYWHITE);

        // Activate the camera's 2D mode so that all drawing inside is affected by the camera transform.
        BeginMode2D(Controls_get_camera());

        DrawCircuit(circuit);
        // Draw a grid to visualize the 2D world.
        DrawGrid(20, 50.0f);
        // You can draw additional world elements here.
        EndMode2D();

        // Draw UI elements that remain in screen space
        DrawText("Drag with the left mouse button and scroll to zoom", 10, 10, 20, DARKGRAY);
        EndDrawing();
    }

    // De-Initialization
    CloseWindow();
    return 0;
}
