#include "Controls.h"
#include "LogicElements.h"
#include "LogicElementsDraw.h"
#include "common_types.h"
#include "logicElementFactory.h"
#include "raylib.h"
#include "raylibHelper.h"
#include "GUI/GUIEditor.h"

int main(void)
{
    SetTraceLogLevel(LOG_NONE);  // Disable raylib logging
    // Initialization
    const unsigned int screenWidth = 600;
    const unsigned int screenHeight = 600;
    const unsigned int targetFps = 60;
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    RaylibHelper::Init(screenWidth, screenHeight, targetFps,
                       "raylib [core] example - 2D camera drag with zoom");
    LogicElements::init_logicTextures();  // this should also be wrapped
    Controls::Controls_set_camera(screenWidth, screenHeight);
    std::string and_gate_logger = "AndLogger1";
    std::string or_gate_logger = "OrLogger1";
    std::string not_gate_logger = "NotLogger1";
    std::string xand_gate_logger = "XandLogger1";
    std::string xor_gate_logger = "XorLogger1";
    auto gate1 = LogicElements::LogicElementFactory::createGate(LogicElements::GateType::AND,
                                                                and_gate_logger);
    auto gate2 =
        LogicElements::LogicElementFactory::createGate(LogicElements::GateType::OR, or_gate_logger);
    auto gate3 = LogicElements::LogicElementFactory::createGate(LogicElements::GateType::NOT,
                                                                not_gate_logger);
    auto gate4 = LogicElements::LogicElementFactory::createGate(LogicElements::GateType::XAND,
                                                                xand_gate_logger);
    auto gate5 = LogicElements::LogicElementFactory::createGate(LogicElements::GateType::XOR,
                                                                xor_gate_logger);

    // Create a circuit and add both gates.
    std::string circuit_logger = "CircuitLogger";
    auto circuit = std::make_shared<CircuitElements::Circuit>(circuit_logger);
    gate1->setPosition(0, 100 - 250);
    gate2->setPosition(0, 200 - 250);
    gate3->setPosition(0, 300 - 250);
    gate4->setPosition(0, 400 - 250);
    gate5->setPosition(0, 500 - 250);

    circuit->addGate(gate1);
    circuit->addGate(gate2);
    circuit->addGate(gate3);
    circuit->addGate(gate4);
    circuit->addGate(gate5);
    // Main game loop
    GUIEditor::Init(screenWidth, screenHeight);
    while (!RaylibHelper::ShouldClose())  // Detect window close button or ESC key
    {
        // Update
        Controls::Controls_update(circuit);
        InputResolver::resolve();
        // Draw
        RaylibHelper::BeginFrame();
        // Activate the camera's 2D mode so that all drawing inside is affected by the camera
        circuit->evaluate();
        GUIEditor::BeginOffscreenDraw();
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
        GUIEditor::EndOffscreenDraw();
        RaylibHelper::DrawGUI(circuit);
        RaylibHelper::EndFrame();
    }

    // De-Initialization
    CloseWindow();
    return 0;
}
