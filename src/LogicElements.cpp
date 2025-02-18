#include "LogicElements.h"

namespace LogicElements
{
    std::map<GateType, Texture> logicElementTextures;
    void init_logicTextures()
    {
        
        std::string file_path = "assets/gates/test_and.png"; // Use relative path
        std::string full_path = (std::filesystem::path(PROJECT_ROOT_DIR) / file_path).string();
        logicElementTextures[GateType::AND] = LoadTexture(full_path.c_str());
        file_path = "assets/gates/test_or.png"; // Use relative path
        full_path = (std::filesystem::path(PROJECT_ROOT_DIR) / file_path).string();
        logicElementTextures[GateType::OR] = LoadTexture(full_path.c_str());
        file_path = "assets/gates/test_not.png"; // Use relative paths
        full_path = (std::filesystem::path(PROJECT_ROOT_DIR) / file_path).string();
        logicElementTextures[GateType::NOT] = LoadTexture(full_path.c_str());
        file_path = "assets/gates/test_xand.png"; // Use relative path
        full_path = (std::filesystem::path(PROJECT_ROOT_DIR) / file_path).string();
        logicElementTextures[GateType::XOR] = LoadTexture(full_path.c_str());
        file_path = "assets/gates/test_xor.png"; // Use relative path
        full_path = (std::filesystem::path(PROJECT_ROOT_DIR) / file_path).string();
        logicElementTextures[GateType::XAND] = LoadTexture(full_path.c_str());
        file_path = "assets/gates/test_not.png"; // Use relative path
        full_path = (std::filesystem::path(PROJECT_ROOT_DIR) / file_path).string();
        logicElementTextures[GateType::INPUT] = LoadTexture(full_path.c_str());
    }
    LogicGate::~LogicGate()
    {
        m_logger.info("LogicGate destroyed.");
        UnloadTexture(m_texture);
    }

    void LogicGate::setPosition(float x, float y)
    {
        bd.x = x;
        bd.y = y;
    }

    Vector2 LogicGate::getPosition() const
    {
        return {bd.x, bd.y};
    }

    const std::unordered_map<std::string, bool> &LogicGate::getInputs() const
    {
        return inputs;
    }

    const std::unordered_map<std::string, bool> &LogicGate::getOutputs() const
    {
        return outputs;
    }

    namespace Gates
    {
        AndGate::AndGate(std::string &logger_name) : LogicGate(logger_name)
        {
            inputs["A"] = false;
            inputs["B"] = false;
            outputs["Out"] = false;

            type = GateType::AND;
            m_logger.info("And Gate Created.");
            m_texture = logicElementTextures[LogicElements::GateType::AND];
        }

        void AndGate::evaluate()
        {
            auto& out = outputs["Out"];
            for (auto const& [key, val] : inputs)
            {
                if (!out) break;
                out = out && val;
            }
        }

        void AndGate::setInput(const std::string &name, bool value)
        {
            if (inputs.find(name) != inputs.end())
            {
                inputs[name] = value;
            }
        }

        bool AndGate::getOutput(const std::string &name) const
        {
            auto it = outputs.find(name);
            return (it != outputs.end()) ? it->second : false;
        }

        OrGate::OrGate(std::string &logger_name) : LogicGate(logger_name)
        {
            inputs["A"] = false;
            inputs["B"] = false;
            outputs["Out"] = false;
            type = GateType::OR;
            m_logger.info("Or Gate Created.");
            m_texture = logicElementTextures[LogicElements::GateType::OR];
        }

        void OrGate::evaluate()
        {
            auto& out = outputs["Out"];
            for (auto const& [key, val] : inputs)
            {
                if(out) break; 
                out = out || val;
            }
        }

        void OrGate::setInput(const std::string &name, bool value)
        {
            if (inputs.find(name) != inputs.end())
            {
                inputs[name] = value;
            }
        }

        bool OrGate::getOutput(const std::string &name) const
        {
            auto it = outputs.find(name);
            return (it != outputs.end()) ? it->second : false;
        }

        NotGate::NotGate(std::string &logger_name) : LogicGate(logger_name)
        {
            inputs["In"] = false;
            outputs["Out"] = false;
            type = GateType::NOT;
            m_logger.info("Not Gate Created.");
            m_texture = logicElementTextures[LogicElements::GateType::NOT];

        }

        void NotGate::evaluate()
        {
            outputs["Out"] = !inputs["In"];
        }

