#include <notGate.h>

namespace LogicElements::Gates
{
    NotGate::NotGate(std::string& logger_name) : LogicGate(logger_name)
    {
        inputs["In"] = false;
        outputs["Out"] = false;
        type = GateType::NOT;
        m_logger.info("Not Gate Created.");

        m_texture = LogicElements::logicElementTextures[GateType::NOT];
    }

    void NotGate::evaluate()
    {
        outputs["Out"] = !inputs["In"];
    }

}  // namespace LogicElements::Gates
