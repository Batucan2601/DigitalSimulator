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

namespace LogicElements
{
    enum class GateType
    {
        AND,
        OR,
        NOT,
        XOR,
        XAND
    };

    class LogicGate
    {
    public:
        explicit LogicGate(std::string& logger_name) : m_logger(logger_name) {}
        void setPosition(float x, float y);
        Vector2 getPosition() const;

        ~LogicGate();
        virtual void evaluate() = 0;
        virtual void setInput(const std::string& name, bool value) = 0;
        virtual bool getOutput(const std::string& name) const = 0;

        const std::unordered_map<std::string, bool>& getInputs() const;
        const std::unordered_map<std::string, bool>& getOutputs() const;

        Rectangle bd = { 0, 0, 100, 100 }; // bounding box
        GateType type;
        Texture2D m_texture;

    protected:
        std::unordered_map<std::string, bool> inputs;
        std::unordered_map<std::string, bool> outputs;
        ClassLogger m_logger;
    };

    namespace Gates
    {
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

        class NotGate : public LogicGate
        {
        public:
            NotGate(std::string& logger_name);

            void evaluate() override;
            void setInput(const std::string& name, bool value) override;
            bool getOutput(const std::string& name) const override;
        };

        class XorGate : public LogicGate
        {
        public:
            XorGate(std::string& logger_name);

            void evaluate() override;
            void setInput(const std::string& name, bool value) override;
            bool getOutput(const std::string& name) const override;
        };

        class XandGate : public LogicGate
        {
        public:
            XandGate(std::string& logger_name);

            void evaluate() override;
            void setInput(const std::string& name, bool value) override;
            bool getOutput(const std::string& name) const override;
        };

    }
}

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
        Circuit(std::string& logger_name) : m_logger(logger_name) {}
        void addGate(std::shared_ptr<LogicElements::LogicGate> gate);
        void addConnection(std::shared_ptr<LogicElements::LogicGate> sourceGate, const std::string& sourceOutput,
            std::shared_ptr<LogicElements::LogicGate> targetGate, const std::string& targetInput);
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