#include "LogicElementsDraw.h"

#include <iostream>
namespace LogicElementsDraw
{

    void DrawGateElement(const std::shared_ptr<LogicElements::LogicGate> gate)
    {
        Rectangle bd = gate->bd; // Bounding box of the gate
        float width = bd.width;
        float height = bd.height;

        Rectangle source = {0, 0, gate->m_texture.width, gate->m_texture.height};
        Rectangle dest = {bd.x, bd.y, width, height};
        Vector2 origin = {0, 0}; // Top-left corner as origin

        DrawTexturePro(gate->m_texture, source, dest, origin, 0.0f, WHITE);
    }

    void DrawCircuit(const std::shared_ptr<CircuitElements::Circuit> circuit)
    {
        // 1 - Draw gates
        for (size_t i = 0; i < circuit->gates.size(); i++)
        {
            const auto &gate = circuit->gates[i]; // Access the gate

#ifdef IS_DRAWING_BOUNDARY_BOX
            DrawBoundaryBox(gate);
#endif

            DrawGateElement(gate);
        }

        // 2 - Draw connections
        for (size_t i = 0; i < circuit->connections.size(); i++)
        {
            for (size_t j = 0; j < circuit->connections[i].physCon.wires.size() - 1; j++)
            {
                Vector2 start = circuit->connections[i].physCon.wires[j];
                Vector2 end = circuit->connections[i].physCon.wires[j + 1];
                // DrawLine();
                DrawLineEx(start, end, LINE_THICKNESS, circuit->connections[i].is_connected ? BLACK : RED);
                // draw their interactable points
                DrawInteractableWirePoints(start, end, BLUE);
            }
        }

        // color green the selected wires
        for (size_t i = 0; i < circuit->selected_wires.selected_wires.size(); i++)
        {
            Vector2 pos = circuit->selected_wires.selected_wires[i];
            DrawInteractableWirePoints(pos, pos, GREEN);
        }
        DrawInteractableWirePoints(circuit->selected_wires.wire_hovering, circuit->selected_wires.wire_hovering, GREEN);

        // 3 - DrawActiveWire
        if (circuit->active_wire.is_visible)
        {
            Vector2 straight_line = Controls::Generate_straight_lines(circuit->active_wire.start, circuit->active_wire.end);
            DrawLine(circuit->active_wire.start.x, circuit->active_wire.start.y, straight_line.x, straight_line.y, GREEN);
            DrawLine(straight_line.x, straight_line.y, circuit->active_wire.end.x, circuit->active_wire.end.y, GREEN);

            DrawInteractableWirePoints(circuit->active_wire.start, straight_line, GREEN);
            DrawInteractableWirePoints(straight_line, circuit->active_wire.end, GREEN);
        }
    }
    void DrawInteractableWirePoints(Vector2 start, Vector2 end, Color color)
    {
        DrawPointAcross(start, end, WIRE_INTERACT_POINT_SIZE, SPACING_SIZE, color);
    }
    void DrawBoundaryBox(const std::shared_ptr<LogicElements::LogicGate> gate)
    {
        Color color;
        if (gate->type == LogicElements::GateType::AND)
        {
            color = GREEN;
        }
        else if (gate->type == LogicElements::GateType::OR)
        {
            color = BLUE;
        }
        else if (gate->type == LogicElements::GateType::NOT)
        {
            color = RED;
        }
        else if (gate->type == LogicElements::GateType::XOR)
        {
            color = YELLOW;
        }
        else if (gate->type == LogicElements::GateType::XOR)
        {
            color = ORANGE;
        }
        else
        {
            color = BLACK;
        }

        DrawRectangleLines(gate->bd.x, gate->bd.y, gate->bd.width, gate->bd.height,
                           color);
    }
    void DrawClippedCircle(float cx, float cy, float radius, Color color)
    {
        int segments = 720; // Number of segments for smoothness
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

} // namespace LogicElementsDraw
