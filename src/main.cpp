#include "Application.h"
int main(void) {

  Application::Init(AppSettings::appSettings.screenWidth,
                     AppSettings::appSettings.screenHeight,
                     AppSettings::appSettings.targetFps,
                     "Digital Simulatior");
  Application::Run();
  return 0;
}


