#include "LogicElements.h"

namespace CircuitElements 
{
    void Circuit::addGate(std::shared_ptr<LogicElements::LogicGate> gate)
    {
        this->m_logger.info("Gate added to the circuit.");
        gates.push_back(gate);
    }

    void Circuit::addConnection(std::shared_ptr<LogicElements::LogicGate> sourceGate,
                                const std::string& sourceOutput,
                                std::shared_ptr<LogicElements::LogicGate> targetGate,
                                const std::string& targetInput)
    {
        this->m_logger.info("Connection added to the circuit.");
        connections.push_back({sourceGate, sourceOutput, targetGate, targetInput});
    }

    void Circuit::evaluate()
    {
        bool stabilized = false;
        int iterations = 0;
        const int maxIterations = 100;  // Prevent infinite loops

        while (!stabilized && iterations < maxIterations)
        {
            stabilized = true;
            for (auto& gate : gates)
            {
                gate->evaluate();
                auto previousOutputs = gate->getOutputs();
                gate->evaluate();
                if (gate->getOutputs() != previousOutputs)
                {
                    stabilized = false;
                }
            }
            // Then, update the inputs based on the connections.
            for (auto& conn : connections)
            {
                bool sourceValue = conn.sourceGate->getOutput(conn.sourceLogic);
                if (conn.targetLogic != "")
                {
                    conn.targetGate->setInput(conn.targetLogic, sourceValue);
                }
            }
            iterations++;
        }
        if (iterations == maxIterations)
        {
            // Handle infinite loop case
            throw std::runtime_error("Circuit evaluation did not stabilize.");
        }
    }

}  // namespace CircuitElements
