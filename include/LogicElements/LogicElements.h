#ifndef LOGIC_ELEMENTS_H
#define LOGIC_ELEMENTS_H

#include "ClassLogger.h"
#include "LogicElementBase.h"
#include "raylib.h"

#include <filesystem>
#include <memory>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <vector>

namespace CircuitElements
{
    struct HoveringWire
    {
        bool is_hovering;
        Vector2 pos;
    };
    struct PhysicalConnection 
    {
        std::vector<Vector2> wires;
    };
    class Connection : public IInputHandler
    {
    public:
        std::shared_ptr<LogicElements::LogicGate> sourceGate;
        std::string sourceLogic;
        std::shared_ptr<LogicElements::LogicGate> targetGate;
        std::string targetLogic;
        PhysicalConnection physCon;
        HoveringWire hovering;
        Circuit* circuit;
        bool is_connected = false;
        void OnInputEvent(const InputEvent& event) override;
        void OnLeftClick(const InputEvent& event);
        void OnMove(const InputEvent& event);

    };
    class ActiveWire : public IInputHandler
    {
    public:
        Vector2 start;
        Vector2 end;
        bool is_visible;
        void OnInputEvent(const InputEvent& event) override;
    private:
        void OnMove(const InputEvent& event);
        void OnLeftClick(const InputEvent& event);
        void OnRightClick(const InputEvent& event);
    };
    struct SelectedWires
    {
        std::vector<Vector2> selected_wires;
        Vector2 wire_hovering;
    };
    class Circuit
    {
      public:
        Circuit(std::string& logger_name) : m_logger(logger_name)
        {
            this->connections.reserve(1000);
        }
        void addGate(std::shared_ptr<LogicElements::LogicGate> gate);
        void addConnection(std::shared_ptr<LogicElements::LogicGate> sourceGate,
                           const std::string& sourceOutput,
                           std::shared_ptr<LogicElements::LogicGate> targetGate,
                           const std::string& targetInput);
        void evaluate();
        ClassLogger m_logger;

        std::vector<std::shared_ptr<LogicElements::LogicGate>> gates;
        // std::shared_ptr<std::vector<LogicElements::LogicGate> gates;
        std::vector<Connection> connections;
        // TODO
        // this might be moved to a better data structure
        ActiveWire active_wire = {};
        SelectedWires selected_wires;

        bool is_GUIdragdropped = false;
        bool is_GUIdragdragging = false;
    };

}  // namespace CircuitElements

#endif  // LOGIC_ELEMENTS_H
