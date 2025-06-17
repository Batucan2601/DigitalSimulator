#include "Component.h"
#include "LogicElements.h"
class SubcircuitComponent : public Component {
public:
    SubcircuitComponent(const CircuitElements::Circuit& inner, const std::string& name);
    //void evaluate() override;
    // Implement getInputs, getOutputs, etc. using internal Circuit

private:
    std::shared_ptr<CircuitElements::Circuit> internalCircuit;
};
