#include "Application.h"
#include "ComponentTextures.h"
#include <imgui.h>
#include <rlImGui.h>
#include "logicElementFactory.h"

std::shared_ptr<CircuitController> Application::circuitController = nullptr;
std::shared_ptr<GUIManager> Application::imguiManager = std::make_shared<GUIManager>();

void Application::Init(int screenWidth, int screenHeight, int targetFps, const char* title)
{
    AppSettings::appSettings.theme = AppSettings::Theme::DarkMode;
    SetTraceLogLevel(LOG_NONE); // Disable raylib logging
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InputResolver::Init();

    std::string circuit_logger = "CircuitLogger";
    Application::circuitController = CircuitController::getInstance(circuit_logger);
    InitWindow(screenWidth, screenHeight, title);
    // set exit key to 'q'
    SetExitKey(KEY_Q);
    SetTargetFPS(targetFps);
    imguiManager->Init();
    LogicElements::comptextures_init_logicTextures(); // this should also be
    Controls::Controls_set_camera(AppSettings::appSettings.screenWidth,
                                AppSettings::appSettings.screenHeight);
    SampleCircuit();
    

}

bool Application::ShouldClose()
{
    return WindowShouldClose();
}

void Application::BeginFrame()
{
    BeginDrawing();
    ClearBackground(RAYWHITE);
}

void Application::EndFrame()
{
    EndDrawing();
}

void Application::Draw2D(const Camera2D& camera, const std::function<void()>& drawFn)
{
    BeginMode2D(camera);
    drawFn();  // Execute the drawing function
    EndMode2D();
}

void Application::DrawGUI(std::shared_ptr<CircuitController> circuitController)
{
    imguiManager->DrawGUI(circuitController);
}
void Application::Update(std::shared_ptr<CircuitController> circuitController)
{
    imguiManager->Update(circuitController);
}
void Application::Close()
{
    imguiManager->Cleanup();
    CloseWindow();
}
void Application::Show(GUIWindowType index)
{
    imguiManager->Show(index);
}
void Application::Hide(GUIWindowType index)
{
    imguiManager->Hide(index);

}

void Application::Run()
{
    while (!Application::ShouldClose()) // Detect window close button or ESC key
    {
        AppSettings::appSettings.screenHeight = GetScreenHeight();
        AppSettings::appSettings.screenWidth = GetScreenWidth();
        // Update
        //Controls::Controls_update(circuitController);
        circuitController->getCircuit()->evaluate();
        // Draw
        Application::BeginFrame();
        Application::DrawGUI(circuitController);
        Application::EndFrame();
        // update each GUI object
        Application::Update(circuitController);
    }
    CloseWindow();
}


void Application::SampleCircuit()
{
      std::string and_gate_logger = "AndLogger1";
  std::string or_gate_logger = "OrLogger1";
  std::string not_gate_logger = "NotLogger1";
  std::string xand_gate_logger = "XandLogger1";
  std::string xor_gate_logger = "XorLogger1";
  std::string nor1_logger = "norLogger1";
  std::string nor2_logger = "norLogger2";
  std::string input1_logger = "Input1";
  std::string input2_logger = "input2";


  auto in1 = LogicElements::LogicElementFactory::createInput(input1_logger);
  auto in2 = LogicElements::LogicElementFactory::createInput(input2_logger);

  auto gate6 = LogicElements::LogicElementFactory::createGate(
      CircuitElements::ComponentType::NOR, nor1_logger);
  auto gate7 = LogicElements::LogicElementFactory::createGate(
      CircuitElements::ComponentType::NOR, nor2_logger);

  auto clk = LogicElements::LogicElementFactory::createClock(nor2_logger, 50);

  in1->setPosition(0, 0);
  in2->setPosition(0, 100);

  gate6->setPosition(0, 100 - 250);
  gate7->setPosition(0, 100 - 350);
  clk->setPosition(100 , 100);
  circuitController->addComponent(gate6);
  circuitController->addComponent(gate7);
  circuitController->addComponent(in1);
  circuitController->addComponent(in2);
  circuitController->addComponent(clk);
}
