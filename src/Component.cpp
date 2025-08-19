#include "Component.h"
#include "Commands.h"
#include "appSettings.h"
#include "LogicElements.h"
#include "Util/Utils.h"
#include "Controls.h"
#include "raylibHelper.h"
// Define static members.
std::queue<InputEvent> InputResolver::queue;
std::list<IInputHandler*>
    InputResolver::handlers;  // I do not really know what thefuck that is about
std::vector<IInputHandler*> InputResolver::selectedHandler;
bool InputResolver::m_blocked = false;
void InputResolver::Init()
{
    queue = std::queue<InputEvent>();
    m_blocked = false;
}
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
            if (handler && !m_blocked)
            {
                handler->OnInputEvent(event);
            }
        }
    }
}
void Component::setPosition(float x, float y)
{
    this->bd.x = x;
    this->bd.y = y;
    this->setInOutPositions();
};  // TODO: Implement this

Vector2 Component::getPosition() const
{
    return {bd.x, bd.y};
}

CircuitElements::ComponentType Component::getType() const
{
    return m_type;
}

void Component::setInput(const std::string& name, std::vector<SignalVal>  value)
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

std::vector<SignalVal> Component::getOutput(const std::string& name) const
{
    for (auto& it : this->outputs)
    {
        if (it.name == name)
        {
            return it.val;
        }
    }
    return std::vector<SignalVal>() = { SignalVal::SIGNAL_X };  // Return false if the output is not found
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

int Component::getInputByName(std::string name) const
{
    for (size_t i = 0; i < inputs.size(); i++)
    {
        if (inputs[i].name == name)
        {
            return i;
        }
    }
    return -1;  // Return -1 if the input is not found
}

int Component::getOutputByName(std::string name) const
{
    for (size_t i = 0; i < outputs.size(); i++)
    {
        if (outputs[i].name == name)
        {
            return i;
        }
    }
    return -1;  // Return -1 if the input is not found
}

int Component::getID() const
{
    return id;
}

void Component::OnInputEvent(InputEvent& event)
    {
        if (event.type == InputType::Mouse)
        {
            if (event.mouseState == MouseEventState::LeftClick)
            {
                OnLeftClick(event);
            }
            if (event.mouseState == MouseEventState::Release)
            {
                OnRelease(event);
            }
            if (event.mouseState == MouseEventState::RightClick)
            {
                OnRightClick(event);
            }
            if (event.mouseState == MouseEventState::Down)
            {
                OnDown(event);
            }
            if (event.mouseState == MouseEventState::Move)
            {
                OnMove(event);
            }
            if (event.mouseState == MouseEventState::Enter)
            {
                OnEnter(event);
            }
            if (event.mouseState == MouseEventState::Leave)
            {
                OnExit(event);
            }
        }

        if (event.type == InputType::Keyboard)
        {
            if (event.keyState == KeyboardEvent::KeyPress)
            {
                OnKeyPress(event);
            }
            if (event.keyState == KeyboardEvent::KeyRelease)
            {
                // OnKeyRelease(event);
            }
            if (event.keyState == KeyboardEvent::KeyRepeat)
            {
                // OnKeyRepeat(event);
            }
        }
}
bool Component::is_connection_clicked(const Vector2& mousePos,
                                        CircuitElements::Connection& possibleConnection)
{
    if (this->CheckMouseOnInOut(mousePos, possibleConnection))
    {
        return true;
    }
    return false;
}
void Component::OnLeftClick(const InputEvent& event)
{
    // check bb
    Vector2 pos = {(float)event.pos.x, (float)event.pos.y};
    bool isCol = CheckCollisionPointRec(pos, this->bd);
    if (!isCol)
    {
        return;
    }
    // ok first look at the selected handler, check if it is a logic gate
    CircuitElements::Connection possibleConnection;
    if (!circuit->active_wire.is_visible)  // we are not building a connection
    {
        // it cannot be a connection end
        // it can be a connection start, or gate select
        if (this->is_connection_clicked(pos, possibleConnection))
        {
            // if hits select it
            // possibleConnection.circuit = this->circuit;
            controller->addConnection(possibleConnection.sourceGate, possibleConnection.targetGate,
                possibleConnection.sourceLogic, possibleConnection.targetLogic);
            /*circuit->addConnection(
                possibleConnection.sourceGate, possibleConnection.sourceLogic,
                possibleConnection.targetGate, possibleConnection.targetLogic);*/
            circuit->active_wire.is_visible = true;
            circuit->active_wire.start = pos;
            circuit->active_wire.end = pos;
            InputResolver::RegisterHandler(
                static_cast<IInputHandler*>(&(circuit->active_wire)));
            std::vector<IInputHandler*>  handler = {&circuit->connections[circuit->connections.size() - 1]};
             
            InputResolver::setSelectedHandler(handler);
        }
        else  // select the gate
        {
            std::vector<IInputHandler*>  handler = {this};
            InputResolver::setSelectedHandler(handler);
        }
        return;
    }
    // check if a connection already selected.
    if( InputResolver::getSelectedHandler().size() != 1 )
    {
        return;
    }
    if (auto handler =
            dynamic_cast<CircuitElements::Connection*>(InputResolver::getSelectedHandler()[0]))
    {
        if (this->is_connection_clicked(pos, possibleConnection))
        {

            // the source should be output
            // the target should be an input
            bool is_output = false;
            bool is_input = false;
            for (size_t i = 0; i < handler->sourceGate->outputs.size(); i++)
            {
                if (handler->sourceGate->outputs[i].name == handler->sourceLogic)
                {
                    is_output = true;
                    break;
                }
            }
            for (size_t i = 0; i < possibleConnection.sourceGate->inputs.size(); i++)
            {
                if (possibleConnection.sourceGate->inputs[i].name ==
                    possibleConnection.sourceLogic)
                {
                    is_input = true;
                    break;
                }
            }
            if (is_output != is_input)  // if one is true one is false
            {
                return;
            }
            handler->targetGate = possibleConnection.sourceGate;
            handler->targetLogic = possibleConnection.sourceLogic;
            handler->is_connected = true;
            if (!is_output && !is_input)
            {
                std::shared_ptr<Component> temp_ptr = std::static_pointer_cast<Component>(handler->sourceGate);
                handler->sourceGate = handler->targetGate;
                handler->targetGate = temp_ptr;

                std::string temp_str = handler->sourceLogic;
                handler->sourceLogic = handler->targetLogic;
                handler->targetLogic = temp_str;
            }

            InputResolver::RegisterHandler(static_cast<IInputHandler*>(
                &circuit->connections[circuit->connections.size() - 1]));
        }
    }
    
}
void Component::OnRightClick(const InputEvent& event)
{
    (void)event;

    // check bb
    Vector2 pos = {(float)event.pos.x, (float)event.pos.y};
    bool isCol = CheckCollisionPointRec(pos, this->bd);
    if (!isCol)
    {
        //InputResolver::setSelectedHandler(nullptr);
        return;
    }
    std::vector<IInputHandler*> handler = {this}; 
    InputResolver::setSelectedHandler(handler);
    RaylibHelper::Show(4);

}
static Vector2 posBeforeDrag;
static bool isFirst = true;
static bool isDragging = false;
Vector2 dif;

void UpdateConnection(Component* gate)
{
    for (size_t i = 0; i < gate->circuit->connections.size(); i++)
    {
        CircuitElements::Connection* c = &gate->circuit->connections[i];
        if (c->sourceGate.get() == gate)
        {
            std::string name = c->sourceLogic;
            for (size_t j = 0; j < gate->outputs.size(); j++)
            {
                if (name == gate->outputs[j].name && c->physCon.wires.size() > 0)
                {
                 
                    Rectangle rec = {gate->outputs[j].pos.x, gate->outputs[j].pos.y, 0, 0};
                    Vector2 newPos = Utils::SnapToNearestGrid(rec);
                    Vector2 newLine =
                    Controls::Generate_straight_lines(newPos, c->physCon.wires[0]);
                    c->physCon.wires.insert(c->physCon.wires.begin(), newPos);
                    if (!(newLine.x == c->physCon.wires[0].x &&
                            newLine.y == c->physCon.wires[0].y))
                    {
                        c->physCon.wires.insert(c->physCon.wires.begin() + 1, newLine);
                    }
                }
            }
        }
        if (c->targetGate.get() == gate)
        {
            std::string name = c->targetLogic;
            for (size_t j = 0; j < gate->inputs.size(); j++)
            {
                if (name == gate->inputs[j].name)
                {
                    Rectangle rec = {gate->inputs[j].pos.x, gate->inputs[j].pos.y, 0, 0};
                    Vector2 newPos = Utils::SnapToNearestGrid(rec);
                    int last_index = c->physCon.wires.size() - 1;
                    if( last_index < 0 )
                    {
                        return;
                    }
                    Vector2 newLine =
                        Controls::Generate_straight_lines(newPos, c->physCon.wires[last_index]);
                    c->physCon.wires.push_back(newLine);
                    if (!(newLine.x == c->physCon.wires[last_index].x &&
                            newLine.y == c->physCon.wires[last_index].y))
                    {
                        c->physCon.wires.push_back(newPos);
                    }
                }
            }
        }
    }
}
void ReducePhysicalWires(Component* gate)
{
    for (size_t i = 0; i < gate->circuit->connections.size(); i++)
    {
        CircuitElements::Connection* c = &gate->circuit->connections[i];
        if (c->sourceGate.get() == gate || c->targetGate.get() == gate)
        {
            std::vector<unsigned int> indices_destroyed;
            for (int j = c->physCon.wires.size() - 1; j > 1; j--)
            {
                // Vector2 end = c->physCon.wires[j];
                Vector2 mid = c->physCon.wires[j - 1];
                Vector2 start = c->physCon.wires[j - 2];

                if (mid.x == start.x && mid.y == start.y)
                {
                    indices_destroyed.push_back(j - 1);
                }
            }
            for (size_t j = 0; j < indices_destroyed.size(); j++)
            {
                c->physCon.wires.erase(c->physCon.wires.begin() + indices_destroyed[j]);
            }
            indices_destroyed.clear();
            for (int j = c->physCon.wires.size() - 1; j > 1; j--)
            {
                Vector2 end = c->physCon.wires[j];
                Vector2 mid = c->physCon.wires[j - 1];
                Vector2 start = c->physCon.wires[j - 2];
                if ((mid.y == start.y && mid.y == end.y) ||
                    (mid.x == start.x && mid.x == end.x))
                {
                    indices_destroyed.push_back(j - 1);
                }
            }
            for (size_t j = 0; j < indices_destroyed.size(); j++)
            {
                c->physCon.wires.erase(c->physCon.wires.begin() + indices_destroyed[j]);
            }
        }
    }
}
void Component::OnDown(InputEvent& event)
{
    if(InputResolver::getSelectedHandler().size() != 1 )
    {
        return; 
    }
    if (this == InputResolver::getSelectedHandler()[0])
    {
        Vector2 mousePos = {(float)event.pos.x, (float)event.pos.y};

        if (!isDragging)
        {
            if (CheckCollisionPointRec(mousePos, this->bd))
            {
                isDragging = true;
                dif = {this->bd.x - event.pos.x, this->bd.y - event.pos.y};
            }
            else
            {
                return;
            }
        }
        event.consumed = true;
        Rectangle rec = {event.pos.x + dif.x, event.pos.y + dif.y, 0, 0};
        this->setPosition(rec.x, rec.y);
        if (isFirst)
        {
            posBeforeDrag = {rec.x, rec.y};
            isFirst = false;
        }
        // check the connections and their endpoints
        UpdateConnection(this);
        ReducePhysicalWires(this);
    }
}

void Component::OnRelease(const InputEvent& event)
{
    // if only one selected. 
    if( InputResolver::getSelectedHandler().size() != 1 )
    {
        return; 
    }
    if (this == InputResolver::getSelectedHandler()[0] )
    {
        if (!isDragging)
        {
            return;
        }
        Rectangle rec = {(float)event.pos.x, (float)event.pos.y, 0, 0};
        Vector2 v = Utils::SnapToNearestGrid(rec);
        bool is_other_gate_exist = false;
        for (auto val : InputResolver::handlers)
        {
            if (auto handler = dynamic_cast<Component*>(val))
            {
                if (handler == this)
                {
                    continue;
                }
                // Check for overlap between the new gate's bounding box and the existing gate's
                // bounding box
                if (CheckCollisionRecs(this->bd, handler->bd))
                {
                    is_other_gate_exist = true;  // Overlap detected, grid is occupied
                    break;
                }
            }
        }
        if (is_other_gate_exist)
        {
            this->setPosition(posBeforeDrag.x, posBeforeDrag.y);
        }
        else
        {
            rec.x = v.x + dif.x;
            rec.y = v.y + dif.y;
            Vector2 v = Utils::SnapToNearestGrid(rec);
            this->controller->moveComponent( shared_from_this(), posBeforeDrag, v);
        }
        isFirst = true;
        isDragging = false;
        ReducePhysicalWires(this);
    }
}
void Component::OnMove(const InputEvent& event)
{
    Vector2 mouse_pos = {(float)event.pos.x, (float)event.pos.y};
    CircuitElements::Connection temp;
    if (CheckMouseOnInOut(mouse_pos, temp))
    {
        // this should change the input color
    }
    bool currently_hovered = CheckCollisionPointRec(mouse_pos, this->bd);
    if (currently_hovered && !this->is_hovered)
    {
        this->is_hovered = true;
    }
    else if (!currently_hovered && this->is_hovered)
    {
        this->is_hovered = false;
    }
}

void Component::OnEnter(const InputEvent& event)
{
    // update the circuit->hoveredGate with this object
    (void)event;
 
    if (this == InputResolver::getSelectedHandler()[0] &&
        InputResolver::getSelectedHandler().size() == 1 )
    {
        circuit->hoveredGate = shared_from_this();
    }
}
void Component::OnExit(const InputEvent& event)
{
    (void)event;
    // update the circuit->hoveredGate with nullptr
}

void Component::OnKeyPress(const InputEvent& event)
{
    if (event.keyCode == KeyboardKey::KEY_DELETE)
    {
        std::vector<IInputHandler*> handlers = InputResolver::getSelectedHandler(); 
        for (size_t i = 0; i < handlers.size(); i++)
        {
            if (this == handlers[i])
            {
                this->m_mark_for_deletion = true; 
            }
        }
        this->controller->removeComponent(this->shared_from_this());
    }
}

bool Component::CheckMouseOnInOut(const Vector2& mousePosition,
                                    CircuitElements::Connection& connection)
{
    std::shared_ptr<Component> itself = shared_from_this();
    Rectangle rec;
    for (size_t i = 0; i < inputs.size(); i++)
    {
        rec.x = inputs[i].pos.x - AppSettings::appSettings.IN_OUT_RECT_WIDTH;
        rec.y = inputs[i].pos.y - AppSettings::appSettings.IN_OUT_RECT_WIDTH;
        rec.width = AppSettings::appSettings.IN_OUT_INTERACTION;
        rec.height = AppSettings::appSettings.IN_OUT_INTERACTION;
        if (CheckCollisionPointRec(mousePosition, rec))
        {
            connection.sourceGate = itself;
            connection.sourceLogic = inputs[i].name;
            Vector2 pos = {rec.x, rec.y};
            connection.physCon.wires.push_back(pos);
            return true;
        }
    }
    for (size_t i = 0; i < outputs.size(); i++)
    {
        rec.x = outputs[i].pos.x - AppSettings::appSettings.IN_OUT_RECT_WIDTH;
        rec.y = outputs[i].pos.y - AppSettings::appSettings.IN_OUT_RECT_WIDTH;
        rec.width = AppSettings::appSettings.IN_OUT_INTERACTION;
        rec.height = AppSettings::appSettings.IN_OUT_INTERACTION;
        if (CheckCollisionPointRec(mousePosition, rec))
        {
            connection.sourceGate = itself;
            connection.sourceLogic = outputs[i].name;
            Vector2 pos = {rec.x, rec.y};
            connection.physCon.wires.push_back(pos);
            return true;
        }
    }
    return false;
}

const Texture2D& Component::getTexture() const 
{
    return m_texture;
}