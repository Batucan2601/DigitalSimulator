#include "LogicElementsDraw.h"

#include <iostream>
namespace LogicElementsDraw
{

    void DrawGateElement(const std::shared_ptr<LogicElements::LogicGate> gate)
    {
        Rectangle bd = gate->bd;  // Bounding box of the gate
        float bd_width = bd.width;
        float bd_height = bd.height;

        float texture_width = gate->m_texture.width;
        float texture_height = gate->m_texture.height;

        Rectangle source = {0, 0, texture_width, texture_height};
        Rectangle dest = {bd.x, bd.y, bd_width, bd_height};
        Vector2 origin = {0, 0};  // Top-left corner as origin

        DrawTexturePro(gate->m_texture, source, dest, origin, 0.0f, WHITE);
    }

    void DrawCircuit(const std::shared_ptr<CircuitElements::Circuit> circuit)
    {
        // 1 - Draw gates
        for (size_t i = 0; i < circuit->gates.size(); i++)
        {
            const auto& gate = circuit->gates[i];  // Access the gate

#ifdef IS_DRAWING_BOUNDARY_BOX
            DrawBoundaryBox(gate);
#endif

            DrawGateElement(gate);
        }

        // 2 - Draw connections
        for (size_t i = 0; i < circuit->connections.size(); i++)
        {
            if (circuit->connections[i].physCon.wires.size() == 0)
            {
                continue;
            }
            for (size_t j = 0; j < circuit->connections[i].physCon.wires.size() - 1; j++)
            {
                Vector2 start = circuit->connections[i].physCon.wires[j];
                Vector2 end = circuit->connections[i].physCon.wires[j + 1];
                // DrawLine();
                if (circuit->connections[i].sourceGate->getOutput("Out"))
                {
                    DrawLineEx(start, end, LINE_THICKNESS,
                               circuit->connections[i].is_connected ? GREEN : RED);
                }
                else
                {
                    DrawLineEx(start, end, LINE_THICKNESS,
                               circuit->connections[i].is_connected ? BLACK : RED);
                }

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
        DrawInteractableWirePoints(circuit->selected_wires.wire_hovering,
                                   circuit->selected_wires.wire_hovering, GREEN);

        // 3 - DrawActiveWire
        if (circuit->active_wire.is_visible)
        {
            Vector2 straight_line = Controls::Generate_straight_lines(circuit->active_wire.start,
                                                                      circuit->active_wire.end);
            DrawLine(circuit->active_wire.start.x, circuit->active_wire.start.y, straight_line.x,
                     straight_line.y, GREEN);
            DrawLine(straight_line.x, straight_line.y, circuit->active_wire.end.x,
                     circuit->active_wire.end.y, GREEN);

            DrawInteractableWirePoints(circuit->active_wire.start, straight_line, GREEN);
            DrawInteractableWirePoints(straight_line, circuit->active_wire.end, GREEN);
        }

        if (circuit->is_GUIdragdragging)
        {
            DrawRectangleLines(circuit->selected_wires.wire_hovering.x,
                               circuit->selected_wires.wire_hovering.y, SLICE_SIZE, SLICE_SIZE,
                               BLUE);
        }
        if (circuit->is_GUIdragdropped)
        {
            circuit->is_GUIdragdropped = false;
        }
    }
    void DrawInteractableWirePoints(Vector2 start, Vector2 end, Color color)
    {
        DrawPointAcross(start, end, WIRE_INTERACT_POINT_SIZE, SPACING_SIZE, color);
    }
    void DrawBoundaryBox(const std::shared_ptr<LogicElements::LogicGate> gate)
    {
        Color color;
        if (gate->m_type == LogicElements::GateType::AND)
        {
            color = GREEN;
        }
        else if (gate->m_type == LogicElements::GateType::OR)
        {
            color = BLUE;
        }
        else if (gate->m_type == LogicElements::GateType::NOT)
        {
            color = RED;
        }
        else if (gate->m_type == LogicElements::GateType::XOR)
        {
            color = YELLOW;
        }
        else if (gate->m_type == LogicElements::GateType::XOR)
        {
            color = ORANGE;
        }
        else
        {
            color = BLACK;
        }

        DrawRectangleLines(gate->bd.x, gate->bd.y, gate->bd.width, gate->bd.height, color);
    }

}  // namespace LogicElementsDraw
