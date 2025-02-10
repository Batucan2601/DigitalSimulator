#ifndef LOGIC_ELEMENTS_H
#define LOGIC_ELEMENTS_H
#include <string>
#include <unordered_map>
#include <memory>
#include "raylib.h"
class LogicGate {
public:
    virtual ~LogicGate() {}
    virtual void evaluate() = 0;

    // Optionally, a method to set an input by name
    virtual void setInput(const std::string& name, bool value) = 0;

    // Get output by name
    virtual bool getOutput(const std::string& name) const = 0;

    Rectangle bd = { 0, 0, 50,50}; //bounding box
    std::string type; 
};
class AndGate : public LogicGate {
public:
    AndGate() {
        inputs["A"] = false;
        inputs["B"] = false;
        type = "and";
    }

    void evaluate() override {
        outputs["Out"] = inputs["A"] && inputs["B"];
    }

    void setInput(const std::string& name, bool value) override {
        if (inputs.find(name) != inputs.end()) {
            inputs[name] = value;
        }
    }

    bool getOutput(const std::string& name) const override {
        auto it = outputs.find(name);
        return (it != outputs.end()) ? it->second : false;
    }


    std::unordered_map<std::string, bool> inputs{ {"A", false}, {"B", false} };
    std::unordered_map<std::string, bool> outputs{ {"Out", false} };
};

// The Circuit class holds multiple gates and manages connections between them.
class Circuit {
public:
    // Add a gate to the circuit.
    void addGate(std::shared_ptr<LogicGate> gate) {
        gates.push_back(gate);
    }

    // Define a connection between a source gate's output and a target gate's input.
    struct Connection {
        std::shared_ptr<LogicGate> sourceGate;
        std::string sourceOutput;
        std::shared_ptr<LogicGate> targetGate;
        std::string targetInput;
    };

    // Add a connection to the circuit.
    void addConnection(std::shared_ptr<LogicGate> sourceGate, const std::string& sourceOutput,
        std::shared_ptr<LogicGate> targetGate, const std::string& targetInput) {
        connections.push_back({ sourceGate, sourceOutput, targetGate, targetInput });
    }

    // A simple evaluate routine:
    // 1. Evaluate all gates.
    // 2. Propagate outputs via the connections.
    // Note: For more complex circuits (especially with loops), you might need to iterate until the circuit stabilizes.
    void evaluate() {
        // First, evaluate all gates.
        for (auto& gate : gates) {
            gate->evaluate();
        }

        // Then, update the inputs based on the connections.
        for (auto& conn : connections) {
            bool sourceValue = conn.sourceGate->getOutput(conn.sourceOutput);
            conn.targetGate->setInput(conn.targetInput, sourceValue);
        }
    }

    std::vector<std::shared_ptr<LogicGate>> gates;
    std::vector<Connection> connections;
};
#endif