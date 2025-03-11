#include "Controls.h"

#include "Component.h"
#include "GUI/BaseWindow.h"
#include "GUI/GUIEditor.h"
#include "GUI/Tools.h"
#include "LogicElementBase.h"
#include "LogicElements.h"
#include "logicElementFactory.h"
#include "raylib.h"
#include "raylibHelper.h"

#include <iostream>
#include <memory>
#include <queue>

namespace Controls
{

    static Camera2D camera = {};
    // since we draw raylib inside a texture and pass it to imgui we need a transform.
    static void ConvertMouseCoord(Vector2& mouse_pos)
    {
        auto* base_window = RaylibHelper::getGUIWindow("Editor");

        if (!base_window)
        {
            std::cerr << "Error: Editor window not found!" << std::endl;
            return;
        }

        auto* editor_window = dynamic_cast<GUI::Editor*>(base_window);

        if (!editor_window)
        {
            std::cerr << "Error: dynamic_cast failed! Object is not of type Editor." << std::endl;
            return;
        }

        // Correct way to access ImageMin
        Vector2 virtualMouse;
        virtualMouse.x = (mouse_pos.x - editor_window->m_editor_render.window.ImageMin.x);
        virtualMouse.y = (mouse_pos.y - editor_window->m_editor_render.window.ImageMin.y);

        mouse_pos = GetScreenToWorld2D(virtualMouse, camera);
    }
    std::string control_logger_name = "ControlLogger";
    std::string gui_circuit_logger = "GUICircuitLogger";
    static ClassLogger control_logger(control_logger_name);
    static auto selected_circuit = std::make_shared<CircuitElements::Circuit>(gui_circuit_logger);
    std::vector<std::shared_ptr<LogicElements::LogicGate>> selected_logic_gate(1);
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

    void Controls_update(SP_Circuit circuit)
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

        mouse_pos = GetMousePosition();
        ConvertMouseCoord(mouse_pos);

        // get data
        selected_circuit = circuit;

        Controls_Mouse_click();
        Controls_Mouse_Movements();
        Control_Keyboard_Event();
        // Controls_Handle_Continous(selected_circuit);

