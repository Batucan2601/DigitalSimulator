#ifndef MAIN_H
#define MAIN_H

// Include necessary libraries
#include "Controls.h"
#include "GUI/GUIEditor.h"
#include "LogicElements.h"
#include "LogicElementsDraw.h"
#include "appSettings.h"
#include "common_types.h"
#include "logicElementFactory.h"
#include "raylib.h"
#include "raylibHelper.h"

#include <iostream>
// Function declarations
extern std::shared_ptr<CircuitElements::Circuit> circuit;

void setLoadedCircuit(std::shared_ptr<CircuitElements::Circuit> loadedCircuit);

#endif  // MAIN_H