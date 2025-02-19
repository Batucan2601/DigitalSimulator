#include "logicElementFactory.h"

namespace LogicElements
{
    std::shared_ptr<LogicGate> LogicElementFactory::createGate(GateType type,
                                                               std::string logger_name)
    {
        auto gate = std::make_shared<LogicGate>(type, logger_name);

        switch (type)
        {
            case GateType::AND:
                gate->setEvaluationFunction(
                    [](LogicGate& g)
                    {
                        auto& out = g.outputs["Out"];
                        for (auto const& [key, val] : g.inputs)
                        {
                            if (!out)
                                break;
                            out = out && val;
                        }
                    });
                break;

            case GateType::OR:
                gate->setEvaluationFunction(
                    [](LogicGate& g)
                    {
                        auto& out = g.outputs["Out"];
                        for (auto const& [key, val] : g.inputs)
                        {
                            if (out)
                                break;
                            out = out || val;
                        }
                    });
                break;

            case GateType::NOT:
                gate->setEvaluationFunction(
                    [](LogicGate& g)
                    {
                        g.outputs["Out"] = !g.inputs["A"];
                    });
                break;

            case GateType::XOR:
                gate->setEvaluationFunction(
                    [](LogicGate& g)
                    {
                        auto& out = g.outputs["Out"];
                        for (auto const& [key, val] : g.inputs)
                        {
                            if (!out)
                                break;
                            out = out ^ val;
                        }
                    });
                break;

            case GateType::XAND:
                gate->setEvaluationFunction(
                    [](LogicGate& g)
                    {
                        // thi is NAND logic
                        auto& out = g.outputs["Out"];
                        bool allTrue = true;  // Assume all inputs are true initially.
                        for (auto const& [name, value] : g.inputs)
                        {
                            if (!value)
                            {  // As soon as one input is false...
                                allTrue = false;
                                break;  // ...we can stop checking.
                            }
                        }
                        out = !allTrue;  // NAND: output is true if any input is false.    }
                    });
                break;

            default:
                break;
        }

        return gate;
    }
}  // namespace LogicElements
