#pragma once
#include "LogicElements/LogicElements.h"
#include "Commands.h"
class CircuitController {
    public:
        CircuitController(std::string logger_name = "circuit");
        SP_Circuit getCircuit() const;
        void addComponent(std::shared_ptr<Component> component);
        void removeComponent(std::shared_ptr<Component> component);
        void moveComponent(std::shared_ptr<Component> component , Vector2 oldPosition,
        Vector2 newPosition);
    private:
    SP_Circuit circuit;
    std::unique_ptr<Command::UndoManager> undoManager;
};