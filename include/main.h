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
extern SP_Circuit circuit;

void setLoadedCircuit(SP_Circuit loadedCircuit);

#endif  // MAIN_H