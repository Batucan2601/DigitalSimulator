#ifndef GUILOGICSETTING_H
#define GUILOGICSETTING_H
#include "LogicElements.h"

#include <GUI/include.h>
#include <imgui.h>
#include <raylib.h>

namespace GUI
{
    class LogicGateInfo : public BaseWindow
    {
      public:
        LogicGateInfo() : BaseWindow("Logic Gate Info") {}

        void Draw(SP_Circuit circuit) override;
        void Update(SP_Circuit circuit) override;
        void draw_Inputs(Component* logicGate);
        void draw_Outputs(Component* logicGate);
        bool change_InOut_name(Component* logicGate, bool is_input, const std::string& oldName, const std::string& newName);
        void GUITools_BasicLogicDisplay_draw(Component* logicGate);
    };

}  // namespace GUI

#endif  // GUILOGICSETTING_H