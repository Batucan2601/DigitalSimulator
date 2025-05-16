#ifndef UTILS_H
#define UTILS_H
#include "LogicElements.h"
#include "common_types.h"
namespace Utils
{ 
    bool CheckNearWire(SP_Circuit circuit, const Vector2& mousePosition,
                       CircuitElements::Connection& con);
    Vector2 SnapToNearestGrid(const Rectangle& rect);

}

#endif