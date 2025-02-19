#include "Controls.h"

#include "GUI/GUITools.h"
#include "LogicElementBase.h"
#include "LogicElements.h"
#include "LogicElements/include.h"
#include "raylib.h"

#include <iostream>
#include <memory>

namespace Controls
{
    std::string control_logger_name = "ControlLogger";
    std::string gui_circuit_logger = "GUICircuitLogger";
    static ClassLogger control_logger(control_logger_name);
    static auto selected_circuit = std::make_shared<CircuitElements::Circuit>(gui_circuit_logger);
    std::vector<std::shared_ptr<LogicElements::LogicGate>> selected_logic_gate(1);
    static Camera2D camera = {};
    static bool is_dragging = false;
    static bool is_logic_selected = false;
    static Vector2 mouse_pos;
    Vector2 offset;
    static Vector2 gate_initial_position;

    void Controls_set_camera(unsigned int screen_width, unsigned int screen_height)
    {
        camera.target = {0.0f, 0.0f};  // Camera looks at the origin initially
        camera.offset = {screen_width / 2.0f,
                         screen_height / 2.0f};  // Offset to center the camera in the window
        camera.rotation = 0.0f;                  // No rotation
        camera.zoom = 1.0f;                      // Default zoom
    }

    void Controls_update(std::shared_ptr<CircuitElements::Circuit> circuit)
    {
        // Drag camera with the left mouse button
        if (IsMouseButtonDown(MOUSE_RIGHT_BUTTON))
        {
            // Get the mouse movement since the last frame
            Vector2 mouseDelta = GetMouseDelta();
            // Adjust the camera target (dividing by camera.zoom for consistent movement at
            // different zoom levels)
            camera.target.x -= mouseDelta.x / camera.zoom;
            camera.target.y -= mouseDelta.y / camera.zoom;
        }

        // Zoom in/out using the mouse wheel
        float wheel = GetMouseWheelMove();
        if (wheel != 0)
        {
            camera.zoom += wheel * 0.1f;  // Adjust the zoom sensitivity as needed
            if (camera.zoom < 0.1f)
                camera.zoom = 0.1f;  // Prevent zoom from becoming too small (or negative)
        }

        // get data
        selected_circuit = circuit;

        Controls_Mouse_click();
        Control_Keyboard_Event(selected_circuit);
        Controls_Handle_Continous(selected_circuit);
    }

    Camera2D Controls_get_camera()
    {
        return camera;
    }

