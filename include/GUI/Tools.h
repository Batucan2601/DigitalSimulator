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
        CircuitElements::ComponentType componentType;
    };

    class Tools : public BaseWindow
    {
      public:
        Tools() : BaseWindow("Tools") {}

        void Draw(SP_Circuit circuit) override;
        void Update(std::shared_ptr<CircuitController> circuit) override;
        void RenderGateButton(const std::string& gateName, CircuitElements::ComponentInfo gateInfo);

    };

    extern GUIToolsDragDrop dragDrop;

}  // namespace GUI

#endif