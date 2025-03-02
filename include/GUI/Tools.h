#ifndef GUITOOLS_H
#define GUITOOLS_H
#include "LogicElements.h"

#include <GUI/include.h>
// #include <components/TreeView.h>
namespace GUI
{

    enum class DragDropState
    {
        DRAGGING,
        DROPPED,
        IDLE,
    };
    struct GUIToolsDragDrop
    {
        DragDropState state;
        LogicElements::GateType gateType;
    };

    class Tools : public BaseWindow
    {
      public:
        Tools() : BaseWindow("Tools") {}

        void Draw(SP_Circuit circuit) override;
        void RenderGateButton(const std::string& gateName, LogicElements::GateInfo gateInfo);
    };

    extern GUIToolsDragDrop dragDrop;

}  // namespace GUI

#endif