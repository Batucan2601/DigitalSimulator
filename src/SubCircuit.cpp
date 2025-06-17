#include "Subcircuit.h"

SubcircuitComponent::SubcircuitComponent(const CircuitElements::Circuit& circuitRef, const std::string& name)
{
    this->internalCircuit = std::make_shared<CircuitElements::Circuit>(circuitRef);
    
    // with connections get the 
    for (size_t i = 0; i < this->internalCircuit->gates.size(); i++)
    {
        for (size_t j = 0; j < this->internalCircuit->gates[i]->inputs.size(); j++)
        {
            bool is_found = false; 
            for (size_t k = 0; k < this->internalCircuit->connections.size(); k++)
            {
                
            }
        }
        for (size_t j = 0; j < this->internalCircuit->gates[i]->outputs.size(); j++)
        {

        }
    }
}

//void SubcircuitComponent::evaluate() {
//    this->internalCircuit->evaluate();
//}
