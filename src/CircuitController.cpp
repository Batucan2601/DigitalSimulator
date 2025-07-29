#include "CircuitController.h"

CircuitController::CircuitController(std::string logger_name)
    : circuit(std::make_shared<CircuitElements::Circuit>(logger_name)),
      undoManager(std::make_unique<Command::UndoManager>())
{

}

SP_Circuit CircuitController::getCircuit() const
{
    return circuit;
}

void CircuitController::addComponent(std::shared_ptr<Component> component)
{
    if (component)
    {
        circuit->addGate(component);
        undoManager->execute(std::make_unique<Command::AddComponentCommand>(circuit, component));
    }
}

void CircuitController::removeComponent(std::shared_ptr<Component> component)
{
    if (component)
    {
        // Create a command to remove the component
        auto removeCommand = std::make_unique<Command::RemoveComponentCommand>(circuit, component);
        removeCommand->undo();  // Remove the component from the circuit
        undoManager->execute(std::move(removeCommand));
    }
}


void CircuitController::moveComponent(std::shared_ptr<Component> component, Vector2 oldPosition, Vector2 newPosition)
{
    if (component)
    {
        // Create a command to move the component
        auto moveCommand = std::make_unique<Command::MoveComponentCommand>(component, oldPosition, newPosition);
        moveCommand->redo();  // Move the component to the new position
        undoManager->execute(std::move(moveCommand));
    }
}