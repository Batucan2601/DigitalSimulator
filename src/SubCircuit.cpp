#include "SubCircuit.h"
#include <ComponentTextures.h>

SubcircuitComponent::SubcircuitComponent(const SP_Circuit& circuitRef, const std::string& logger_name)
    :Component(logger_name)
{
    this->internalCircuit = circuitRef;
    for (size_t i = 0; i < this->internalCircuit->connections.size(); i++)
    {
        InputResolver::UnregisterHandler(
            &this->internalCircuit->connections[i]);  // Unregister connections from the circuit
        this->internalCircuit->connections[i].physCon.wires.clear();  // Clear the wires in the connection        
    }
    for (size_t i = 0; i < this->internalCircuit->gates.size(); i++)
    {
        InputResolver::UnregisterHandler(
            this->internalCircuit->gates[i].get());  // Unregister connections from the circuit
    }
    
    // with connections get the 
    for (size_t i = 0; i < this->internalCircuit->gates.size(); i++)
    {
        for (size_t j = 0; j < this->internalCircuit->gates[i]->inputs.size(); j++)
        {
            if(this->internalCircuit->gates[i]->inputs[j].type == SignalType::INPUT)
            {
                //this->internalCircuit->gates[i]->inputs[j].val = SignalVal::SIGNAL_0;  // Initialize input signals to Z state
                Signal in = this->internalCircuit->gates[i]->inputs[j];
                this->inputs.push_back(in);
                this->inputs_ptr.push_back(&this->internalCircuit->gates[i]->inputs[j]);
            }
        }
        for (size_t j = 0; j < this->internalCircuit->gates[i]->outputs.size(); j++)
        {
            if(this->internalCircuit->gates[i]->outputs[j].type == SignalType::OUTPUT)
            {
                //this->internalCircuit->gates[i]->outputs[j].val = SignalVal::SIGNAL_0;  // Initialize output signals to Z state
                Signal out = this->internalCircuit->gates[i]->outputs[j];
                this->outputs.push_back(out);
                this->outputs_ptr.push_back(&this->internalCircuit->gates[i]->outputs[j]);
            }
        }
    }
    this->m_texture = LogicElements::compTexture_getTexture(CircuitElements::ComponentType::INPUT_0);
    InputResolver::RegisterHandler(this);
    this->setInOutPositions();
}
void SubcircuitComponent::setInOutPositions()
{
    // output
    // int no_of_grid_points = this->bd.width / AppSettings::appSettings.GRID_POINT_SIZE + 1;
    for (size_t i = 0; i < this->inputs.size(); i++)
    {
        float x = this->bd.x;
        float y = this->bd.y + (i * AppSettings::appSettings.SPACING_SIZE);
        this->inputs[i].pos = {x, y};
    }
    for (size_t i = 0; i < this->outputs.size(); i++)
    {
        float x = this->bd.x + this->bd.width;
        float y = this->bd.y + (i * AppSettings::appSettings.SPACING_SIZE);
        this->outputs[i].pos = {x, y};
    }
}
void SubcircuitComponent::connect_inputs()
{
    for (size_t i = 0; i < this->inputs.size(); i++)
    {
        //this->inputs[i].val = this->inputs_ptr[i]->val;
        *this->inputs_ptr[i] = this->inputs[i];
    }
}
void SubcircuitComponent::connect_outputs()
{
    for (size_t i = 0; i < this->outputs.size(); i++)
    {
        //*this->outputs_ptr[i] = this->outputs[i];
        Vector2 pos = this->outputs[i].pos;
        this->outputs[i] = *this->outputs_ptr[i];
        this->outputs[i].pos = pos;
    }
}
void SubcircuitComponent::evaluate()
{
    // Evaluate the internal circuit
    if (internalCircuit)
    {
        this->connect_inputs();
        internalCircuit->evaluate();
        this->connect_outputs();
    }
    // Notify observers that the input has changed
    notifyObservers();
}
void SubcircuitComponent::onInputChanged()
{
    this->evaluate();  // Automatically reevaluate when input changes
}
//void SubcircuitComponent::OnInputEvent(const InputEvent& event)
//{
//    if (event.type == InputType::Mouse)
//    {
//        if (event.mouseState == MouseEventState::LeftClick)
//        {
//            OnLeftClick(event);
//        }
//        if (event.mouseState == MouseEventState::Release)
//        {
//            OnRelease(event);
//        }
//        if (event.mouseState == MouseEventState::RightClick)
//        {
//            OnRightClick(event);
//        }
//        if (event.mouseState == MouseEventState::Down)
//        {
//            OnDown(event);
//        }
//        if (event.mouseState == MouseEventState::Move)
//        {
//            OnMove(event);
//        }
//        if (event.mouseState == MouseEventState::Enter)
//        {
//            OnEnter(event);
//        }
//        if (event.mouseState == MouseEventState::Leave)
//        {
//            OnExit(event);
//        }
//    }
//
//    if (event.type == InputType::Keyboard)
//    {
//        if (event.keyState == KeyboardEvent::KeyPress)
//        {
//            OnKeyPress(event);
//        }
//        if (event.keyState == KeyboardEvent::KeyRelease)
//        {
//            // OnKeyRelease(event);
//        }
//        if (event.keyState == KeyboardEvent::KeyRepeat)
//        {
//            // OnKeyRepeat(event);
//        }
//    }
//}

nlohmann::json SubcircuitComponent::serialize() const {
    nlohmann::json j;
    j["id"] = getID();
    j["type"] = getType();
    j["position"] = {{"x", getPosition().x}, {"y", getPosition().y}};
    j["inputs"] = getInputs();
    j["outputs"] = getOutputs();
    return j;
}