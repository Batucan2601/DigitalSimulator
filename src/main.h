#ifndef MAIN_H
#define MAIN_H

// Include necessary libraries
#include "Controls.h"
#include "GUI/GUIEditor.h"
#include "LogicElements.h"
#include "LogicElementsDraw.h"
#include "common_types.h"
#include "logicElementFactory.h"
#include "raylib.h"
#include "raylibHelper.h"

#include <iostream>
// Function declarations
std::shared_ptr<CircuitElements::Circuit> circuit;

#endif  // MAIN_H