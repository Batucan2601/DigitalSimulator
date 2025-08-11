#ifndef GUISAVESYSTEM_H
#define GUISAVESYSTEM_H
#include "ImGuiFileDialog.h"
#include "JsonSerializer.h"
#include "LogicElements.h"
#include "logicElementFactory.h"

#include <GUI/include.h>
#include <common_types.h>
#include <filesystem>
#include <string>
#ifndef PROJECT_ROOT_DIR
#define PROJECT_ROOT_DIR "/path/to/project/root"  // Replace with the actual project root directory
#endif

namespace GUI
{
    class SaveLoad : public BaseWindow
    {
      public:
        enum class State
        {  // sorting for filetering of the file lsit
            STATE_IDLE,
            STATE_SAVE,
            STATE_LOAD,
            STATE_LOADSUBCIRCUIT,
        };

        SaveLoad() : BaseWindow("Save/Load") {}

        void Draw(std::shared_ptr<CircuitController> circuit) override;
        void Update(std::shared_ptr<CircuitController> circuit) override;
        void RenderSaveButton(const std::string& gateName, CircuitElements::ComponentInfo gateInfo);
        void RenderLoadButton(const std::string& gateName, CircuitElements::ComponentInfo gateInfo);

        void ShowSaveWindow();
        void ShowLoadWindow();
        void ShowLoadSubCircuitWindow();
        
        void drawSubcircuitWindow(SP_Circuit circuit);
        void drawSaveWindow(SP_Circuit circuit);
        void drawLoadWindow(SP_Circuit circuit);
        
        bool saveCircuit(std::string name);
        bool loadCircuit(std::string name);
        bool loadSubCircuit(std::string fileName);

        State state = State::STATE_IDLE;
    };

}  // namespace GUI
#endif