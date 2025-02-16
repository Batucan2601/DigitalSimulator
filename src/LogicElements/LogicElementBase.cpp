#include "LogicElementBase.h"

namespace LogicElements
{
    LogicGate::~LogicGate()
    {
        m_logger.info("LogicGate destroyed.");
        UnloadTexture(m_texture);
    }

    void LogicGate::setPosition(float x, float y)
    {
        bd.x = x;
        bd.y = y;
    }

    Vector2 LogicGate::getPosition() const
    {
        return {bd.x, bd.y};
    }

    const std::unordered_map<std::string, bool> &LogicGate::getInputs() const
    {
        return inputs;
    }

    const std::unordered_map<std::string, bool> &LogicGate::getOutputs() const
    {
        return outputs;
    }

    void LogicGate::setInput(const std::string &name, bool value)
    {
        if (inputs.find(name) != inputs.end())
        {
            inputs[name] = value;
        }
    }

    bool LogicGate::getOutput(const std::string &name) const
    {
        auto it = outputs.find(name);
        return (it != outputs.end()) ? it->second : false;
    }

    // GatePosition &LogicGate::getPositionManager()
    // {
    //     return m_position;
    // }

} // namespace LogicElements