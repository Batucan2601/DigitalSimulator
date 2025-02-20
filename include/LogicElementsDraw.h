#ifndef LOGICELEMENTDRAW_H
#define LOGICELEMENTDRAW_H
#include "Controls.h"
#include "LogicElements.h"
#include "raylib.h"

#include <math.h>

#define IS_DRAWING_BOUNDARY_BOX true  // TODO: this should be in userspace
namespace LogicElementsDraw
{
    void DrawCircuit(const std::shared_ptr<CircuitElements::Circuit> circuit);
    void DrawGateElement(const std::shared_ptr<LogicElements::LogicGate> gate);

    // Helper drawing functions
    void DrawBoundaryBox(const std::shared_ptr<LogicElements::LogicGate> gate);
    void DrawInteractableWirePoints(Vector2 start, Vector2 end, Color color);
}  // namespace LogicElementsDraw

#endif