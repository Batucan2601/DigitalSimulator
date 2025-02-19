#include <andGate.h>

namespace LogicElements::Gates
{
    AndGate::AndGate(std::string& logger_name) : LogicGate(logger_name)
    {
        inputs["A"] = false;
        inputs["B"] = false;
        outputs["Out"] = false;

        type = GateType::AND;
        m_logger.info("And Gate Created.");

        m_texture = LogicElements::logicElementTextures[GateType::AND];
    }

    void AndGate::evaluate()
    {
        auto& out = outputs["Out"];
        for (auto const& [key, val] : inputs)
        {
            if (!out)
                break;
            out = out && val;
        }
    }

}  // namespace LogicElements::Gates