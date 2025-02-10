#include "LogicElementsDraw.h"

namespace LogicElementsDraw
{
void DrawAnd(const std::shared_ptr<LogicGate> gate)
{
    // Calculate input positions
    float inputLineX = gate->bd.x + gate->bd.width * 0.1f;     // Slightly inside the bounding box
    float inputTopY = gate->bd.y + gate->bd.height * 0.25;     // Top input
    float inputBottomY = gate->bd.y + gate->bd.height * 0.75;  // Bottom input

    // Draw input lines (vertical lines)
    DrawLine(inputLineX, inputTopY, inputLineX + gate->bd.width * 0.15f, inputTopY,
             BLACK);  // Top input
    DrawLine(inputLineX, inputBottomY, inputLineX + gate->bd.width * 0.15f, inputBottomY,
             BLACK);  // Bottom input

    // Draw the semi-circle (OR gate curve)
    Vector2 center;
    center.x = inputLineX + gate->bd.width * 0.15f;  // Right end of input lines
    center.y = gate->bd.y + gate->bd.height / 2;
    DrawCircleSectorLines(center, gate->bd.width / 2, -90, 90, 16, BLACK);

    // Draw output line (horizontal line)
    DrawLine(center.x + gate->bd.width / 2, center.y, center.x + gate->bd.width / 2 + 10, center.y,
             BLACK);
}

void DrawOr(const std::shared_ptr<LogicGate> gate)
{
    // Calculate input positions
    float inputLineX = gate->bd.x + gate->bd.width * 0.1f;     // Slightly inside the bounding box
    float inputTopY = gate->bd.y + gate->bd.height * 0.25;     // Top input
    float inputBottomY = gate->bd.y + gate->bd.height * 0.75;  // Bottom input

    // Draw input lines (vertical lines)
    DrawLine(inputLineX, inputTopY, inputLineX + gate->bd.width * 0.15f, inputTopY,
             RED);  // Top input
    DrawLine(inputLineX, inputBottomY, inputLineX + gate->bd.width * 0.15f, inputBottomY,
             RED);  // Bottom input

    // Draw the semi-circle (OR gate curve)
    Vector2 center;
    center.x = inputLineX + gate->bd.width * 0.15f;  // Right end of input lines
    center.y = gate->bd.y + gate->bd.height / 2;
    DrawCircleSectorLines(center, gate->bd.width / 2, -90, 90, 16, RED);

    // Draw output line (horizontal line)
    DrawLine(center.x + gate->bd.width / 2, center.y, center.x + gate->bd.width / 2 + 10, center.y,
             RED);
}

void DrawCircuit(const std::shared_ptr<Circuit> circuit)
{
    // 1 - Draw gates
    for (size_t i = 0; i < circuit->gates.size(); i++)
    {
        const auto& gate = circuit->gates[i];  // Access the gate
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
        // const auto& connection = circuit->connections[i]; // Access the connection

        // // Get the source and target gates
        // const auto& sourceGate = connection.sourceGate;
        // const auto& targetGate = connection.targetGate;

        // // Get the source and target positions
        // Vector2 sourcePos = {
        //     sourceGate->bd.x + sourceGate->bd.width,            // Right edge of the source gate
        //     sourceGate->bd.y + sourceGate->bd.height / 2        // Vertically centered
        // };
        // Vector2 targetPos = {
        //     targetGate->bd.x,                                   // Left edge of the target gate
        //     targetGate->bd.y + targetGate->bd.height / 2        // Vertically centered
        // };

        // // Draw the connection line
        // DrawLineEx(sourcePos, targetPos, 2.0f, DARKGRAY);

        // // Optionally, draw the name of the signal being passed (e.g., "Out")
        // DrawText(connection.sourceOutput.c_str(), (sourcePos.x + targetPos.x) / 2,
        //          (sourcePos.y + targetPos.y) / 2, 10, DARKGRAY);
    }
}

}  // namespace LogicElementsDraw
