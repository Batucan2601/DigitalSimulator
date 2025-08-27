#pragma once
#include "LogicElements/LogicElements.h"
#include "Commands.h"
#include "SelectionHandler.h"
class CircuitController : public IInputHandler, public std::enable_shared_from_this<CircuitController>{
    public:
    static std::shared_ptr<CircuitController> create(std::string logger_name) {
        auto controller = std::shared_ptr<CircuitController>(
            new CircuitController(logger_name)
        );
        controller->postInit();
        return controller;
        }
        void postInit() {
        InputResolver::RegisterHandler(shared_from_this());
        InputResolver::RegisterHandler(multiSelection);
        }
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
        CircuitController(std::string logger_name = "circuit");
        virtual void OnKeyPress(const InputEvent& event);
        virtual void OnInputEvent( InputEvent& event);
    private:
    SP_Circuit circuit;
    std::unique_ptr<Command::UndoManager> undoManager;
    std::shared_ptr<SelectionTool> multiSelection; 
};