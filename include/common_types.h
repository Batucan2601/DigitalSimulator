#ifndef COMMON_TYPES_H
#define COMMON_TYPES_H

// #define SLICE_SIZE 100
// #define SPACING_SIZE    25
// #define MOUSE_SELECTION_OFFSET   SPACING_SIZE / 2
// #define GRID_POINT_SIZE          3
#define WIRE_INTERACT_POINT_SIZE 8
#define LINE_THICKNESS           5

typedef std::shared_ptr<CircuitElements::Circuit> SP_Circuit;
typedef std::shared_ptr<Component> SP_Component;

#endif  // COMMON_TYPES_H