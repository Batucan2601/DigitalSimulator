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
    std::shared_ptr<Component> LogicElementFactory::createInput(std::string logger_name)
    {
        std::shared_ptr<Component> gate = std::make_shared<InputElement>(logger_name);
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
                        auto& g = static_cast<LogicGate&>(c);
                        bool result = true;
                        for (const auto& val : g.inputs)
                        {
                            result = result && val.val;
                            if (!result) break;
                        }
                        g.outputs[0].val = result;
                    });
                break;

            case CircuitElements::ComponentType::OR:
                gate->inputs.push_back(A);
                gate->inputs.push_back(B);
                gate->outputs.push_back(Out);
                gate->setEvaluationFunction(
                    [](Component& c)
                    {
                        auto& g = static_cast<LogicGate&>(c);
                        bool result = false;
                        for (const auto& val : g.inputs)
                        {
                            result = result || val.val;
                            if (result) break;
                        }
                        g.outputs[0].val = result;
                    });
                break;

            case CircuitElements::ComponentType::NOT:
                A.name = "In";
                gate->inputs.push_back(A);
                gate->outputs.push_back(Out);
                gate->setEvaluationFunction(
                    [](Component& c)
                    {
                        auto& g = static_cast<LogicGate&>(c);
                        if (!g.inputs.empty())
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
                        auto& g = static_cast<LogicGate&>(c);
                        bool result = false;
                        for (const auto& val : g.inputs)
                        {
                            result ^= val.val;
                        }
                        g.outputs[0].val = result;
                    });
                break;

            case CircuitElements::ComponentType::XAND:
                gate->inputs.push_back(A);
                gate->inputs.push_back(B);
                gate->outputs.push_back(Out);
                gate->setEvaluationFunction(
                    [](Component& c)
                    {
                        auto& g = static_cast<LogicGate&>(c);
                        bool result = true;
                        for (const auto& val : g.inputs)
                        {
                            result = result && val.val;
                            if (!result) break;
                        }
                        g.outputs[0].val = !result;
                    });
                break;
            case CircuitElements::ComponentType::NOR:
                gate->inputs.push_back(A);
                gate->inputs.push_back(B);
                gate->outputs.push_back(Out);
                gate->setEvaluationFunction(
                    [](Component& c)
                    {
                        auto& g = static_cast<LogicGate&>(c);
                        bool result = false;
                        for (const auto& val : g.inputs)
                        {
                            result = result || val.val;
                            if (result) break;
                        }
                        g.outputs[0].val = !result;
                    });
                break;
            default:
                break;
        }
    }

 
}  // namespace LogicElements
