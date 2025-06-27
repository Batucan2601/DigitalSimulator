#include "logicElementFactory.h"
#include "InputElement.h"
#include "Component.h"
#include "Clock.h"
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
            g.outputs[0].val = std::vector<SignalVal>(1, SignalVal::SIGNAL_0); // Default to SIGNAL_0
            g.outputs[0].val[0] = (g.getType() == CircuitElements::ComponentType::INPUT_1) ? SignalVal::SIGNAL_1 : SignalVal::SIGNAL_0;
        });
        return gate;
    }
    std::shared_ptr<Component> LogicElementFactory::createClock(std::string logger_name , unsigned int tickrate )
    {
        std::shared_ptr<Component> clk = std::make_shared<Clock>(logger_name ,tickrate);
        return clk;
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
                        std::vector<SignalVal> result = std::vector<SignalVal>(g.inputs[0].val.size(), SignalVal::SIGNAL_1);
                        for (const auto& val : g.inputs)
                        {
                            result =  signal_and(result , val.val);
                            //if (result == SignalVal::SIGNAL_0) break;
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
                        std::vector<SignalVal> result = std::vector<SignalVal>(g.inputs[0].val.size(), SignalVal::SIGNAL_0);
                        for (const auto& val : g.inputs)
                        {
                            result =  signal_or(result , val.val);
                            //if (result == SignalVal::SIGNAL_1) break;
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
                            g.outputs[0].val = signal_not(g.inputs[0].val);
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
                        std::vector<SignalVal> result = std::vector<SignalVal>(g.inputs[0].val.size(), SignalVal::SIGNAL_0);
                        for (const auto& val : g.inputs)
                        {
                            result = signal_xor(result , val.val );
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
                        std::vector<SignalVal> result = std::vector<SignalVal>(g.inputs[0].val.size(), SignalVal::SIGNAL_1);
                        for (const auto& val : g.inputs)
                        {
                            result = signal_and(result , val.val);
                            //if (result == SignalVal::SIGNAL_0) break;
                        }
                        g.outputs[0].val = signal_not(result);
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
                        std::vector<SignalVal> result = std::vector<SignalVal>(g.inputs[0].val.size(), SignalVal::SIGNAL_0);
                        for (const auto& val : g.inputs)
                        {
                            result = signal_or(result, val.val);
                            //if (result == SignalVal::SIGNAL_0) break;
                        }
                        g.outputs[0].val = signal_not(result);
                    });
                break;
            default:
                break;
        }
    }

 
}  // namespace LogicElements
