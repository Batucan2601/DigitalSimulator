#ifndef CONTROLS_H
#define CONTROLS_H
#include "raylib.h"
#include "LogicElements.h"

void Controls_set_camera(unsigned int screen_width, unsigned int screen_height);
void Controls_update(std::shared_ptr<Circuit> circuit);
Camera2D Controls_get_camera();

// mouse
void Controls_Mouse_click();
#endif 