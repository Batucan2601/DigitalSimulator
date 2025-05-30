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
            STATE_LOAD
        };

        SaveLoad() : BaseWindow("Save/Load") {}

        void Draw(SP_Circuit circuit) override;
        void Update(SP_Circuit circuit) override;
        void RenderSaveButton(const std::string& gateName, CircuitElements::ComponentInfo gateInfo);
        void RenderLoadButton(const std::string& gateName, CircuitElements::ComponentInfo gateInfo);

        void ShowSaveWindow(SP_Circuit globalCircuit);
        void ShowLoadWindow();

        void drawSaveWindow();
        void drawLoadWindow();
        bool saveCircuit(std::string name);
        bool loadCircuit(std::string name);

        State state = State::STATE_IDLE;
    };

}  // namespace GUI
#endif