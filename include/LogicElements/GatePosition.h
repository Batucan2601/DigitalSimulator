#ifndef GATEPOSITION_H
#define GATEPOSITION_H

#include "raylib.h"

namespace LogicElements
{
    class GatePosition
    {
    public:
        explicit GatePosition(float x = 0, float y = 0, float width = 100, float height = 100);
        explicit GatePosition(const Rectangle &rect);

        void setPosition(float x, float y);
        Vector2 getPosition() const;

        const Rectangle &getBoundingBox() const;
        void setBoundingBoxWH(float width, float height);

    private:
        Rectangle bd; // Bounding box (x, y, width, height)
    };
}

#endif // GATEPOSITION_H
