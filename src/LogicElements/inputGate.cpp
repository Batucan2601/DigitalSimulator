#include <inputGate.h>

namespace LogicElements::Gates
{
    InputGate::InputGate(std::string& logger_name) : LogicGate(logger_name)
    {
        inputs["A"] = false;
        inputs["B"] = false;
        outputs["Out"] = false;

        type = LogicElements::GateType::INPUT;
        m_logger.info("Input Gate Created.");

        m_texture = LogicElements::logicElementTextures[GateType::INPUT];
    }

    void InputGate::evaluate()
    {
        return;
    }

}  // namespace LogicElements::Gates