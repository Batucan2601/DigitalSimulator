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
#include <logicElementFactory.h>

namespace CircuitElements
{

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
    class Circuit: public std::enable_shared_from_this<Circuit>
    {
      public:
        Circuit(std::string& logger_name) : m_logger(logger_name)
        {
            this->hoveredGate = nullptr;
            this->connections.reserve(1000);
            //LogicElements::LogicElementFactory::initFactory(shared_from_this());
        }
        void addComponent(std::shared_ptr<Component> gate);
        std::shared_ptr<Component> Circuit::getMainComponent();
        void addConnection(std::shared_ptr<LogicElements::LogicGate> sourceGate,
                           const std::string& sourceOutput,
                           std::shared_ptr<LogicElements::LogicGate> targetGate,
                           const std::string& targetInput);
        void evaluate();
        ClassLogger m_logger;
        std::vector<std::shared_ptr<Component>> components;
        // std::shared_ptr<std::vector<LogicElements::LogicGate> gates;
        std::vector<Connection> connections;
        // TODO
        // this might be moved to a better data structure
        ActiveWire active_wire = {};
        SelectedWires selected_wires;
        LogicElements::LogicElementFactory factory;

        bool is_GUIdragdropped = false;
        bool is_GUIdragdragging = false;
        std::shared_ptr<LogicElements::LogicGate> hoveredGate;
    };

}  // namespace CircuitElements

#endif  // LOGIC_ELEMENTS_H
