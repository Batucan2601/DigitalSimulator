#include "main.h"
#include "ComponentTextures.h"
#include "CircuitController.h"
// Create a circuit and add both gates.
std::string circuit_logger = "CircuitLogger";
//SP_Circuit circuit = std::make_shared<CircuitElements::Circuit>(circuit_logger);
std::shared_ptr<CircuitController> circuitController;
int main(void)
{
    AppSettings::appSettings.theme = AppSettings::Theme::DarkMode;

    SetTraceLogLevel(LOG_NONE);  // Disable raylib logging
    // Initialization

    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InputResolver::Init();
    RaylibHelper::Init(AppSettings::appSettings.screenWidth, AppSettings::appSettings.screenHeight, AppSettings::appSettings.targetFps,
                       "raylib [core] example - 2D camera drag with zoom");
    LogicElements::comptextures_init_logicTextures();  // this should also be wrapped
    Controls::Controls_set_camera(AppSettings::appSettings.screenWidth, AppSettings::appSettings.screenHeight);
    std::string and_gate_logger = "AndLogger1";
    std::string or_gate_logger = "OrLogger1";
    std::string not_gate_logger = "NotLogger1";
    std::string xand_gate_logger = "XandLogger1";
    std::string xor_gate_logger = "XorLogger1";
    std::string nor1_logger = "norLogger1";
    std::string nor2_logger = "norLogger2";
    std::string input1_logger = "Input1";
    std::string input2_logger = "input2";

    circuitController = std::make_shared<CircuitController>(circuit_logger);

    /*auto gate1 = LogicElements::LogicElementFactory::createGate(CircuitElements::ComponentType::AND,
                                                                and_gate_logger);
    auto gate2 =
        LogicElements::LogicElementFactory::createGate(CircuitElements::ComponentType::OR, or_gate_logger);
    auto gate3 = LogicElements::LogicElementFactory::createGate(CircuitElements::ComponentType::NOT,
                                                                not_gate_logger);
    auto gate4 = LogicElements::LogicElementFactory::createGate(CircuitElements::ComponentType::XAND,
                                                                xand_gate_logger);
    auto gate5 = LogicElements::LogicElementFactory::createGate(CircuitElements::ComponentType::XOR,
                                                                xor_gate_logger);*/
    auto in1 = LogicElements::LogicElementFactory::createInput(input1_logger);
    auto in2 = LogicElements::LogicElementFactory::createInput(input2_logger);
    
    auto gate6 = LogicElements::LogicElementFactory::createGate(CircuitElements::ComponentType::NOR,
                                                                nor1_logger);
    auto gate7 = LogicElements::LogicElementFactory::createGate(CircuitElements::ComponentType::NOR,nor2_logger);
    
    auto clk = LogicElements::LogicElementFactory::createClock(nor2_logger , 50);

    /*gate1->setPosition(0, 100 - 250);
    gate2->setPosition(0, 200 - 250);
    gate3->setPosition(0, 300 - 250);
    gate4->setPosition(0, 400 - 250);
    gate5->setPosition(0, 500 - 250);
    
    circuit->addGate(gate1);
    circuit->addGate(gate2);
    circuit->addGate(gate3);
    circuit->addGate(gate4);
    circuit->addGate(gate5);
    circuit->addGate(in1);*/
    
    in1->setPosition(0, 0);
    in2->setPosition(0, 100);

    gate6->setPosition(0, 100 - 250);
    gate7->setPosition(0, 100 - 350);

    circuitController->addComponent(gate6);
    circuitController->addComponent(gate7);
    circuitController->addComponent(in1);
    circuitController->addComponent(in2);
    circuitController->addComponent(clk);
    // Main game loop
    // GUIEditor::Init(appSettings.screenWidth, appSettings.screenHeight);
    while (!RaylibHelper::ShouldClose())  // Detect window close button or ESC key
    {
        AppSettings::appSettings.screenHeight = GetScreenHeight();
        AppSettings::appSettings.screenWidth = GetScreenWidth();
        // Update
        Controls::Controls_update(circuitController);
        circuitController->getCircuit()->evaluate();
        // Draw
        RaylibHelper::BeginFrame();
        RaylibHelper::DrawGUI(circuitController->getCircuit());
        RaylibHelper::EndFrame();
        //update each GUI object 
        RaylibHelper::Update(circuitController);
    }

    // De-Initialization
    CloseWindow();
    return 0;
}

void setLoadedCircuit(SP_Circuit loadedCircuit)
{
    circuitController->setCircuit(loadedCircuit);
}
void addComponent(std::shared_ptr<Component> c)
{
    circuitController->addComponent(c);
}