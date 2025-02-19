#include <xorGate.h>

namespace LogicElements::Gates
{
    XorGate::XorGate(std::string& logger_name) : LogicGate(logger_name)
    {
        inputs["A"] = false;
        inputs["B"] = false;
        outputs["Out"] = false;
        type = GateType::XOR;
        m_logger.info("Xor Gate Created.");

        m_texture = LogicElements::logicElementTextures[GateType::XOR];
    }

    void XorGate::evaluate()
    {
        auto& out = outputs["Out"];
        for (auto const& [key, val] : inputs)
        {
            if (!out)
                break;
            out = out ^ val;
        }
    }

}  // namespace LogicElements::Gates
