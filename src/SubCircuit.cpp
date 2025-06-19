#include "Subcircuit.h"
#include <ComponentTextures.h>

SubcircuitComponent::SubcircuitComponent(const SP_Circuit& circuitRef, const std::string& logger_name)
    :Component(logger_name)
{
    this->internalCircuit = circuitRef;
    
    // with connections get the 
    for (size_t i = 0; i < this->internalCircuit->gates.size(); i++)
    {
        for (size_t j = 0; j < this->internalCircuit->gates[i]->inputs.size(); j++)
        {
            bool is_found = false; 
            for (size_t k = 0; k < this->internalCircuit->connections.size(); k++)
            {
                if (this->internalCircuit->connections[k].sourceGate == this->internalCircuit->gates[i] &&
                    this->internalCircuit->connections[k].sourceLogic == this->internalCircuit->gates[i]->inputs[j].name)
                {
                    is_found = true; 
                    break; 
                }
            }
            if (is_found)
            {
                continue; 
            }
            Signal in;
            in = this->internalCircuit->gates[i]->inputs[j];
            this->inputs.push_back(in);
        }
        for (size_t j = 0; j < this->internalCircuit->gates[i]->outputs.size(); j++)
        {
            bool is_found = false; 
            for (size_t k = 0; k < this->internalCircuit->connections.size(); k++)
            {
                if (this->internalCircuit->connections[k].sourceGate == this->internalCircuit->gates[i] &&
                    this->internalCircuit->connections[k].sourceLogic == this->internalCircuit->gates[i]->outputs[j].name)
                {
                    is_found = true; 
                    break; 
                }
            }
            if (is_found)
            {
                continue; 
            }
            Signal out;
            out = this->internalCircuit->gates[i]->outputs[j];
            this->outputs.push_back(out);
        }
    }
    this->m_texture = LogicElements::compTexture_getTexture(CircuitElements::ComponentType::INPUT_0);
    InputResolver::RegisterHandler(this);
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
void SubcircuitComponent::onInputChanged()
{
    //this->evaluate();  // Automatically reevaluate when input changes
}
void SubcircuitComponent::OnInputEvent(const InputEvent& event)
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

nlohmann::json SubcircuitComponent::serialize() const {
    nlohmann::json j;
    j["id"] = getID();
    j["type"] = getType();
    j["position"] = {{"x", getPosition().x}, {"y", getPosition().y}};
    j["inputs"] = getInputs();
    j["outputs"] = getOutputs();
    return j;
}