#ifndef GUITOOLS_H
#define GUITOOLS_H
#include "LogicElements.h"

// #include <components/TreeView.h>
namespace GUITools
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

    extern GUIToolsDragDrop dragDrop;
    void GUITools_BasicLogicDisplay();
    void GUITools_Display();
}  // namespace GUITools

#endif