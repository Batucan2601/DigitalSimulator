#include "InputElement.h"
#include "appSettings.h"
#include "Util/Utils.h"
#include "ComponentTextures.h"
#include "raylibHelper.h"

static_assert(!std::is_abstract<InputElement>::value, "InputElement is abstract!");

InputElement::InputElement()
{
    this->m_type = CircuitElements::ComponentType::INPUT_0;  // Set type to INPUT_0
    this->m_texture = LogicElements::compTexture_getTexture(CircuitElements::ComponentType::INPUT_0);
    //this->setPosition(0, 0);  // Initialize position
    //this->setInOutPositions();
    InputResolver::RegisterHandler(this);
}
void InputElement::setInOutPositions()
{
    // output
    // int no_of_grid_points = this->bd.width / AppSettings::appSettings.GRID_POINT_SIZE + 1;
    for (size_t i = 0; i < this->outputs.size(); i++)
    {
        float x = this->bd.x;
        float y = this->bd.y + (i * AppSettings::appSettings.SPACING_SIZE);
        this->outputs[i].pos = {x, y};
    }
}

 void InputElement::OnLeftClick(const InputEvent& event)
{
    // check bb
    Vector2 pos = {(float)event.pos.x, (float)event.pos.y};
    bool isCol = CheckCollisionPointRec(pos, this->bd);
    if (!isCol)
    {
        return;
    }
    RaylibHelper::Show(1); // shows logicGateInfo window
    // if it is a inputgate
    if (this->m_type == CircuitElements::ComponentType::INPUT_0)
    {
        this->m_type = CircuitElements::ComponentType::INPUT_1;
        this->m_texture = LogicElements::compTexture_getTexture(CircuitElements::ComponentType::INPUT_1);
        this->outputs[0].val = 1;  // Set output to true
        this->notifyObservers();  // Notify observers of the change
    }
    else if (this->m_type == CircuitElements::ComponentType::INPUT_1)
    {
        this->m_type = CircuitElements::ComponentType::INPUT_0;
        this->m_texture = LogicElements::compTexture_getTexture(CircuitElements::ComponentType::INPUT_0);
        this->outputs[0].val = 0;  // Set output to true
        this->notifyObservers();  // Notify observers of the change
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
            circuit->addConnection(
                possibleConnection.sourceGate, possibleConnection.sourceLogic,
                possibleConnection.targetGate, possibleConnection.targetLogic);
            circuit->active_wire.is_visible = true;
            circuit->active_wire.start = pos;
            circuit->active_wire.end = pos;
            InputResolver::RegisterHandler(
                static_cast<IInputHandler*>(&(circuit->active_wire)));
            InputResolver::setSelectedHandler(
                (IInputHandler*)&circuit->connections[circuit->connections.size() - 1]);
        }
        else  // select the gate
        {
            InputResolver::setSelectedHandler((IInputHandler*)this);
        }
        return;
    }
    // check if a connection already selected.
    if (auto handler =
            dynamic_cast<CircuitElements::Connection*>(InputResolver::getSelectedHandler()))
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
                std::shared_ptr<InputElement> temp_ptr = std::static_pointer_cast<InputElement>(handler->sourceGate);
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
void InputElement::onInputChanged()
{
    this->evaluate();  // Automatically reevaluate when input changes
}
void InputElement::OnInputEvent(const InputEvent& event)
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

nlohmann::json InputElement::serialize() const
{
    nlohmann::json j;
    j["id"] = getID();
    j["type"] = getType();
    j["position"] = {{"x", getPosition().x}, {"y", getPosition().y}};
    j["inputs"] = this->getInputs();
    j["outputs"] = this->getOutputs();
    return j;
}
