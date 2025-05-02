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
    
    void DrawCircuit(const SP_Circuit circuit)
    {
        // auto start = std::chrono::high_resolution_clock::now();  // ✅ Start timing
        // auto end = std::chrono::high_resolution_clock::now();  // ✅ End timing
        // double elapsed = std::chrono::duration<double, std::milli>(end - start).count();
        // std::cout << "Time taken to draw gate: " << elapsed << " ms" << std::endl;

         // 1) Seed the stack with all top-level components
        std::vector<SP_Component> stack;
        stack.reserve(circuit->components.size());
        for (const auto& gate : circuit->components)
            stack.push_back(gate);
        // 2) Pop, draw, then push any children
        while (!stack.empty()) {
            SP_Component gate = stack.back();
            stack.pop_back();
            if (appSettings.isDrawingBoundaryBox)
                DrawBoundaryBox(gate);
            gate->Draw();
            // push this gate’s own components onto the stack
            // (so they’ll be drawn later)
            for (const auto& child : gate->components) {
                stack.push_back(child);
            }
        }

        // 2 - Draw connections
        for (size_t i = 0; i < circuit->getMainComponent()->connections.size(); i++)
        {
            if (circuit->getMainComponent()->connections[i].physCon.wires.size() == 0)
            {
                continue;
            }
            for (size_t j = 0; j < circuit->getMainComponent()->connections[i].physCon.wires.size() - 1; j++)
            {
                Vector2 start = circuit->getMainComponent()->connections[i].physCon.wires[j];
                Vector2 end = circuit->getMainComponent()->connections[i].physCon.wires[j + 1];
                // DrawLine();
                if (circuit->getMainComponent()->connections[i].is_connected)
                {
                    bool val = false;
                    for (size_t k = 0; k < circuit->getMainComponent()->connections[i].sourceGate->outputs.size(); k++)
                    {
                        if (circuit->getMainComponent()->connections[i].sourceGate->outputs[k].name ==
                            circuit->getMainComponent()->connections[i].sourceLogic)
                        {
                            val = circuit->getMainComponent()->connections[i].sourceGate->outputs[k].val;
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
        for (size_t i = 0; i < circuit->getMainComponent()->connections.size(); i++)
        {
            if (circuit->getMainComponent()->connections[i].hovering.is_hovering)
            {
                DrawInteractableWirePoints(circuit->getMainComponent()->connections[i].hovering.pos,
                    circuit->getMainComponent()->connections[i].hovering.pos, GREEN);
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
    void DrawBoundaryBox(const std::shared_ptr<Component> component)
    {
        Color color = GREEN;
        /*if (gate->m_type == LogicElements::GateType::AND)
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
        }*/
        DrawRectangleLines(component->bd.x, component->bd.y, component->bd.width, component->bd.height, color);
    }
    
}  // namespace LogicElementsDraw
