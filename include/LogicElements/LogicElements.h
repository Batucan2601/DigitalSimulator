#ifndef LOGIC_ELEMENTS_H
#define LOGIC_ELEMENTS_H

#include "ClassLogger.h"
#include "raylib.h"

#include <memory>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <vector>
#include <filesystem>

#include "LogicElementBase.h"

namespace CircuitElements
{

  struct PhysicalConnection
  {
    std::vector<Vector2> wires;
  };
  struct Connection
  {
    std::shared_ptr<LogicElements::LogicGate> sourceGate;
    std::string sourceLogic;
    std::shared_ptr<LogicElements::LogicGate> targetGate;
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
  struct SelectedWires
  {
    std::vector<Vector2> selected_wires;
    Vector2 wire_hovering;
  };
  class Circuit
  {
  public:
    Circuit(std::string &logger_name) : m_logger(logger_name) {}
    void addGate(std::shared_ptr<LogicElements::LogicGate> gate);
    void addConnection(std::shared_ptr<LogicElements::LogicGate> sourceGate, const std::string &sourceOutput,
                       std::shared_ptr<LogicElements::LogicGate> targetGate, const std::string &targetInput);
    void evaluate();
    ClassLogger m_logger;
    std::vector<std::shared_ptr<LogicElements::LogicGate>> gates;
    std::vector<Connection> connections;
    // TODO
    // this might be moved to a better data structure
    ActiveWire active_wire;
    SelectedWires selected_wires;
  };

}

#endif // LOGIC_ELEMENTS_H
