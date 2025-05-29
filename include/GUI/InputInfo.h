/*#pragma once 
#include "LogicElements.h"

#include <GUI/include.h>
#include <imgui.h>
#include <raylib.h>
#include "InputElement.h"
namespace GUI
{
    class InputInfo : public BaseWindow
    {
      public:
        InputInfo() : BaseWindow("Input Info") {}
        void Draw(SP_Circuit circuit) override;
        void Update(SP_Circuit circuit) override;
        void draw_Inputs(InputElement* logicGate);
        void draw_Outputs(InputElement* logicGate);
        void change_connection_name(InputElement* logicGate, bool is_input, std::string newName);
        void GUITools_BasicLogicDisplay_draw(InputElement* logicGate);
    };

}  // namespace GUI */