        void NotGate::setInput(const std::string &name, bool value)
        {
            if (inputs.find(name) != inputs.end())
            {
                inputs[name] = value;
            }
        }

        bool NotGate::getOutput(const std::string &name) const
        {
            auto it = outputs.find(name);
            return (it != outputs.end()) ? it->second : false;
        }

        XorGate::XorGate(std::string &logger_name) : LogicGate(logger_name)
        {
            inputs["A"] = false;
            inputs["B"] = false;
            outputs["Out"] = false;
            type = GateType::XOR;
            m_logger.info("Xor Gate Created.");
            m_texture = logicElementTextures[LogicElements::GateType::XOR];

        }

        void XorGate::evaluate()
        {
            auto& out = outputs["Out"];
            for (auto const& [key, val] : inputs)
            {
                if (!out) break;
                out = out ^ val;
            }
        }

        void XorGate::setInput(const std::string &name, bool value)
        {
            if (inputs.find(name) != inputs.end())
            {
                inputs[name] = value;
            }
        }

        bool XorGate::getOutput(const std::string &name) const
        {
            auto it = outputs.find(name);
            return (it != outputs.end()) ? it->second : false;
        }

        XandGate::XandGate(std::string &logger_name) : LogicGate(logger_name)
        {
            inputs["A"] = false;
            inputs["B"] = false;
            outputs["Out"] = false;
            type = GateType::XAND;
            m_logger.info("Xand Gate Created.");
            m_texture = logicElementTextures[LogicElements::GateType::XAND];

        }

        void XandGate::evaluate()
        {
            //thi is NAND logic
            auto& out = outputs["Out"];
            bool allTrue = true;  // Assume all inputs are true initially.
            for (auto const& [name, value] : inputs) {
                if (!value) {    // As soon as one input is false...
                    allTrue = false;
                    break;       // ...we can stop checking.
                }
            }
            out = !allTrue;  // NAND: output is true if any input is false.
        }

        void XandGate::setInput(const std::string &name, bool value)
        {
            if (inputs.find(name) != inputs.end())
            {
                inputs[name] = value;
            }
        }

        bool XandGate::getOutput(const std::string &name) const
        {
            auto it = outputs.find(name);
            return (it != outputs.end()) ? it->second : false;
        }

        InputGate::InputGate(std::string& logger_name) : LogicGate(logger_name)
        {
            m_texture = logicElementTextures[LogicElements::GateType::NOT];
            InputGate::setInput("Out", 1);
        }
        void InputGate::evaluate()
        {
            return; 
        }

        void InputGate::setInput(const std::string& name, bool value) 
        {
            outputs["Out"] = value;
        }
        bool InputGate::getOutput(const std::string& name) const
        {
            return outputs.at("Out");
        }
    }
}
namespace CircuitElements
{
    void Circuit::addGate(std::shared_ptr<LogicElements::LogicGate> gate)
    {
        this->m_logger.info("Gate added to the circuit.");
        gates.push_back(gate);
    }

    void Circuit::addConnection(std::shared_ptr<LogicElements::LogicGate> sourceGate, const std::string &sourceOutput,
                                std::shared_ptr<LogicElements::LogicGate> targetGate, const std::string &targetInput)
    {
        this->m_logger.info("Connection added to the circuit.");
        connections.push_back({sourceGate, sourceOutput, targetGate, targetInput});
    }

    void Circuit::evaluate()
    {
        bool stabilized = false;
        int iterations = 0;
        const int maxIterations = 100; // Prevent infinite loops

        while (!stabilized && iterations < maxIterations)
        {
            stabilized = true;
            for (auto &gate : gates)
            {
                gate->evaluate();
                auto previousOutputs = gate->getOutputs();
                gate->evaluate();
                if (gate->getOutputs() != previousOutputs)
                {
                    stabilized = false;
                }
            }
            // Then, update the inputs based on the connections.
            for (auto &conn : connections)
            {
                bool sourceValue = conn.sourceGate->getOutput(conn.sourceLogic);
                if (conn.targetLogic != "")
                {
                    conn.targetGate->setInput(conn.targetLogic, sourceValue);
                }
            }
            iterations++;
        }
        if (iterations == maxIterations)
        {
            // Handle infinite loop case
            throw std::runtime_error("Circuit evaluation did not stabilize.");
        }
    } 


    
}
