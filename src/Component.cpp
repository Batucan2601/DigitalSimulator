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

void Component::allocateConnection()
{
    this->connections.reserve(1000);
    this->components.reserve(1000);
}
void Component::Draw()
{
    for (size_t i = 0; i < this->components.size(); i++)
    {
        this->components[i]->Draw();
    }
}

void Component::addComponent(const std::shared_ptr<Component>& comp)
{
    this->components.push_back(comp);
    InputResolver::RegisterHandler((IInputHandler*)comp.get()); // TODO get a better place 
}
const std::vector<Signal>& Component::getInputs() const
{
    return inputs;
}
const std::vector<Signal>& Component::getOutputs() const
{
    return outputs;
}
void Component::evaluate()
{
    for (size_t i = 0; i < this->components.size(); i++)
    {
        this->components[i]->evaluate();
    }
}

int Component::getID() const
{
    return id; 
}

void Component::setInput(const std::string& name, bool value)
{
    for (auto& I : this->inputs)
    {
        if (I.name == name)
        {
            I.val = value;
            //notifyObservers();
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

void Component::addConnection(const CircuitElements::Connection& con)
{
    this->connections.push_back(con);
}