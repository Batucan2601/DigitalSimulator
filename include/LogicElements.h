#ifndef LOGIC_ELEMENTS_H
#define LOGIC_ELEMENTS_H

#include "raylib.h"

#include <memory>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <vector>

enum class GateType
{
    AND,
    OR,
    NOT
};

enum class SignalName
{
    A,
    B,
    OUT
};

class LogicGate
{
  public:
    void setPosition(float x, float y);
    Vector2 getPosition() const;

    virtual ~LogicGate() {}
    virtual void evaluate() = 0;
    virtual void setInput(const std::string& name, bool value) = 0;
    virtual bool getOutput(const std::string& name) const = 0;

    const std::unordered_map<std::string, bool>& getInputs() const;
    const std::unordered_map<std::string, bool>& getOutputs() const;

    Rectangle bd = {0, 0, 50, 50};  // bounding box
    std::string type;

  protected:
    std::unordered_map<std::string, bool> inputs;
    std::unordered_map<std::string, bool> outputs;
};

class AndGate : public LogicGate
{
  public:
    AndGate();

    void evaluate() override;
    void setInput(const std::string& name, bool value) override;
    bool getOutput(const std::string& name) const override;

    std::unordered_map<std::string, bool> inputs{{"A", false}, {"B", false}};
    std::unordered_map<std::string, bool> outputs{{"Out", false}};
};

class OrGate : public LogicGate
{
  public:
    OrGate();

    void evaluate() override;
    void setInput(const std::string& name, bool value) override;
    bool getOutput(const std::string& name) const override;

    std::unordered_map<std::string, bool> inputs{{"A", false}, {"B", false}};
    std::unordered_map<std::string, bool> outputs{{"Out", false}};
};

class Circuit
{
  public:
    void addGate(std::shared_ptr<LogicGate> gate);

    struct Connection
    {
        std::shared_ptr<LogicGate> sourceGate;
        std::string sourceOutput;
        std::shared_ptr<LogicGate> targetGate;
        std::string targetInput;
    };

    void addConnection(std::shared_ptr<LogicGate> sourceGate, const std::string& sourceOutput,
                       std::shared_ptr<LogicGate> targetGate, const std::string& targetInput);

    void evaluate();

    std::vector<std::shared_ptr<LogicGate>> gates;
    std::vector<Connection> connections;
};

#endif  // LOGIC_ELEMENTS_H
