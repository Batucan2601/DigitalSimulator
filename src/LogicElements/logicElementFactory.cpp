#include "logicElementFactory.h"
#include "InputElement.h"
namespace LogicElements
{
    static void generate_logic_gate( std::shared_ptr<Component> gate , CircuitElements::ComponentType type,  Signal A , Signal B , Signal Out );
    std::shared_ptr<Component> LogicElementFactory::createGate(CircuitElements::ComponentType type,
                                                               std::string logger_name)
    {
        auto gate = std::make_shared<LogicGate>(type, logger_name);
        Signal A("A");
        Signal B("B");
        Signal Out("Out");
        // types for actual logic gates
        generate_logic_gate(gate, type, A, B, Out);
        return gate;
    }
    std::shared_ptr<Component> LogicElementFactory::createInput()
    {
        std::shared_ptr<Component> gate = std::make_shared<InputElement>();
        Signal Out("Out");
        gate->outputs.push_back(Out);
        gate->m_type = CircuitElements::ComponentType::INPUT_0;
        gate->setEvaluationFunction([](Component& c) {
            auto& g = static_cast<InputElement&>(c);
            g.outputs[0].val = (g.getType() == CircuitElements::ComponentType::INPUT_1) ? 1 : 0;
        });
        return gate;
    }
    static void generate_logic_gate( std::shared_ptr<Component> gate , CircuitElements::ComponentType type,  Signal A , Signal B , Signal Out )
    {
        switch (type)
        {
            case CircuitElements::ComponentType::AND:
                gate->inputs.push_back(A);
                gate->inputs.push_back(B);
                gate->outputs.push_back(Out);
                gate->setEvaluationFunction(
                    [](Component& c)
                    {
                        auto& g = static_cast<LogicGate&>(c); // downcast
                        auto& out = g.outputs[0];
                        for (auto const& val : g.inputs)
                        {
                            if (!out.val)
                                break;
                            out.val = out.val && val.val;
                        }
                    });
                break;

            case CircuitElements::ComponentType::OR:
                gate->inputs.push_back(A);
                gate->inputs.push_back(B);
                gate->outputs.push_back(Out);
                gate->setEvaluationFunction(
                    [](Component& c)
                    {
                        auto& g = static_cast<LogicGate&>(c); // downcast
                        auto& out = g.outputs[0];
                        for (auto const& val : g.inputs)
                        {
                            if (out.val)
                                break;
                            out.val = out.val || val.val;
                        }
                    });
                break;

            case CircuitElements::ComponentType::NOT:
                A.name = "In";
                gate->inputs.push_back(A);
                gate->outputs.push_back(Out);
                gate->setEvaluationFunction(
                    [](Component& c)
                    {
                        auto& g = static_cast<LogicGate&>(c); // downcast
                        g.outputs[0].val = !g.inputs[0].val;
                    });
                break;

            case CircuitElements::ComponentType::XOR:
                gate->inputs.push_back(A);
                gate->inputs.push_back(B);
                gate->outputs.push_back(Out);
                gate->setEvaluationFunction(
                    [](Component& c)
                    {
                        auto& g = static_cast<LogicGate&>(c); // downcast
                        auto& out = g.outputs[0];
                        for (auto const& val: g.inputs)
                        {
                            if (!out.val)
                                break;
                            out.val = out.val ^ val.val;
                        }
                    });
                break;

            case CircuitElements::ComponentType::XAND:
                gate->inputs.push_back(A);
                gate->inputs.push_back(B);
                gate->outputs.push_back(Out);
                gate->setEvaluationFunction(
                    [](Component& c)
                    {
                        auto& g = static_cast<LogicGate&>(c); // downcast
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
    }

 
}  // namespace LogicElements
