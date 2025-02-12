#ifndef LOGICELEMENTDRAW_H
#define LOGICELEMENTDRAW_H
#include "Controls.h"
#include "LogicElements.h"

#include <math.h>

#define IS_DRAWING_BOUNDARY_BOX true // TODO this should be in userspace
namespace LogicElementsDraw
{
void DrawCircuit(const std::shared_ptr<Circuit> circuit);
void DrawAnd(const std::shared_ptr<LogicGate> gate);
void DrawOr(const std::shared_ptr<LogicGate> gate);

// Helper drawing functions
void DrawBoundaryBox(const std::shared_ptr<LogicGate> gate);
void DrawClippedCircle(float cx, float cy, float radius, Color color = BLACK);
}  // namespace LogicElementsDraw

#endif