    void Controls_Handle_Continous(std::shared_ptr<CircuitElements::Circuit> circuit)
    {
        mouse_pos = GetScreenToWorld2D(GetMousePosition(), camera);  // Get mouse position
        if (is_logic_selected)
        {
            Rectangle pos = {mouse_pos.x, mouse_pos.y, 0, 0};
            circuit->active_wire.end = SnapToNearestGrid(pos);
        }

        // hovering coloring
        CircuitElements::Connection temp;
        bool is_near_wire = CheckNearWire(circuit, mouse_pos, temp);
        if (is_near_wire)
        {
            Rectangle rec = {mouse_pos.x, mouse_pos.y, 0, 0};
            Vector2 pos = SnapToNearestGrid(rec);
            circuit->selected_wires.wire_hovering = pos;
            circuit->m_logger.info("catched new ");
        }

        // check dragging
        if (GUITools::dragDrop.state == GUITools::DragDropState::DRAGGING)
        {
            Rectangle rec = {mouse_pos.x, mouse_pos.y, 0, 0};
            Vector2 pos = SnapToNearestGrid(rec);
            circuit->selected_wires.wire_hovering = pos;
            circuit->m_logger.info("catched new ");
            circuit->is_GUIdragdragging = true;
        }
        else if (GUITools::dragDrop.state == GUITools::DragDropState::DROPPED)
        {
            circuit->is_GUIdragdropped = true;
            circuit->is_GUIdragdragging = false;

            // add the new circuit
            std::string new_gate = "or_gate_logger";
            switch (GUITools::dragDrop.gateType)
            {
                case (LogicElements::GateType::AND):
                    circuit->addGate(std::make_shared<LogicElements::Gates::AndGate>(new_gate));
                    break;
                case (LogicElements::GateType::OR):
                    circuit->addGate(std::make_shared<LogicElements::Gates::OrGate>(new_gate));
                    break;
                case (LogicElements::GateType::XOR):
                    circuit->addGate(std::make_shared<LogicElements::Gates::XorGate>(new_gate));
                    break;
                case (LogicElements::GateType::XAND):
                    circuit->addGate(std::make_shared<LogicElements::Gates::XandGate>(new_gate));
                    break;
                case (LogicElements::GateType::NOT):
                    circuit->addGate(std::make_shared<LogicElements::Gates::NotGate>(new_gate));
                    break;
                case (LogicElements::GateType::INPUT):
                    circuit->addGate(std::make_shared<LogicElements::Gates::InputGate>(new_gate));
                    break;
                default:
                    break;
            }
            if (GUITools::dragDrop.gateType != LogicElements::GateType::NONE)
            {
                circuit->gates[circuit->gates.size() - 1]->setPosition(mouse_pos.x, mouse_pos.y);
                GUITools::dragDrop.gateType = LogicElements::GateType::NONE;
            }
        }
    }
    void Control_Keyboard_Event(std::shared_ptr<CircuitElements::Circuit> circuit)
    {
        if (selected_logic_gate.empty() || !selected_logic_gate[0])
        {
            // std::cerr << "Error: No selected logic gate!" << std::endl;
            // control_logger.info("Error: No selected logic gate!");
            return;
        }

        // Store the current position of the selected logic gate
        float current_x = selected_logic_gate[0]->bd.x;
        float current_y = selected_logic_gate[0]->bd.y;
        float gate_width = selected_logic_gate[0]->bd.width;
        float gate_height = selected_logic_gate[0]->bd.height;

        Vector2 new_position = {current_x, current_y};

        // Adjust the position based on keyboard input
        bool key_pressed = false;
        if (IsKeyPressed(KEY_UP))
        {
            key_pressed = true;
            new_position.y -= SPACING_SIZE;
        }
        if (IsKeyPressed(KEY_DOWN))
        {
            key_pressed = true;
            new_position.y += SPACING_SIZE;
        }
        if (IsKeyPressed(KEY_LEFT))
        {
            key_pressed = true;
            new_position.x -= SPACING_SIZE;
        }
        if (IsKeyPressed(KEY_RIGHT))
        {
            key_pressed = true;
            new_position.x += SPACING_SIZE;
        }
        if (IsKeyPressed(KEY_ESCAPE))
        {
            is_logic_selected = false;  // kills wiring process for sure everytime
            circuit->active_wire.is_visible = false;
        }

        if (IsKeyPressed(KEY_DELETE))
        {
            // delete the selected gate
            for (size_t i = 0; i < circuit->gates.size(); i++)
            {
                if (circuit->gates[i] == selected_logic_gate[0])
                {
                    circuit->gates.erase(circuit->gates.begin() + i);
                    break;
                }
            }
            // delete the connections
            for (size_t i = 0; i < circuit->connections.size(); i++)
            {
                if (circuit->connections[i].sourceGate == selected_logic_gate[0] ||
                    circuit->connections[i].targetGate == selected_logic_gate[0])
                {
                    circuit->connections.erase(circuit->connections.begin() + i);
                    i--;
                }
            }
            selected_logic_gate[0] = nullptr;
        }

        if (key_pressed)
        {
            // Check if the new position is occupied
            if (!is_grid_occupied(circuit, new_position))
            {
                // Update the position if the new grid is not occupied
                selected_logic_gate[0]->bd.x = new_position.x;
                selected_logic_gate[0]->bd.y = new_position.y;
            }
            else
            {
                std::cout << "Move blocked: grid is occupied!" << std::endl;
            }
        }
    }

