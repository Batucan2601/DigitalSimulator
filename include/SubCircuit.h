#include "Component.h"
#include "LogicElements.h"
class SubcircuitComponent : public Component {
public:
    SubcircuitComponent(const SP_Circuit& inner, const std::string& name);
    //void evaluate() override;
    // Implement getInputs, getOutputs, etc. using internal Circuit
    nlohmann::json serialize() const override;
    void evaluate() override;  // Override evaluate function
    void onInputChanged() override;  // Override observer function
    //void OnInputEvent(const InputEvent& event) override;
  
    private:
    void setInOutPositions() override;
    void connect_inputs();
    void connect_outputs();
    std::vector<Signal*> inputs_ptr;
    std::vector<Signal*> outputs_ptr;


private:
    SP_Circuit internalCircuit;
};
