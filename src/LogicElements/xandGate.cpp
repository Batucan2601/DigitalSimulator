#include <xandGate.h>

namespace LogicElements::Gates
{
    XandGate::XandGate(std::string& logger_name) : LogicGate(logger_name)
    {
        inputs["A"] = false;
        inputs["B"] = false;
        outputs["Out"] = false;
        type = GateType::XAND;
        m_logger.info("Xand Gate Created.");

        m_texture = LogicElements::logicElementTextures[GateType::XAND];
    }

    void XandGate::evaluate()
    {
        // thi is NAND logic
        auto& out = outputs["Out"];
        bool allTrue = true;  // Assume all inputs are true initially.
        for (auto const& [name, value] : inputs)
        {
            if (!value)
            {  // As soon as one input is false...
                allTrue = false;
                break;  // ...we can stop checking.
            }
        }
        out = !allTrue;  // NAND: output is true if any input is false.    }
    }
}  // namespace LogicElements::Gates
