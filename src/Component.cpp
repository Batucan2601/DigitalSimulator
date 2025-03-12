#include "Component.h"
#include "appSettings.h"
extern AppSettings::Settings appSettings;
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

void DrawInOut(std::shared_ptr<Component> gate)
{
    for (size_t i = 0; i < gate->outputs.size(); i++)
    {
        // GRID_POINT_SIZE
        Vector2 pos = gate->outputs[i].pos;
        Rectangle rec = { pos.x - appSettings.IN_OUT_RECT_WIDTH / 2,
                         pos.y - appSettings.IN_OUT_RECT_WIDTH / 2,
                         appSettings.IN_OUT_RECT_WIDTH, appSettings.IN_OUT_RECT_WIDTH };
        DrawRectangle(rec.x, rec.y, rec.width, rec.width, BLUE);
    }
    if (gate->is_hovered)
    {
        for (size_t i = 0; i < gate->inputs.size(); i++)
        {
            Vector2 pos = gate->inputs[i].pos;
            Rectangle rec = { pos.x - appSettings.IN_OUT_RECT_WIDTH / 2,
                             pos.y - appSettings.IN_OUT_RECT_WIDTH / 2,
                             appSettings.IN_OUT_RECT_WIDTH, appSettings.IN_OUT_RECT_WIDTH };
            DrawRectangle(rec.x, rec.y, rec.width, rec.width, BLUE);
        }
    }
}

void Component::Draw()
{
    for (size_t i = 0; i < this->components.size(); i++)
    {
        this->components[i]->Draw();
        DrawInOut(this->components[i]);
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