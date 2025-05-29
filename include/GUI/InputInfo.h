#pragma once 
#include "LogicElements.h"

#include <GUI/include.h>
#include <imgui.h>
#include <raylib.h>

namespace GUI
{
    class InputInfo : public BaseWindow
    {
      public:
        InputInfo() : BaseWindow("Input Info") {}
        void Draw(SP_Circuit circuit) override;
        void Update(SP_Circuit circuit) override;
        void draw_Inputs(Component* logicGate);
        void draw_Outputs(Component* logicGate);
        void change_connection_name(Component* logicGate, bool is_input, std::string newName);
        void GUITools_BasicLogicDisplay_draw(Component* logicGate);
    };

}  // namespace GUI
