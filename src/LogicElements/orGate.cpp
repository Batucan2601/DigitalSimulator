#include <orGate.h>

namespace LogicElements::Gates
{
    OrGate::OrGate(std::string& logger_name) : LogicGate(logger_name)
    {
        inputs["A"] = false;
        inputs["B"] = false;
        outputs["Out"] = false;
        type = GateType::OR;
        m_logger.info("Or Gate Created.");

        m_texture = LogicElements::logicElementTextures[GateType::OR];
    }

    void OrGate::evaluate()
    {
        auto& out = outputs["Out"];
        for (auto const& [key, val] : inputs)
        {
            if (out)
                break;
            out = out || val;
        }
    }

}  // namespace LogicElements::Gates
