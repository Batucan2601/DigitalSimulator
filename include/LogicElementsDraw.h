#ifndef LOGICELEMENTDRAW_H
#define LOGICELEMENTDRAW_H
#include "Controls.h"
#include "LogicElements.h"
#include "appSettings.h"
#include "raylib.h"
#include "CircuitController.h"
#include <common_types.h>
#include <math.h>

#define IS_DRAWING_BOUNDARY_BOX true  // TODO: this should be in userspace
namespace LogicElementsDraw
{
    void DrawCircuit(std::shared_ptr<CircuitController> circuit);
    void DrawGateElement(const std::shared_ptr<Component> gate);

    // Helper drawing functions
    void DrawBoundaryBox(const std::shared_ptr<Component> gate);
    void DrawInteractableWirePoints(Vector2 start, Vector2 end, Color color);
    void DrawInOut(std::shared_ptr<Component> gate);
}  // namespace LogicElementsDraw

#endif