    Rectangle CalculateRegion(Rectangle rect, float xStartRatio, float xEndRatio, float yStartRatio,
                              float yEndRatio)
    {
        float xLower = rect.x + rect.width * xStartRatio;
        float xUpper = rect.x + rect.width * xEndRatio;
        float yLower = rect.y + rect.height * yStartRatio;
        float yUpper = rect.y + rect.height * yEndRatio;

        return {xLower, yLower, xUpper - xLower, yUpper - yLower};
    }
    Vector2 SnapToNearestGrid(const Rectangle& rect)
    {
        Vector2 nearest_grid_point;
        nearest_grid_point.x = std::round(rect.x / SPACING_SIZE) * SPACING_SIZE;
        nearest_grid_point.y = std::round(rect.y / SPACING_SIZE) * SPACING_SIZE;
        // TODO: Highlight the nearest grid point
        return nearest_grid_point;
    }

    void HandleMouseLeftClick(std::shared_ptr<CircuitElements::Circuit> circuit,
                              const Vector2& mousePosition)
    {
        bool gateSelected = false;
        if (!is_logic_selected)  // the default system goes when not doing wiring
        {
            CircuitElements::Connection connection_start = {};
            for (const auto& gate : circuit->gates)
            {
                if (CheckCollisionPointRec(mousePosition, gate->bd))
                {
                    HandleGateSelection(gate, mousePosition);
                    CheckGatePartClicked(circuit, gate, mousePosition, connection_start);
                    gateSelected = true;
                    if (connection_start.sourceLogic != "")  // not intitialized
                    {
                        circuit->connections.push_back(connection_start);
                    }
                    if (is_logic_selected)
                    {
                        Rectangle pos = {mousePosition.x, mousePosition.y, 0, 0};
                        circuit->active_wire.start = SnapToNearestGrid(pos);
                        circuit->active_wire.is_visible = true;
                    }
                    break;
                }
            }
            // if still not wiring
            if (!is_logic_selected)
            {
                CircuitElements::Connection con;
                is_logic_selected = CheckNearWire(circuit, mousePosition, con);
                if (is_logic_selected)  // this section checks what happens when you touch a wire
                {
                    Rectangle pos = {mousePosition.x, mousePosition.y, 0, 0};
                    circuit->active_wire.start = SnapToNearestGrid(pos);
                    circuit->active_wire.is_visible = true;
                    // get which line it belongs to
                    CircuitElements::Connection new_connection;
                    new_connection.sourceGate = con.sourceGate;
                    new_connection.sourceLogic = con.sourceLogic;
                    new_connection.physCon.wires.push_back(mousePosition);
                    circuit->connections.push_back(new_connection);
                }
            }
        }
        else
        {
            HandleLogicWiring(circuit, mousePosition);
        }
        // TODO: Deselect the gate if no gate was clicked
        if (!gateSelected)
        {
            selected_logic_gate[0] = nullptr;
        }
    }
    void HandleMouseRightClick(std::shared_ptr<CircuitElements::Circuit>& circuit,
                               const Vector2& mousePosition)
    {
        is_logic_selected = false;  // kills wiring process for sure everytime
        circuit->active_wire.is_visible = false;
    }
    void HandleLogicWiring(std::shared_ptr<CircuitElements::Circuit> circuit,
                           const Vector2& mousePosition)
    {
        Rectangle mockRec = {mousePosition.x, mousePosition.y, 0, 0};
        Vector2 nearest_grid_point = SnapToNearestGrid(mockRec);
        Vector2 wire_prev =
            circuit->connections[circuit->connections.size() - 1].physCon.wires
                [circuit->connections[circuit->connections.size() - 1].physCon.wires.size() - 1];
        Vector2 straight_line = Generate_straight_lines(wire_prev, nearest_grid_point);
        circuit->connections[circuit->connections.size() - 1].physCon.wires.push_back(
            straight_line);
        circuit->connections[circuit->connections.size() - 1].physCon.wires.push_back(
            nearest_grid_point);

        // finish if we hit logic gates
        CircuitElements::Connection connection_end;
        for (const auto& gate : circuit->gates)
        {
            if (CheckCollisionPointRec(mousePosition, gate->bd))
            {
                CheckGatePartClicked(circuit, gate, mousePosition, connection_end);
                if (connection_end.sourceLogic != "")  // not intitialized
                {
                    circuit->connections[circuit->connections.size() - 1].targetGate =
                        connection_end.sourceGate;
                    circuit->connections[circuit->connections.size() - 1].targetLogic =
                        connection_end.sourceLogic;
                    circuit->connections[circuit->connections.size() - 1].is_connected = true;
                    is_logic_selected = false;
                    circuit->active_wire.is_visible = false;
                }
                break;
            }
        }
        if (is_logic_selected)
        {
            Rectangle pos = {mousePosition.x, mousePosition.y, 0, 0};
            circuit->active_wire.start = SnapToNearestGrid(pos);
            circuit->active_wire.is_visible = true;
        }
    }
    void HandleGateSelection(const std::shared_ptr<LogicElements::LogicGate>& gate,
                             const Vector2& mousePosition)
    {
        selected_logic_gate[0] = gate;
        gate_initial_position = {gate->bd.x, gate->bd.y};
        offset.x = mousePosition.x - gate->bd.x;
        offset.y = mousePosition.y - gate->bd.y;
    }
    void CheckGatePartClicked(std::shared_ptr<CircuitElements::Circuit> circuit,
                              const std::shared_ptr<LogicElements::LogicGate>& gate,
                              const Vector2& mousePosition, CircuitElements::Connection& connection)
    {
        auto inputTopRegion = CalculateRegion(gate->bd, 0.05, 0.15, 0.2, 0.3);
        auto inputBottomRegion = CalculateRegion(gate->bd, 0.05, 0.15, 0.7, 0.8);
        auto outputRegion = CalculateRegion(gate->bd, 0.85, 0.95, 0.45, 0.55);

        // TODO after dynamic input this should change
        if (CheckCollisionPointRec(mousePosition, inputTopRegion))
        {
            control_logger.info("Input Top Clicked");
            is_logic_selected = true;
            connection.sourceGate = gate;
            connection.sourceLogic = "A";
            Vector2 pos = {inputTopRegion.x, inputTopRegion.y};
            connection.physCon.wires.push_back(pos);
        }
        else if (CheckCollisionPointRec(mousePosition, inputBottomRegion))
        {
            control_logger.info("Input Bottom Clicked");
            is_logic_selected = true;
            connection.sourceGate = gate;
            connection.sourceLogic = "B";
            Vector2 pos = {inputBottomRegion.x, inputBottomRegion.y};
            connection.physCon.wires.push_back(pos);
        }
        else if (CheckCollisionPointRec(mousePosition, outputRegion))
        {
            control_logger.info("Output clicked");
            is_logic_selected = true;
            connection.sourceGate = gate;
            connection.sourceLogic = "Out";
            Vector2 pos = {outputRegion.x, outputRegion.y};
            connection.physCon.wires.push_back(pos);
        }
    }
    bool CheckNearWire(std::shared_ptr<CircuitElements::Circuit> circuit,
                       const Vector2& mousePosition, CircuitElements::Connection& con)
    {
        for (size_t i = 0; i < circuit->connections.size(); i++)
        {
            for (size_t j = 0; j < circuit->connections[i].physCon.wires.size() - 1; j++)
            {
                Vector2 start = circuit->connections[i].physCon.wires[j];
                Vector2 end = circuit->connections[i].physCon.wires[j + 1];
                Rectangle col = {0, 0, 0, 0};
                if (std::abs(end.x - start.x) < SPACING_SIZE)
                {
                    col = {start.x - MOUSE_SELECTION_OFFSET, start.y,
                           SPACING_SIZE + MOUSE_SELECTION_OFFSET, std::abs(end.y - start.y)};
                }
                else if (std::abs(end.y - start.y) < SPACING_SIZE)
                {
                    col = {start.x, start.y + -MOUSE_SELECTION_OFFSET, std::abs(end.x - start.x),
                           SPACING_SIZE + MOUSE_SELECTION_OFFSET};
                }
                if (CheckCollisionPointRec(mousePosition, col))
                {
                    con = circuit->connections[i];
                    return true;
                }
            }
        }
        return false;
    }
    void HandleMouseDrag(std::shared_ptr<CircuitElements::Circuit> circuit,
                         const Vector2& mousePosition)
    {
        if (selected_logic_gate[0])
        {
            is_dragging = true;
            selected_logic_gate[0]->bd.x = mousePosition.x - offset.x;
            selected_logic_gate[0]->bd.y = mousePosition.y - offset.y;
            // check the connections
            for (size_t i = 0; i < circuit->connections.size(); i++)
            {
                // !!! for now this gives the same location as the BB, but when resolved it will
                // allow us to move wires with gates
                // TODO
                if (circuit->connections[i].sourceGate == selected_logic_gate[0])
                {
                    circuit->connections[i].physCon.wires[0].x = mousePosition.x - offset.x;
                    circuit->connections[i].physCon.wires[0].y = mousePosition.y - offset.y;
                }
                if (circuit->connections[i].targetGate == selected_logic_gate[0])
                {
                    int size = circuit->connections[i].physCon.wires.size() - 1;
                    circuit->connections[i].physCon.wires[size].x = mousePosition.x - offset.x;
                    circuit->connections[i].physCon.wires[size].y = mousePosition.y - offset.y;
                }
            }
        }
    }

