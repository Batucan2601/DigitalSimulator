#include "Component.h"
#include "LogicElements.h"
class SubcircuitComponent : public Component {
public:
    SubcircuitComponent(const SP_Circuit& inner, const std::string& name);
    //void evaluate() override;
    // Implement getInputs, getOutputs, etc. using internal Circuit
    nlohmann::json serialize() const override;
    void onInputChanged() override;  // Override observer function
    //void OnInputEvent(const InputEvent& event) override;
  
    private:
    void setInOutPositions() override;

private:
    SP_Circuit internalCircuit;
};
