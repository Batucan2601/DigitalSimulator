#include "logicElementFactory.h"

namespace LogicElements
{
    LogicGate LogicElementFactory::createGate(GateType type, std::string logger_name)
    {
        //auto gate = std::make_shared<LogicGate>(type, logger_name);
        LogicGate gate(type, logger_name);
        Signal A("A");
        Signal B("B");
        Signal Out("Out");
        switch (type)
        {
            case GateType::AND:
                gate.inputs.push_back(A);
                gate.inputs.push_back(B);
                gate.outputs.push_back(Out);
                gate.setEvaluationFunction(
                    [](LogicGate& g)
                    {
                        auto& out = g.outputs[0];
                        for (auto const& val : g.inputs)
                        {
                            if (!out.val)
                                break;
                            out.val = out.val && val.val;
                        }
                    });
                break;

            case GateType::OR:
                gate.inputs.push_back(A);
                gate.inputs.push_back(B);
                gate.outputs.push_back(Out);
                gate.setEvaluationFunction(
                    [](LogicGate& g)
                    {
                        auto& out = g.outputs[0];
                        for (auto const& val : g.inputs)
                        {
                            if (out.val)
                                break;
                            out.val = out.val || val.val;
                        }
                    });
                break;

            case GateType::NOT:
                A.name = "In";
                gate.inputs.push_back(A);
                gate.outputs.push_back(Out);
                gate.setEvaluationFunction(
                    [](LogicGate& g)
                    {
                        g.outputs[0].val = !g.inputs[0].val;
                    });
                break;

            case GateType::XOR:
                gate.inputs.push_back(A);
                gate.inputs.push_back(B);
                gate.outputs.push_back(Out);
                gate.setEvaluationFunction(
                    [](LogicGate& g)
                    {
                        auto& out = g.outputs[0];
                        for (auto const& val: g.inputs)
                        {
                            if (!out.val)
                                break;
                            out.val = out.val ^ val.val;
                        }
                    });
                break;

            case GateType::XAND:
                gate.inputs.push_back(A);
                gate.inputs.push_back(B);
                gate.outputs.push_back(Out);
                gate.setEvaluationFunction(
                    [](LogicGate& g)
                    {
                        // thi is NAND logic
                        auto& out = g.outputs[0];
                        bool allTrue = true;  // Assume all inputs are true initially.
                        for (auto const& val: g.inputs)
                        {
                            if (!val.val)
                            {  // As soon as one input is false...
                                allTrue = false;
                                break;  // ...we can stop checking.
                            }
                        }
                        out.val = !allTrue;  // NAND: output is true if any input is false.    }
                    });
                break;

            default:
                break;
        }

        return gate;
    }
}  // namespace LogicElements