    void HandleMouseRelease(std::shared_ptr<CircuitElements::Circuit> circuit)
    {
        if (selected_logic_gate[0])
        {
            Vector2 nearest_grid_point = SnapToNearestGrid(selected_logic_gate[0]->bd);

            if (!is_grid_occupied(circuit, nearest_grid_point))
            {
                selected_logic_gate[0]->bd.x = nearest_grid_point.x;
                selected_logic_gate[0]->bd.y = nearest_grid_point.y;
            }
            else
            {
                // Reset to initial position if grid is occupied
                selected_logic_gate[0]->bd.x = gate_initial_position.x;
                selected_logic_gate[0]->bd.y = gate_initial_position.y;
            }

            is_dragging = false;
        }
    }

    void Controls_Mouse_click()
    {

        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            HandleMouseLeftClick(selected_circuit, mouse_pos);
        }

        if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT))
        {
            HandleMouseRightClick(selected_circuit, mouse_pos);
        }

        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
        {
            HandleMouseDrag(selected_circuit, mouse_pos);
        }

        if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
        {
            HandleMouseRelease(selected_circuit);
        }
    }

    bool is_grid_occupied(std::shared_ptr<CircuitElements::Circuit> circuit,
                          Vector2 nearest_grid_point)
    {
        // Check if the nearest grid point is occupied by any gate other than the selected gate.
        if (selected_logic_gate.empty() || !selected_logic_gate[0])
        {
            std::cerr << "Error: selected_logic_gate is empty!" << std::endl;
            return true;  // Assume grid is occupied if no gate is selected.
        }

        // Calculate the bounding box of the gate being placed
        float new_gate_x_start = nearest_grid_point.x;
        float new_gate_y_start = nearest_grid_point.y;
        float new_gate_x_end = nearest_grid_point.x + selected_logic_gate[0]->bd.width;
        float new_gate_y_end = nearest_grid_point.y + selected_logic_gate[0]->bd.height;

        for (auto gate : circuit->gates)
        {
            // Skip the currently selected logic gate
            if (gate == selected_logic_gate[0])
            {
                continue;
            }
            // Get the bounding box of the existing gate
            float existing_gate_x_start = gate->bd.x;
            float existing_gate_y_start = gate->bd.y;
            float existing_gate_x_end = gate->bd.x + gate->bd.width;
            float existing_gate_y_end = gate->bd.y + gate->bd.height;

            // Check for overlap between the new gate's bounding box and the existing gate's
            // bounding box
            if (!(new_gate_x_end <=
                      existing_gate_x_start ||  // New gate is to the left of the existing gate
                  new_gate_x_start >=
                      existing_gate_x_end ||  // New gate is to the right of the existing gate
                  new_gate_y_end <= existing_gate_y_start ||  // New gate is above the existing gate
                  new_gate_y_start >= existing_gate_y_end))   // New gate is below the existing gate
            {
                return true;  // Overlap detected, grid is occupied
            }
        }
        return false;  // No overlap detected, grid is not occupied
    }
    Vector2 Generate_straight_lines(const Vector2& start, const Vector2& end)
    {
        Vector2 vec1 = {start.x, start.y};
        if (start.x != end.x && start.y != end.y)
        {
            vec1 = {end.x, start.y};
        }
        return vec1;
    }
}  // namespace Controls
