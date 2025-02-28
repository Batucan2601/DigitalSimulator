#include "main.h"

// Create a circuit and add both gates.
std::string circuit_logger = "CircuitLogger";
std::shared_ptr<CircuitElements::Circuit> circuit =
    std::make_shared<CircuitElements::Circuit>(circuit_logger);

AppSettings::Settings settings;

int main(void)
{
    settings.theme = AppSettings::Theme::DarkMode;

    SetTraceLogLevel(LOG_NONE);  // Disable raylib logging
    // Initialization

    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    RaylibHelper::Init(settings.screenWidth, settings.screenHeight, settings.targetFps,
                       "raylib [core] example - 2D camera drag with zoom");
    LogicElements::init_logicTextures();  // this should also be wrapped
    Controls::Controls_set_camera(settings.screenWidth, settings.screenHeight);
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
    GUIEditor::Init(settings.screenWidth, settings.screenHeight);
    while (!RaylibHelper::ShouldClose())  // Detect window close button or ESC key
    {
        settings.screenHeight = GetScreenHeight();
        settings.screenWidth = GetScreenWidth();
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

void setLoadedCircuit(std::shared_ptr<CircuitElements::Circuit> loadedCircuit)
{
    circuit = loadedCircuit;
}