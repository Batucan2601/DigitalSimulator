#ifndef LOGICELEMENTDRAW_H
#define LOGICELEMENTDRAW_H
#include "Controls.h"
#include "LogicElements.h"

namespace LogicElementsDraw
{
void DrawCircuit(const std::shared_ptr<Circuit> circuit);
void DrawAnd(const std::shared_ptr<LogicGate> gate);
void DrawOr(const std::shared_ptr<LogicGate> gate);
}  // namespace LogicElementsDraw

#endif