#ifndef GUISAVESYSTEM_H
#define GUISAVESYSTEM_H
#include "ImGuiFileDialog.h"
#include "JsonSerializer.h"
#include "LogicElements.h"
#include "logicElementFactory.h"

#include <filesystem>
#include <string>

#ifndef PROJECT_ROOT_DIR
#define PROJECT_ROOT_DIR "/path/to/project/root"  // Replace with the actual project root directory
#endif

namespace GUISaveSystem
{
    enum class State
    {  // sorting for filetering of the file lsit
        STATE_IDLE,
        STATE_SAVE,
        STATE_LOAD
    };

    extern State state;
    void ShowSaveWindow(std::shared_ptr<CircuitElements::Circuit> globalCircuit);
    void ShowLoadWindow(std::shared_ptr<CircuitElements::Circuit> globalCircuit);

    void draw();
    void drawSaveWindow();
    void drawLoadWindow();
    bool saveCircuit(std::string name);
    bool loadCircuit(std::string name);
}  // namespace GUISaveSystem
#endif