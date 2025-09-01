#include "logicElementFactory.h"
#include "InputElement.h"
#include "Component.h"
#include "Clock.h"
#include "Combinational.h"
#include "Util/Utils.h"
namespace LogicElements
{
    static void generate_logic_gate( std::shared_ptr<Component> gate , CircuitElements::ComponentType type,  Signal A , Signal B , Signal Out );
    std::shared_ptr<Component> LogicElementFactory::createComponent(CircuitElements::ComponentType type,
                                                               std::string logger_name)
    {
        if( type == CircuitElements::ComponentType::INPUT ||
            type == CircuitElements::ComponentType::INPUT_0 ||
            type == CircuitElements::ComponentType::INPUT_1 )
        {
            return createInput(logger_name);
        }
        if( type == CircuitElements::ComponentType::CLK )
        {
            return createClock(logger_name, 1000); // Default tick rate of 1000 
        }
        if( type == CircuitElements::ComponentType::MUX)
        {   
            return createMux(logger_name);
        }
        if( type == CircuitElements::ComponentType::DECODER)
        {

        }
        return createGate(type, logger_name);        
    }
    
    
    std::shared_ptr<Component> LogicElementFactory::createGate(CircuitElements::ComponentType type,
                                                               std::string logger_name)
    {
        auto gate = std::make_shared<LogicGate>(type, logger_name);
        Signal A("A");
        Signal B("B");
        Signal Out("Out");
        // types for actual logic gates
        generate_logic_gate(gate, type, A, B, Out);
        InputResolver::RegisterHandler(gate);
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
        InputResolver::RegisterHandler(gate);
        return gate;
    }
    std::shared_ptr<Component> LogicElementFactory::createClock(std::string logger_name , unsigned int tickrate )
    {
        std::shared_ptr<Component> clk = std::make_shared<Clock>(logger_name ,tickrate);
        InputResolver::RegisterHandler(clk);
        return clk;
    }


    std::shared_ptr<Component> LogicElementFactory::createMux(std::string logger_name)
    {
        std::shared_ptr<Component> mux = std::make_shared<Combinational>(CircuitElements::ComponentType::MUX , logger_name);
        Signal A,B,Enable,Out; 
        A.name = "A";
        B.name = "B";
        Enable.name = "Enable";
        Out.name = "Out";
        mux->inputs.push_back(A);
        mux->inputs.push_back(B);
        mux->inputs.push_back(Enable);
        mux->outputs.push_back(Out);
        mux->setEvaluationFunction(
                    [](Component& c)
                    {
                        auto& g = static_cast<Combinational&>(c);
                        Signal enable  =  g.inputs[g.getInputByName("Enable")];
                        // this is for MSB, dont forget
                        int dec = Utils::BitsToDecimal(enable.val ,  true );
                        if(dec != -1 )
                        {
                            g.outputs[0].val = g.inputs[dec].val; // need to consider that aenable shall stay at the end.
                        }
                    });
        InputResolver::RegisterHandler(mux);
        return mux;
    }
    std::shared_ptr<Component> LogicElementFactory::createDecoder(std::string logger_name)
    {
        std::shared_ptr<Component> decoder 
        = std::make_shared<Combinational>(CircuitElements::ComponentType::DECODER , logger_name);
        Signal input[2];
        Signal out[4];
        decoder->inputs.push_back(input[0]);
        decoder->inputs.push_back(input[1]);
        decoder->inputs.push_back(out[0]);
        decoder->inputs.push_back(out[1]);
        decoder->inputs.push_back(out[2]);
        decoder->inputs.push_back(out[3]);
        InputResolver::RegisterHandler(decoder);
        return decoder;
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
            case CircuitElements::ComponentType::XNOR:
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
                            result = signal_xnor(result , val.val );
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
