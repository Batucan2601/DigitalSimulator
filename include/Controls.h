#ifndef CONTROLS_H
#define CONTROLS_H
#include "ClassLogger.h"
#include "LogicElements.h"
#include "common_types.h"
#include "raylib.h"

#include <cmath>

namespace Controls
{
    void Controls_set_camera(unsigned int screen_width, unsigned int screen_height);
    void Controls_update(std::shared_ptr<CircuitElements::Circuit> circuit);

    bool is_grid_occupied(std::shared_ptr<CircuitElements::Circuit> circuit, Vector2 nearest_grid_point);
    Camera2D Controls_get_camera();

    // mouse
    void Controls_Mouse_click();
    void Controls_Handle_Continous(std::shared_ptr<CircuitElements::Circuit> circuit);

    void HandleGateSelection(const std::shared_ptr<LogicElements::LogicGate> &gate, const Vector2 &mousePosition);
    void CheckGatePartClicked(std::shared_ptr<CircuitElements::Circuit> circuit, const std::shared_ptr<LogicElements::LogicGate> &gate, const Vector2 &mousePosition,
                              CircuitElements::Connection &connection);
    Rectangle CalculateRegion(Rectangle rect, float xStartRatio, float xEndRatio, float yStartRatio,
                              float yEndRatio);
    void HandleMouseDrag(std::shared_ptr<CircuitElements::Circuit> circuit, const Vector2 &mousePosition);
    Vector2 SnapToNearestGrid(const Rectangle &rect);
    void HandleMouseRelease(std::shared_ptr<CircuitElements::Circuit> circuit);
    void HandleLogicWiring(std::shared_ptr<CircuitElements::Circuit> circuit, const Vector2 &mousePosition);
    // keyboard
    void Control_Keyboard_Event(std::shared_ptr<CircuitElements::Circuit> circuit);
    Vector2 Generate_straight_lines(const Vector2 &start, const Vector2 &end);
    // TODO this does not belong here
    bool CheckNearWire(std::shared_ptr<CircuitElements::Circuit> circuit, const Vector2 &mousePosition, CircuitElements::Connection &con);
} // namespace Controls

#endif