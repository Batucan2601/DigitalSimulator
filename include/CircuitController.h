#pragma once
#include "LogicElements/LogicElements.h"
#include "Commands.h"
#include "SelectionHandler.h"
class CircuitController : public IInputHandler, public std::enable_shared_from_this<CircuitController>{
    public:
        CircuitController(std::string logger_name = "circuit");
        SP_Circuit getCircuit() const;
        std::shared_ptr<SelectionTool> getMultiSelector() const;
        void setCircuit(SP_Circuit circuit);
        void addComponent(std::shared_ptr<Component> component);
        void removeComponent(std::shared_ptr<Component> component);
        void moveComponent(std::shared_ptr<Component> component , Vector2 oldPosition,
        Vector2 newPosition);
        void addConnection( std::shared_ptr<Component> srcComp,
        std::shared_ptr<Component> targetComp, std::string sourceString , std::string targetString);
    protected:
        virtual void OnKeyPress(const InputEvent& event);
        virtual void OnInputEvent( InputEvent& event);
    private:
    SP_Circuit circuit;
    std::unique_ptr<Command::UndoManager> undoManager;
    std::shared_ptr<SelectionTool> multiSelection; 
};