        InputResolver::resolve();
    }

    Camera2D Controls_get_camera()
    {
        return camera;
    }

    void Controls_Handle_Continous(SP_Circuit circuit)
    {
        // Get mouse position
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
            // circuit->m_logger.info("catched new ");
        }

        if (GUI::dragDrop.state == GUI::DragDropState::DRAGGING)
        {
            Rectangle rec = {mouse_pos.x, mouse_pos.y, 0, 0};
            Vector2 pos = SnapToNearestGrid(rec);
            circuit->selected_wires.wire_hovering = pos;
            // circuit->m_logger.info("catched new ");
            circuit->is_GUIdragdragging = true;
        }
        if (circuit->is_GUIdragdragging && GUI::dragDrop.state == GUI::DragDropState::IDLE)
        {
            circuit->is_GUIdragdropped = true;
            circuit->is_GUIdragdragging = false;

            // add the new circuit
            std::string new_gate = "or_gate_logger";
            std::shared_ptr<LogicElements::LogicGate> gate = circuit->factory.createGate(GUI::dragDrop.gateType, new_gate);
            circuit->getMainComponent()->addComponent(gate);
            if (GUI::dragDrop.gateType != LogicElements::GateType::NONE)
            {
                circuit->getMainComponent()->components[circuit->getMainComponent()->components.size() - 1]->setPosition(
                    circuit->selected_wires.wire_hovering.x,
                    circuit->selected_wires.wire_hovering.y);
                GUI::dragDrop.gateType = LogicElements::GateType::NONE;
            }
        }
    }

    void Control_Keyboard_Event()
    {
        if (selected_logic_gate.empty() || !selected_logic_gate[0])
        {
            // std::cerr << "Error: No selected logic gate!" << std::endl;
            // control_logger.info("Error: No selected logic gate!");
            return;
        }

        std::cout << "Keyboard event" << std::endl;

        // Store the current position of the selected logic gate
        float current_x = selected_logic_gate[0]->bd.x;
        float current_y = selected_logic_gate[0]->bd.y;
        // float gate_width = selected_logic_gate[0]->bd.width;
        // float gate_height = selected_logic_gate[0]->bd.height;

        Vector2 new_position = {current_x, current_y};

        // Adjust the position based on keyboard input
        // bool key_pressed = false;
        if (IsKeyPressed(KEY_UP))
        {
            // key_pressed = true;
            new_position.y -= appSettings.SPACING_SIZE;
        }
        if (IsKeyPressed(KEY_DOWN))
        {
            // key_pressed = true;
            new_position.y += appSettings.SPACING_SIZE;
        }
        if (IsKeyPressed(KEY_LEFT))
        {
            // key_pressed = true;
            new_position.x -= appSettings.SPACING_SIZE;
        }
        if (IsKeyPressed(KEY_RIGHT))
        {
            // key_pressed = true;
            new_position.x += appSettings.SPACING_SIZE;
        }
        if (IsKeyPressed(KEY_ESCAPE))
        {
            is_logic_selected = false;  // kills wiring process for sure everytime
            // circuit->active_wire.is_visible = false;
        }

        if (IsKeyPressed(KEY_DELETE))
        {
            InputEvent event;
            event.type = InputType::Keyboard;
            event.keyState = KeyboardEvent::KeyPress;
            event.keyCode = KEY_DELETE;
            InputResolver::PushEvent(event);
            std::cout << "Key pressed: DELETE" << std::endl;
            // // delete the selected gate
            // for (size_t i = 0; i < circuit->gates.size(); i++)
            // {
            //     if (circuit->gates[i] == selected_logic_gate[0])
            //     {
            //         circuit->gates.erase(circuit->gates.begin() + i);
            //         break;
            //     }
            // }
            // // delete the connections
            // for (size_t i = 0; i < circuit->connections.size(); i++)
            // {
            //     // if (circuit->connections[i].sourceGate == selected_logic_gate[0] ||
            //     //     circuit->connections[i].targetGate == selected_logic_gate[0])
            //     {
            //         circuit->connections.erase(circuit->connections.begin() + i);
            //         i--;
            //     }
            // }
            // selected_logic_gate[0] = nullptr;
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
        nearest_grid_point.x =
            std::round(rect.x / appSettings.SPACING_SIZE) * appSettings.SPACING_SIZE;
        nearest_grid_point.y =
            std::round(rect.y / appSettings.SPACING_SIZE) * appSettings.SPACING_SIZE;
        // TODO: Highlight the nearest grid point
        return nearest_grid_point;
    }

    void HandleMouseLeftClick(SP_Circuit circuit, const Vector2& mousePosition)
    {
        InputEvent event;
        event.type = InputType::Mouse;
        event.mouseState = MouseEventState::LeftClick;
        event.pos = {(int)mousePosition.x, (int)mousePosition.y};
        InputResolver::PushEvent(event);
        return;
    }

    void HandleMouseEnter(SP_Circuit circuit, const Vector2& mousePosition)
    {
        (void)circuit;
        InputEvent event;
        event.type = InputType::Mouse;
        event.mouseState = MouseEventState::Enter;
        event.pos = {(int)mousePosition.x, (int)mousePosition.y};
        InputResolver::PushEvent(event);
    }

    void HandleMouseExit(SP_Circuit circuit, const Vector2& mousePosition)
    {
        (void)circuit;

        InputEvent event;
        event.type = InputType::Mouse;
        event.mouseState = MouseEventState::Leave;
        event.pos = {(int)mousePosition.x, (int)mousePosition.y};
        InputResolver::PushEvent(event);
    }

    void HandleMouseRightClick(SP_Circuit& circuit, const Vector2& mousePosition)
    {
        InputEvent event;
        event.type = InputType::Mouse;
        event.mouseState = MouseEventState::RightClick;
        event.pos = {(int)mousePosition.x, (int)mousePosition.y};
        InputResolver::PushEvent(event);

        is_logic_selected = false;  // kills wiring process for sure everytime
        circuit->active_wire.is_visible = false;
    }
    void HandleGateSelection(const std::shared_ptr<LogicElements::LogicGate>& gate,
                             const Vector2& mousePosition)
    {
        selected_logic_gate[0] = gate;
        gate_initial_position = {gate->bd.x, gate->bd.y};
        offset.x = mousePosition.x - gate->bd.x;
        offset.y = mousePosition.y - gate->bd.y;
    }
    void CheckGatePartClicked(SP_Circuit circuit,
                              const std::shared_ptr<LogicElements::LogicGate>& gate,
                              const Vector2& mousePosition, CircuitElements::Connection& connection)
    {
        (void)circuit;

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
    bool CheckNearWire(SP_Circuit circuit, const Vector2& mousePosition,
                       CircuitElements::Connection& con)
    {
        for (size_t i = 0; i < circuit->connections.size(); i++)
        {
            for (size_t j = 0; j < circuit->connections[i].physCon.wires.size() - 1; j++)
            {
                Vector2 start = circuit->connections[i].physCon.wires[j];
                Vector2 end = circuit->connections[i].physCon.wires[j + 1];
                Rectangle col = {0, 0, 0, 0};
                if (std::abs(end.x - start.x) < appSettings.SPACING_SIZE)
                {
                    col = {start.x - appSettings.MOUSE_SELECTION_OFFSET, start.y,
                           (float)(appSettings.SPACING_SIZE + appSettings.MOUSE_SELECTION_OFFSET),
                           std::abs(end.y - start.y)};
                }
                else if (std::abs(end.y - start.y) < appSettings.SPACING_SIZE)
                {
                    col = {start.x, start.y + -appSettings.MOUSE_SELECTION_OFFSET,
                           std::abs(end.x - start.x),
                           (float)(appSettings.SPACING_SIZE + appSettings.MOUSE_SELECTION_OFFSET)};
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
    void HandleMouseDrag(SP_Circuit circuit, const Vector2& mousePosition)
    {
        (void)circuit;
        InputEvent event;
        event.type = InputType::Mouse;
        event.mouseState = MouseEventState::Down;
        event.pos = {(int)mousePosition.x, (int)mousePosition.y};
        InputResolver::PushEvent(event);
    }

    void HandleMouseRelease(SP_Circuit circuit)
    {
        (void)circuit;

        InputEvent event;
        event.type = InputType::Mouse;
        event.mouseState = MouseEventState::Release;
        event.pos = {(int)mouse_pos.x, (int)mouse_pos.y};
        InputResolver::PushEvent(event);
    }

    void Controls_Mouse_Movements()
    {
        InputEvent event;
        event.type = InputType::Mouse;
        event.mouseState = MouseEventState::Move;
        event.pos = {(int)mouse_pos.x, (int)mouse_pos.y};
        InputResolver::PushEvent(event);
    }

    static float holdTime = 0.0f;
    const float delayThreshold = 0.08f;  // Delay in seconds (e.g., 0.5 seconds)
    void Controls_Mouse_click()
    {
        // mouse always moves
        InputEvent event;
        event.type = InputType::Mouse;
        event.mouseState = MouseEventState::Move;
        event.pos = {(int)mouse_pos.x, (int)mouse_pos.y};
        InputResolver::PushEvent(event);

        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            holdTime = 0.0f;
            HandleMouseLeftClick(selected_circuit, mouse_pos);
        }

        if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT))
        {
            HandleMouseRightClick(selected_circuit, mouse_pos);
        }

        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
        {
            holdTime += GetFrameTime();  // Accumulate elapsed time
            if (holdTime >= delayThreshold)
            {
                HandleMouseDrag(selected_circuit, mouse_pos);
            }
        }

        if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
        {
            holdTime += GetFrameTime();  // Accumulate elapsed time
            if (holdTime >= delayThreshold)
            {
                HandleMouseRelease(selected_circuit);
            }
        }
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
