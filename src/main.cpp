#include "main.h"

// Create a circuit and add both gates.
std::string circuit_logger = "CircuitLogger";
SP_Circuit circuit = std::make_shared<CircuitElements::Circuit>(circuit_logger);

AppSettings::Settings appSettings;

int main(void)
{
    appSettings.theme = AppSettings::Theme::DarkMode;

    SetTraceLogLevel(LOG_NONE);  // Disable raylib logging
    // Initialization

    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    RaylibHelper::Init(appSettings.screenWidth, appSettings.screenHeight, appSettings.targetFps,
                       "raylib [core] example - 2D camera drag with zoom");
    LogicElements::init_logicTextures();  // this should also be wrapped
    Controls::Controls_set_camera(appSettings.screenWidth, appSettings.screenHeight);
    std::string and_gate_logger = "AndLogger1";
    std::string or_gate_logger = "OrLogger1";
    std::string not_gate_logger = "NotLogger1";
    std::string xand_gate_logger = "XandLogger1";
    std::string xor_gate_logger = "XorLogger1";
    
    auto gate1 = circuit->factory.createGate(LogicElements::GateType::AND,
                                                                and_gate_logger);
    auto gate2 =
        circuit->factory.createGate(LogicElements::GateType::OR, or_gate_logger);
    auto gate3 = circuit->factory.createGate(LogicElements::GateType::NOT,
                                                                not_gate_logger);
    auto gate4 = circuit->factory.createGate(LogicElements::GateType::XAND,
                                                                xand_gate_logger);
    auto gate5 = circuit->factory.createGate(LogicElements::GateType::XOR,
                                                                xor_gate_logger);

    gate1.setPosition(0, 100 - 250);
    gate2.setPosition(0, 200 - 250);
    gate3.setPosition(0, 300 - 250);
    gate4.setPosition(0, 400 - 250);
    gate5.setPosition(0, 500 - 250);

    Component mainC; 
    mainC.allocateConnection();
    mainC.addComponent(gate1);
    mainC.addComponent(gate2);
    mainC.addComponent(gate3);
    mainC.addComponent(gate4);
    mainC.addComponent(gate5);

    circuit->addComponent(mainC);
    // Main game loop
    // GUIEditor::Init(appSettings.screenWidth, appSettings.screenHeight);
    while (!RaylibHelper::ShouldClose())  // Detect window close button or ESC key
    {
        appSettings.screenHeight = GetScreenHeight();
        appSettings.screenWidth = GetScreenWidth();
        // Update
        Controls::Controls_update(circuit);
        circuit->evaluate();
        // Draw
        RaylibHelper::BeginFrame();
        RaylibHelper::DrawGUI(circuit);
        RaylibHelper::EndFrame();
    }

    // De-Initialization
    CloseWindow();
    return 0;
}

void setLoadedCircuit(SP_Circuit loadedCircuit)
{
    circuit = loadedCircuit;
}