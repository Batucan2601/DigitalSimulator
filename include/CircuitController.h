#pragma once
#include "LogicElements/LogicElements.h"
#include "Commands.h"
class CircuitController : public IInputHandler, public std::enable_shared_from_this<CircuitController>{
    public:
        CircuitController(std::string logger_name = "circuit");
        SP_Circuit getCircuit() const;
        void setCircuit(SP_Circuit circuit);
        void addComponent(std::shared_ptr<Component> component);
        void removeComponent(std::shared_ptr<Component> component);
        void moveComponent(std::shared_ptr<Component> component , Vector2 oldPosition,
        Vector2 newPosition);
    protected:
        virtual void OnKeyPress(const InputEvent& event);
        virtual void OnInputEvent(const InputEvent& event);
    private:
    SP_Circuit circuit;
    std::unique_ptr<Command::UndoManager> undoManager;
};