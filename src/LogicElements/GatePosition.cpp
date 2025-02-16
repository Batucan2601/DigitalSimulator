#include "GatePosition.h"

namespace LogicElements
{
    GatePosition::GatePosition(float x, float y, float width, float height)
        : bd{x, y, width, height}
    {
    }

    GatePosition::GatePosition(const Rectangle &rect)
        : bd(rect)
    {
    }

    void GatePosition::setPosition(float x, float y)
    {
        bd.x = x;
        bd.y = y;
    }

    Vector2 GatePosition::getPosition() const
    {
        return {bd.x, bd.y};
    }

    const Rectangle &GatePosition::getBoundingBox() const
    {
        return bd;
    }

    void GatePosition::setBoundingBoxWH(float width, float height)
    {
        bd.width = width;
        bd.height = height;
    }
}
