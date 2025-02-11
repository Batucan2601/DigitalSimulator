#include "LogicElements.h"

void LogicGate::setPosition(float x, float y)
{
    bd.x = x;
    bd.y = y;
}

Vector2 LogicGate::getPosition() const
{
    return {bd.x, bd.y};
}

const std::unordered_map<std::string, bool>& LogicGate::getInputs() const
{
    return inputs;
}

const std::unordered_map<std::string, bool>& LogicGate::getOutputs() const
{
    return outputs;
}

AndGate::AndGate()
{
    inputs["A"] = false;
    inputs["B"] = false;
    outputs["Out"] = false;
    type = "and";
}

void AndGate::evaluate()
{
    outputs["Out"] = inputs["A"] && inputs["B"];
}

void AndGate::setInput(const std::string& name, bool value)
{
    if (inputs.find(name) != inputs.end())
    {
        inputs[name] = value;
    }
}

bool AndGate::getOutput(const std::string& name) const
{
    auto it = outputs.find(name);
    return (it != outputs.end()) ? it->second : false;
}

OrGate::OrGate()
{
    inputs["A"] = false;
    inputs["B"] = false;
    outputs["Out"] = false;
    type = "or";
}

void OrGate::evaluate()
{
    outputs["Out"] = inputs["A"] || inputs["B"];
}

void OrGate::setInput(const std::string& name, bool value)
{
    if (inputs.find(name) != inputs.end())
    {
        inputs[name] = value;
    }
}

bool OrGate::getOutput(const std::string& name) const
{
    auto it = outputs.find(name);
    return (it != outputs.end()) ? it->second : false;
}

void Circuit::addGate(std::shared_ptr<LogicGate> gate)
{
    gates.push_back(gate);
}

void Circuit::addConnection(std::shared_ptr<LogicGate> sourceGate, const std::string& sourceOutput,
                            std::shared_ptr<LogicGate> targetGate, const std::string& targetInput)
{
    connections.push_back({sourceGate, sourceOutput, targetGate, targetInput });
}

void Circuit::evaluate()
{
    bool stabilized = false;
    int iterations = 0;
    const int maxIterations = 100;  // Prevent infinite loops

    while (!stabilized && iterations < maxIterations)
    {
        stabilized = true;
        for (auto& gate : gates)
        {
            gate->evaluate();
            auto previousOutputs = gate->getOutputs();
            gate->evaluate();
            if (gate->getOutputs() != previousOutputs)
            {
                stabilized = false;
            }
        }
        // Then, update the inputs based on the connections.
        for (auto& conn : connections)
        {
            bool sourceValue = conn.sourceGate->getOutput(conn.sourceLogic);
            conn.targetGate->setInput(conn.targetLogic, sourceValue);
        }
        iterations++;
    }
    if (iterations == maxIterations)
    {
        // Handle infinite loop case
        throw std::runtime_error("Circuit evaluation did not stabilize.");
    }
}
