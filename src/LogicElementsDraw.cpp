#include "LogicElementsDraw.h"

#include <chrono>  // High precision timing
#include <iostream>

extern AppSettings::Settings appSettings;

namespace LogicElementsDraw
{

    void DrawGateElement(const std::shared_ptr<LogicElements::LogicGate> gate)
    {
        const Rectangle& bd = gate->bd;  // Bounding box of the gate
        float bd_width = bd.width;
        float bd_height = bd.height;

        Texture texture = gate->m_texture;

        Rectangle source = {0, 0, (float)texture.width, (float)texture.height};
        Rectangle dest = {bd.x, bd.y, bd_width, bd_height};
        Vector2 origin = {0, 0};  // Top-left corner as origin

        DrawTexturePro(gate->m_texture, source, dest, origin, 0.0f, WHITE);
    }

    void DrawCircuit(const std::shared_ptr<CircuitElements::Circuit> circuit)
    {
        // 1 - Draw gates
        auto start = std::chrono::high_resolution_clock::now();  // ✅ Start timing

        for (size_t i = 0; i < circuit->gates.size(); i++)
        {
            const auto& gate = circuit->gates[i];  // Access the gate

            if (appSettings.isDrawingBoundaryBox)
            {
                DrawBoundaryBox(gate);
            }

            DrawGateElement(gate);

            DrawInOut(gate);
        }

        auto end = std::chrono::high_resolution_clock::now();  // ✅ End timing
        double elapsed = std::chrono::duration<double, std::milli>(end - start).count();

        std::cout << "Time taken to draw gate: " << elapsed << " ms" << std::endl;

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
                if (circuit->connections[i].is_connected)
                {
                    bool val = false;
                    for (size_t i = 0; i < circuit->connections[i].sourceGate->outputs.size(); i++)
                    {
                        if (circuit->connections[i].sourceGate->outputs[i].name ==
                            circuit->connections[i].sourceLogic)
                        {
                            val = circuit->connections[i].sourceGate->outputs[i].val;
                            break;
                        }
                    }
                    DrawLineEx(start, end, LINE_THICKNESS, val ? GREEN : BLACK);
                }
                else
                {
                    DrawLineEx(start, end, LINE_THICKNESS, RED);
                }

                // draw their interactable points
                DrawInteractableWirePoints(start, end, BLUE);
            }
        }

        // color green the selected wires
        for (size_t i = 0; i < circuit->connections.size(); i++)
        {
            if (circuit->connections[i].hovering.is_hovering)
            {
                DrawInteractableWirePoints(circuit->connections[i].hovering.pos,
                                           circuit->connections[i].hovering.pos, GREEN);
            }
        }
        DrawInteractableWirePoints(circuit->selected_wires.wire_hovering,
                                   circuit->selected_wires.wire_hovering, GREEN);

        // 3 - DrawActiveWire
        if (circuit->active_wire.is_visible)
        {
            Rectangle rec = {circuit->active_wire.start.x, circuit->active_wire.start.y, 0, 0};
            circuit->active_wire.start = Controls::SnapToNearestGrid(rec);
            rec = {circuit->active_wire.end.x, circuit->active_wire.end.y, 0, 0};
            circuit->active_wire.end = Controls::SnapToNearestGrid(rec);

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
                               circuit->selected_wires.wire_hovering.y, appSettings.SLICE_SIZE,
                               appSettings.SLICE_SIZE, BLUE);
        }
        if (circuit->is_GUIdragdropped)
        {
            circuit->is_GUIdragdropped = false;
        }
    }

    void DrawInteractableWirePoints(Vector2 start, Vector2 end, Color color)
    {
        DrawPointAcross(start, end, WIRE_INTERACT_POINT_SIZE, appSettings.SPACING_SIZE, color);
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
    void DrawInOut(std::shared_ptr<LogicElements::LogicGate> gate)
    {
        for (size_t i = 0; i < gate->outputs.size(); i++)
        {
            // GRID_POINT_SIZE
            Vector2 pos = gate->outputs[i].pos;
            Rectangle rec = {pos.x - appSettings.IN_OUT_RECT_WIDTH / 2,
                             pos.y - appSettings.IN_OUT_RECT_WIDTH / 2,
                             appSettings.IN_OUT_RECT_WIDTH, appSettings.IN_OUT_RECT_WIDTH};
            DrawRectangle(rec.x, rec.y, rec.width, rec.width, BLUE);
        }
        if (gate->is_hovered)
        {
            for (size_t i = 0; i < gate->inputs.size(); i++)
            {
                Vector2 pos = gate->inputs[i].pos;
                Rectangle rec = {pos.x - appSettings.IN_OUT_RECT_WIDTH / 2,
                                 pos.y - appSettings.IN_OUT_RECT_WIDTH / 2,
                                 appSettings.IN_OUT_RECT_WIDTH, appSettings.IN_OUT_RECT_WIDTH};
                DrawRectangle(rec.x, rec.y, rec.width, rec.width, BLUE);
            }
        }
    }
}  // namespace LogicElementsDraw
