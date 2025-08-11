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

        void Draw(std::shared_ptr<CircuitController> circuit) override;
        void Update(std::shared_ptr<CircuitController> circuit) override;
        void draw_Inputs(Component* logicGate);
        void draw_Outputs(Component* logicGate);
        void draw_Connection(Component* connection);

        bool change_InOut_name(Component* logicGate, const std::string& oldName, const std::string& newName);
        void GUITools_BasicLogicDisplay_draw(IInputHandler* inputHandler);
    };

}  // namespace GUI

#endif  // GUILOGICSETTING_H