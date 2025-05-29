#include "Component.h"
// Define static members.
std::queue<InputEvent> InputResolver::queue;
std::list<IInputHandler*>
    InputResolver::handlers;  // I do not really know what thefuck that is about
IInputHandler* InputResolver::selectedHandler = nullptr;
void InputResolver::PushEvent(const InputEvent& event)
{
    queue.push(event);
}

void InputResolver::RegisterHandler(IInputHandler* handler)
{
    // Optionally check if the handler is already registered.
    handlers.push_back(handler);
}

void InputResolver::UnregisterHandler(IInputHandler* handler)
{
    // Remove handler from the vector.
    handlers.erase(std::remove(handlers.begin(), handlers.end(), handler), handlers.end());
}

void InputResolver::resolve()
{
    while (!queue.empty())
    {
        InputEvent event = queue.front();
        queue.pop();
        // Dispatch the event to all registered handlers.
        for (auto handler : handlers)
        {
            if (handler)
            {
                handler->OnInputEvent(event);
            }
        }
    }
}

void Component::OnInputEvent(const InputEvent& event)
{
    (void)event;
    // TODO: Implement the event handling logic here.
}

void Component::setPosition(float x, float y)
{
    this->bd.x = x;
    this->bd.y = y;
};  // TODO: Implement this

Vector2 Component::getPosition() const
{
    return {bd.x, bd.y};
}

CircuitElements::ComponentType Component::getType() const
{
    return m_type;
}

void Component::setInput(const std::string& name, bool value)
{
    for (auto& I : this->inputs)
    {
        if (I.name == name)
        {
            I.val = value;
            notifyObservers();
        }
    }
}

bool Component::getOutput(const std::string& name) const
{
    for (auto& it : this->outputs)
    {
        if (it.name == name)
        {
            return true;
        }
    }
    return false;
}
void Component::addObserver(LogicElements::GateObserver* observer)
{
    observers.insert(observer);
}

void Component::removeObserver(LogicElements::GateObserver* observer)
{
    observers.erase(observer);
}

void Component::notifyObservers()
{
    for (auto observer : observers)
    {
        observer->onInputChanged();
    }
}

const std::vector<Signal>& Component::getInputs() const
{
    return inputs;
}
const std::vector<Signal>& Component::getOutputs() const
{
    return outputs;
}

void Component::setEvaluationFunction(std::function<void(Component&)> evalFunc)
{
    evaluateFunction = evalFunc;
}

void Component::evaluate()
{
    if (evaluateFunction)
    {
        evaluateFunction(*this);
    }
}

int Component::getID() const
{
    return id;
}