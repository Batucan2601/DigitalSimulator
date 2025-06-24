#include "LogicElementsDraw.h"

#include <chrono>  // High precision timing
#include <iostream>
#include <Util/Utils.h>
#include <SubCircuit.h>


namespace LogicElementsDraw
{

    void DrawGateElement(const std::shared_ptr<Component> gate)
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

    void DrawSubCircuit(const std::shared_ptr<SubcircuitComponent> subcircuit)
    {
         const Rectangle& bd = subcircuit->bd;  // Bounding box of the gate
        float bd_width = bd.width;
        float bd_height = bd.height;

        Texture texture = subcircuit->m_texture;

        Rectangle source = {0, 0, (float)texture.width, (float)texture.height};
        Rectangle dest = {bd.x, bd.y, bd_width, bd_height};
        Vector2 origin = {0, 0};  // Top-left corner as origin
        DrawTexturePro(subcircuit->m_texture, source, dest, origin, 0.0f, WHITE);

    }
    void DrawCircuit(const SP_Circuit circuit)
    {
        // auto start = std::chrono::high_resolution_clock::now();  // ✅ Start timing
        // auto end = std::chrono::high_resolution_clock::now();  // ✅ End timing
        // double elapsed = std::chrono::duration<double, std::milli>(end - start).count();
        // std::cout << "Time taken to draw gate: " << elapsed << " ms" << std::endl;

        // 1 - Draw gates
        for (size_t i = 0; i < circuit->gates.size(); i++)
        {
            const auto& gate = circuit->gates[i];  // Access the gate

            if (AppSettings::appSettings.isDrawingBoundaryBox)
            {
                DrawBoundaryBox(gate);
            }

            DrawGateElement(gate);
            DrawInOut(gate);
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
                if (circuit->connections[i].is_connected)
                {
                    SignalVal val = SignalVal::SIGNAL_0;
                    for (size_t k = 0; k < circuit->connections[i].sourceGate->outputs.size(); k++)
                    {
                        if (circuit->connections[i].sourceGate->outputs[k].name ==
                            circuit->connections[i].sourceLogic)
                        {
                            val = circuit->connections[i].sourceGate->outputs[k].val;
                            break;
                        }
                    }
                    if( circuit->connections[i].sourceGate->inputs.size() > 0 )
                    {
                         circuit->connections[i].sourceGate->m_logger.
                    info("my inputs are {} {}" ,circuit->connections[i].sourceGate->inputs[0].val ,
                    circuit->connections[i].sourceGate->inputs[1].val  );
                    }
                    circuit->connections[i].sourceGate->m_logger.
                    info("The value is  {} ",val);
                    
                    Color signalColor = BLACK;
                    switch (val)
                    {
                    case SignalVal::SIGNAL_0:
                        signalColor = BLACK;
                        break; 
                    case SignalVal::SIGNAL_1:
                        signalColor = GREEN; 
                        break; 
                    case SignalVal::SIGNAL_X:
                        signalColor = PURPLE; 
                        break; 
                    case SignalVal::SIGNAL_Z:
                        signalColor = YELLOW;
                        break; 
                    default:
                        throw("Signal type undefined");
                    }
                    DrawLineEx(start, end, LINE_THICKNESS, signalColor);

                    circuit->connections[i].sourceGate->m_logger.
                    info("The value is  {} ",circuit->connections[i].sourceGate->outputs[0].val);
                   
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
        if(! (circuit->selected_wires.wire_hovering.x > AppSettings::appSettings.screenWidth ||
        circuit->selected_wires.wire_hovering.x < -AppSettings::appSettings.screenWidth ||
        circuit->selected_wires.wire_hovering.y > AppSettings::appSettings.screenHeight ||
        circuit->selected_wires.wire_hovering.y < -AppSettings::appSettings.screenHeight 
        ))
        {
            DrawInteractableWirePoints(circuit->selected_wires.wire_hovering,
                                       circuit->selected_wires.wire_hovering, GREEN);
        }   
        //DrawInteractableWirePoints(circuit->selected_wires.wire_hovering, circuit->selected_wires.wire_hovering, GREEN);

        // 3 - DrawActiveWire
        if (circuit->active_wire.is_visible)
        {
            Rectangle rec = {circuit->active_wire.start.x, circuit->active_wire.start.y, 0, 0};
            circuit->active_wire.start = Utils::SnapToNearestGrid(rec);
            rec = {circuit->active_wire.end.x, circuit->active_wire.end.y, 0, 0};
            circuit->active_wire.end = Utils::SnapToNearestGrid(rec);

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
                               circuit->selected_wires.wire_hovering.y, AppSettings::appSettings.SLICE_SIZE,
                               AppSettings::appSettings.SLICE_SIZE, BLUE);
        }
        if (circuit->is_GUIdragdropped)
        {
            circuit->is_GUIdragdropped = false;
        }
    }

    void DrawInteractableWirePoints(Vector2 start, Vector2 end, Color color)
    {
        DrawPointAcross(start, end, WIRE_INTERACT_POINT_SIZE, AppSettings::appSettings.SPACING_SIZE, color);
    }
    void DrawBoundaryBox(const std::shared_ptr<Component> gate)
    {
        Color color;
        if (gate->m_type == CircuitElements::ComponentType::AND)
        {
            color = GREEN;
        }
        else if (gate->m_type == CircuitElements::ComponentType::OR)
        {
            color = BLUE;
        }
        else if (gate->m_type == CircuitElements::ComponentType::NOT)
        {
            color = RED;
        }
        else if (gate->m_type == CircuitElements::ComponentType::XOR)
        {
            color = YELLOW;
        }
        else if (gate->m_type == CircuitElements::ComponentType::XOR)
        {
            color = ORANGE;
        }
        else
        {
            color = BLACK;
        }

        DrawRectangleLines(gate->bd.x, gate->bd.y, gate->bd.width, gate->bd.height, color);
    }
    void DrawInOut(std::shared_ptr<Component> gate)
    {
        for (size_t i = 0; i < gate->outputs.size(); i++)
        {
            // GRID_POINT_SIZE
            Vector2 pos = gate->outputs[i].pos;
            Rectangle rec = {pos.x - AppSettings::appSettings.IN_OUT_RECT_WIDTH / 2,
                             pos.y - AppSettings::appSettings.IN_OUT_RECT_WIDTH / 2,
                             AppSettings::appSettings.IN_OUT_RECT_WIDTH, AppSettings::appSettings.IN_OUT_RECT_WIDTH};
            
            Color recColor = BLUE;
            if( gate->outputs[i].type == SignalType::OUTPUT )
            {
                recColor = RED; 
            }
            DrawRectangle(rec.x, rec.y, rec.width, rec.width, recColor);
        }
        //if (gate->is_hovered)
        {
            for (size_t i = 0; i < gate->inputs.size(); i++)
            {
                Vector2 pos = gate->inputs[i].pos;
                Rectangle rec = {pos.x - AppSettings::appSettings.IN_OUT_RECT_WIDTH / 2,
                                 pos.y - AppSettings::appSettings.IN_OUT_RECT_WIDTH / 2,
                                 AppSettings::appSettings.IN_OUT_RECT_WIDTH, AppSettings::appSettings.IN_OUT_RECT_WIDTH};
               
                Color recColor = BLUE;
                if( gate->inputs[i].type == SignalType::INPUT )
                {
                    recColor = GREEN; 
                }
                DrawRectangle(rec.x, rec.y, rec.width, rec.width, recColor);
            
            }
            
        }
    }
}  // namespace LogicElementsDraw
