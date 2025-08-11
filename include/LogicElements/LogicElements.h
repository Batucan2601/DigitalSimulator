#ifndef LOGIC_ELEMENTS_H
#define LOGIC_ELEMENTS_H

#include "ClassLogger.h"
#include "LogicElementBase.h"
#include "appSettings.h"
#include "raylib.h"

#include <filesystem>
#include <fstream>
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
        std::shared_ptr<Component> sourceGate;
        std::string sourceLogic;
        std::shared_ptr<Component> targetGate;
        std::string targetLogic;
        PhysicalConnection physCon;
        HoveringWire hovering{
            false,
            {0.0f, 0.0f}};  // when this variable is uninitialized, it
                            // causes a crash when rendering the is_hovering wires in the circuit
        Circuit* circuit;   // = nullptr;
        bool is_connected = false;
        void OnInputEvent(const InputEvent& event) override;
        void OnLeftClick(const InputEvent& event);
        void OnRightClick(const InputEvent& event);
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
            this->hoveredGate = nullptr;
            this->connections.reserve(1000);
        }
        void addGate(std::shared_ptr<Component> gate);
        void addConnection(std::shared_ptr<Component> sourceGate,
                           const std::string& sourceOutput,
                           std::shared_ptr<Component> targetGate,
                           const std::string& targetInput);
        void evaluate();
        int giveNewId();
        ClassLogger m_logger;

        std::vector<std::shared_ptr<Component>> gates;
        // std::shared_ptr<std::vector<LogicElements::LogicGate> gates;
        std::vector<Connection> connections;
        // TODO
        // this might be moved to a better data structure
        ActiveWire active_wire = {};
        SelectedWires selected_wires;

        bool is_GUIdragdropped = false;
        bool is_GUIdragdragging = false;
        std::shared_ptr<Component> hoveredGate;
        std::string file_path; 
        int id;
        private:
        void removeComponent();
    };

}  // namespace CircuitElements

#endif  // LOGIC_ELEMENTS_H
