#include "LogicElementsDraw.h"

#include <iostream>
namespace LogicElementsDraw
{

void DrawAnd(const std::shared_ptr<LogicGate> gate)
{
    Rectangle bd = gate->bd;
    float width = bd.width;
    float height = bd.height;

    // Normalize the bounding box (bd.x, bd.y is the origin of the rectangle)
    auto NormalizeX = [&](float x)
    {
        return bd.x + x * width;
    };
    auto NormalizeY = [&](float y)
    {
        return bd.y + y * height;
    };
    float leftMarginLowerX = 0.05f;
    float leftMarginUpperX = 0.15f;
    float botLeftLineY = 0.25f;
    float topLeftLineY = 0.75f;

    float topMarginUpperX = 0.5f;
    float topMarginLowerX = 0.15f;
    float topMarginY = 0.85f;
    float botMarginY = 0.15f;

    float rightMarginLowerX = 0.85f;
    float rightMarginUpperX = 0.95f;
    float topRightMarginY = 0.5f;

    // Line 1: y = 0.35 {0.05 < x < 0.25}
    // Bot Input Line
    DrawLine(NormalizeX(leftMarginLowerX), NormalizeY(botLeftLineY), NormalizeX(leftMarginUpperX),
             NormalizeY(botLeftLineY), BLACK);

    // Line 2: y = 0.65 {0.05 < x < 0.25}
    // Top Input Line
    DrawLine(NormalizeX(leftMarginLowerX), NormalizeY(topLeftLineY), NormalizeX(leftMarginUpperX),
             NormalizeY(topLeftLineY), BLACK);

    // Line 3: x = 0.25 {0.15 < y < 0.85}
    DrawLine(NormalizeX(leftMarginUpperX), NormalizeY(botMarginY), NormalizeX(leftMarginUpperX),
             NormalizeY(topMarginY), BLACK);

    // Line 4: y = 0.15 {0.25 < x < 0.6}
    DrawLine(NormalizeX(topMarginLowerX), NormalizeY(botMarginY), NormalizeX(topMarginUpperX),
             NormalizeY(botMarginY), BLACK);

    // Line 5: y = 0.85 {0.25 < x < 0.6}
    DrawLine(NormalizeX(topMarginLowerX), NormalizeY(topMarginY), NormalizeX(topMarginUpperX),
             NormalizeY(topMarginY), BLACK);

    // Line 5: y = 0.5 {0.85 < x < 0.95}
    DrawLine(NormalizeX(rightMarginLowerX), NormalizeY(topRightMarginY),
             NormalizeX(rightMarginUpperX), NormalizeY(topRightMarginY), BLACK);

    // Circle 1: (x - 0.6)^2 + (y - 0.5)^2 = (0.35)^2 {x > 0.6}
    // Normalize the circle's center and radius
    float centerX = NormalizeX(0.5f);
    float centerY = NormalizeY(0.5f);
    float radius = 0.35f * width;  // Radius is scaled only by width
    DrawClippedCircle(centerX, centerY, radius, BLACK);
}

void DrawOr(const std::shared_ptr<LogicGate> gate)
{
    Rectangle bd = gate->bd;
    float width = bd.width;
    float height = bd.height;

    // Normalize the bounding box (bd.x, bd.y is the origin of the rectangle)
    auto NormalizeX = [&](float x)
    {
        return bd.x + x * width;
    };
    auto NormalizeY = [&](float y)
    {
        return bd.y + y * height;
    };
    float leftMarginLowerX = 0.05f;
    float leftMarginUpperX = 0.15f;
    float botLeftLineY = 0.25f;
    float topLeftLineY = 0.75f;

    float topMarginUpperX = 0.5f;
    float topMarginLowerX = 0.15f;
    float topMarginY = 0.85f;
    float botMarginY = 0.15f;

    float rightMarginLowerX = 0.85f;
    float rightMarginUpperX = 0.95f;
    float topRightMarginY = 0.5f;

    // Line 1: y = 0.35 {0.05 < x < 0.25}
    // Bot Input Line
    DrawLine(NormalizeX(leftMarginLowerX), NormalizeY(botLeftLineY), NormalizeX(leftMarginUpperX),
             NormalizeY(botLeftLineY), RED);

    // Line 2: y = 0.65 {0.05 < x < 0.25}
    // Top Input Line
    DrawLine(NormalizeX(leftMarginLowerX), NormalizeY(topLeftLineY), NormalizeX(leftMarginUpperX),
             NormalizeY(topLeftLineY), RED);

    // Line 3: x = 0.25 {0.15 < y < 0.85}
    DrawLine(NormalizeX(leftMarginUpperX), NormalizeY(botMarginY), NormalizeX(leftMarginUpperX),
             NormalizeY(topMarginY), RED);

    // Line 4: y = 0.15 {0.25 < x < 0.6}
    DrawLine(NormalizeX(topMarginLowerX), NormalizeY(botMarginY), NormalizeX(topMarginUpperX),
             NormalizeY(botMarginY), RED);

    // Line 5: y = 0.85 {0.25 < x < 0.6}
    DrawLine(NormalizeX(topMarginLowerX), NormalizeY(topMarginY), NormalizeX(topMarginUpperX),
             NormalizeY(topMarginY), RED);

    // Line 5: y = 0.5 {0.85 < x < 0.95}
    DrawLine(NormalizeX(rightMarginLowerX), NormalizeY(topRightMarginY),
             NormalizeX(rightMarginUpperX), NormalizeY(topRightMarginY), BLACK);

    // Circle 1: (x - 0.6)^2 + (y - 0.5)^2 = (0.35)^2 {x > 0.6}
    // Normalize the circle's center and radius
    float centerX = NormalizeX(0.5f);
    float centerY = NormalizeY(0.5f);
    float radius = 0.35f * width;  // Radius is scaled only by width
    DrawClippedCircle(centerX, centerY, radius, RED);
}

void DrawCircuit(const std::shared_ptr<Circuit> circuit)
{
    // 1 - Draw gates
    for (size_t i = 0; i < circuit->gates.size(); i++)
    {
        const auto& gate = circuit->gates[i];  // Access the gate

#ifdef IS_DRAWING_BOUNDARY_BOX
        DrawBoundaryBox(gate);
#endif

        if (gate->type == "and")
        {
            DrawAnd(gate);
        }
        else if (gate->type == "or")
        {
            DrawOr(gate);
        }
        else
        {
            // Log runtime error
            DrawText("Error: unknown gate type", 10, 10 + (int)i * 20, 20, RED);
        }
    }

    // 2 - Draw connections
    for (size_t i = 0; i < circuit->connections.size(); i++)
    {
        for (size_t j = 0; j < circuit->connections[i].physCon.wires.size()-1; j++)
        {
            DrawLine(circuit->connections[i].physCon.wires[j].x, circuit->connections[i].physCon.wires[j].y,
                circuit->connections[i].physCon.wires[j+1].x, circuit->connections[i].physCon.wires[j+1].y , BLACK);
        }
    }
}

void DrawBoundaryBox(const std::shared_ptr<LogicGate> gate)
{
    DrawRectangleLines(gate->bd.x, gate->bd.y, gate->bd.width, gate->bd.height,
                       gate->type == "and" ? GREEN : BLUE);
}

void DrawClippedCircle(float cx, float cy, float radius, Color color)
{
    int segments = 720;  // Number of segments for smoothness
    float angleStep = 2 * PI / segments;

    for (int i = 0; i < segments; i++)
    {
        float angle1 = i * angleStep;
        float angle2 = (i + 1) * angleStep;

        // Circle points
        float x1 = cx + cos(angle1) * radius;
        float y1 = cy + sin(angle1) * radius;
        float x2 = cx + cos(angle2) * radius;
        float y2 = cy + sin(angle2) * radius;

        // Clip the circle to x > centerX (0.6 normalized)
        if (x1 >= cx && x2 >= cx)
        {
            DrawLineV(Vector2{x1, y1}, Vector2{x2, y2}, color);
        }
    }
}

}  // namespace LogicElementsDraw
