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
    void Controls_update(SP_Circuit circuit);

    bool is_grid_occupied(SP_Circuit circuit, Vector2 nearest_grid_point);
    Camera2D Controls_get_camera();

    // mouse
    void Controls_Mouse_click();
    void Controls_Mouse_Movements();
    void Controls_Handle_Continous(SP_Circuit circuit);

    void HandleGateSelection(const std::shared_ptr<Component>& gate,
                             const Vector2& mousePosition);
    void CheckGatePartClicked(SP_Circuit circuit,
                              const std::shared_ptr<Component>& gate,
                              const Vector2& mousePosition,
                              CircuitElements::Connection& connection);
    Rectangle CalculateRegion(Rectangle rect, float xStartRatio, float xEndRatio, float yStartRatio,
                              float yEndRatio);
    void HandleMouseDrag(SP_Circuit circuit, const Vector2& mousePosition);
    void HandleMouseRelease(SP_Circuit circuit);
    void HandleLogicWiring(SP_Circuit circuit, const Vector2& mousePosition);
    // keyboard
    void Control_Keyboard_Event();
    Vector2 Generate_straight_lines(const Vector2& start, const Vector2& end);
    // TODO this does not belong here

}  // namespace Controls

#endif