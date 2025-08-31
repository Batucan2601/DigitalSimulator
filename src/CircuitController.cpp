#include "CircuitController.h"

CircuitController::CircuitController(std::string logger_name)
    : circuit(std::make_shared<CircuitElements::Circuit>(logger_name)),
      undoManager(std::make_unique<Command::UndoManager>()),
      multiSelection(std::make_shared<SelectionTool>(circuit))
{
}

SP_Circuit CircuitController::getCircuit() const
{
    return circuit;
}
std::shared_ptr<SelectionTool> CircuitController::getMultiSelector() const
{
    return multiSelection;
}
void CircuitController::setCircuit(SP_Circuit circuit)
{
    this->circuit = circuit;
    this->circuit->m_logger.info("Circuit set in CircuitController.");
}


void CircuitController::addComponent(std::shared_ptr<Component> component)
{
    if (component)
    {
        //circuit->addGate(component);
        undoManager->execute(std::make_unique<Command::AddComponentCommand>(circuit, component));
    }
}

void CircuitController::addConnection( std::shared_ptr<Component> srcComp,
        std::shared_ptr<Component> targetComp, std::string sourceString , std::string targetString)
{
    undoManager->execute(std::make_unique<Command::AddConnectionCommand>(circuit , srcComp, targetComp , sourceString,
    targetString));
}
void CircuitController::removeComponent(std::shared_ptr<Component> component)
{
    if (component && component->m_mark_for_deletion)
    {
        // Create a command to remove the component
        auto removeCommand = std::make_unique<Command::RemoveComponentCommand>(circuit, component);
        //removeCommand->undo();  // Remove the component from the circuit
        undoManager->execute(std::move(removeCommand));
        component->m_mark_for_deletion = false;
    }
}

void CircuitController::removeConnection( std::shared_ptr<CircuitElements::Connection> connection)
{
    auto removeCommand = std::make_unique<Command::RemoveConnectionCommand>(circuit, connection);
    undoManager->execute(std::move(removeCommand));
}


void CircuitController::moveComponent(std::shared_ptr<Component> component, Vector2 oldPosition, Vector2 newPosition)
{
    if (component)
    {
        // Create a command to move the component
        auto moveCommand = std::make_unique<Command::MoveComponentCommand>(circuit, component, oldPosition, newPosition);
        moveCommand->redo();  // Move the component to the new position
        undoManager->execute(std::move(moveCommand));
    }
}



void CircuitController::OnKeyPress(const InputEvent& event)
{
    if (event.keyCode == KeyboardKey::KEY_Z && event.keyState == KeyboardEvent::KeyPress)
    {
        undoManager->undo();
        circuit->m_logger.info("Undo last action.");
    }
    else if (event.keyCode == KeyboardKey::KEY_Y && event.keyState == KeyboardEvent::KeyPress)
    {
        undoManager->redo();
        circuit->m_logger.info("Redo last action.");
    }
    std::cout << "Pressed key code: " << event.keyCode << std::endl;

}


void CircuitController::OnInputEvent( InputEvent& event)
{
    if (event.type == InputType::Keyboard)
    {
        OnKeyPress(event);
    }
}
