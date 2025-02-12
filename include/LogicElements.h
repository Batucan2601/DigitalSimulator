#ifndef LOGIC_ELEMENTS_H
#define LOGIC_ELEMENTS_H

#include "ClassLogger.h"
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

class LogicGate
{
  public:
    explicit LogicGate(std::string& logger_name) : m_logger(logger_name) {}
    void setPosition(float x, float y);
    Vector2 getPosition() const;

    virtual ~LogicGate() {}
    virtual void evaluate() = 0;
    virtual void setInput(const std::string& name, bool value) = 0;
    virtual bool getOutput(const std::string& name) const = 0;

    const std::unordered_map<std::string, bool>& getInputs() const;
    const std::unordered_map<std::string, bool>& getOutputs() const;

    Rectangle bd = {0, 0, 100, 100};  // bounding box
    GateType type;

  protected:
    std::unordered_map<std::string, bool> inputs;
    std::unordered_map<std::string, bool> outputs;
    ClassLogger m_logger;
};

class AndGate : public LogicGate
{
  public:
    AndGate(std::string& logger_name);

    void evaluate() override;
    void setInput(const std::string& name, bool value) override;
    bool getOutput(const std::string& name) const override;
};

class OrGate : public LogicGate
{
  public:
    OrGate(std::string& logger_name);

    void evaluate() override;
    void setInput(const std::string& name, bool value) override;
    bool getOutput(const std::string& name) const override;
};

struct PhysicalConnection
{
    std::vector<Vector2> wires;
};
struct Connection
{
    std::shared_ptr<LogicGate> sourceGate;
    std::string sourceLogic;
    std::shared_ptr<LogicGate> targetGate;
    std::string targetLogic;
    PhysicalConnection physCon;
    bool is_connected = false;
};
struct ActiveWire
{
    Vector2 start;
    Vector2 end;
    bool is_visible;
};
class Circuit
{
  public:
    Circuit(std::string& logger_name) : m_logger(logger_name) {}
    void addGate(std::shared_ptr<LogicGate> gate);
    void addConnection(std::shared_ptr<LogicGate> sourceGate, const std::string& sourceOutput,
                       std::shared_ptr<LogicGate> targetGate, const std::string& targetInput);
    void evaluate();
    ClassLogger m_logger;
    std::vector<std::shared_ptr<LogicGate>> gates;
    std::vector<Connection> connections;
    // TODO 
    // this might be moved to a better data structure
    ActiveWire active_wire;
};

#endif  // LOGIC_ELEMENTS_H
