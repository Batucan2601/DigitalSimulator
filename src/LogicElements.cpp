#include "LogicElements.h"

namespace LogicElements
{
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

            // Construct the full path for the image
            std::string file_path = "assets/gates/test_and.png"; // Use relative path
            std::string full_path = (std::filesystem::path(PROJECT_ROOT_DIR) / file_path).string();

            // Check if the file exists
            if (!std::filesystem::exists(full_path))
            {
                m_logger.error("File does not exist: ", full_path);
                throw std::runtime_error("Failed to find file: " + full_path);
            }
            // Load image and texture
            Image image = LoadImage(full_path.c_str());
            if (!image.data)
            {
                m_logger.error("Failed to load image: ", full_path);
                throw std::runtime_error("Failed to load image: " + full_path);
            }

            m_texture = LoadTextureFromImage(image);
            if (!m_texture.id)
            {
                m_logger.error("Failed to load texture from image: ", full_path);
                UnloadImage(image); // Free resources if texture loading fails
                throw std::runtime_error("Failed to load texture from image: " + full_path);
            }
            UnloadImage(image); // Free the image from RAM after loading into VRAM
        }

        void AndGate::evaluate()
        {
            outputs["Out"] = inputs["A"] && inputs["B"];
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

            // Construct the full path for the image
            std::string file_path = "assets/gates/test_or.png"; // Use relative path
            std::string full_path = (std::filesystem::path(PROJECT_ROOT_DIR) / file_path).string();

            // Check if the file exists
            if (!std::filesystem::exists(full_path))
            {
                m_logger.error("File does not exist: ", full_path);
                throw std::runtime_error("Failed to find file: " + full_path);
            }

            // Load image and texture
            Image image = LoadImage(full_path.c_str());
            if (!image.data)
            {
                m_logger.error("Failed to load image: ", full_path);
                throw std::runtime_error("Failed to load image: " + full_path);
            }

            m_texture = LoadTextureFromImage(image);
            if (!m_texture.id)
            {
                m_logger.error("Failed to load texture from image: ", full_path);
                UnloadImage(image); // Free resources if texture loading fails
                throw std::runtime_error("Failed to load texture from image: " + full_path);
            }
        }

        void OrGate::evaluate()
        {
            outputs["Out"] = inputs["A"] || inputs["B"];
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

            // Construct the full path for the image
            std::string file_path = "assets/gates/test_not.png"; // Use relative path
            std::string full_path = (std::filesystem::path(PROJECT_ROOT_DIR) / file_path).string();

            // Check if the file exists
            if (!std::filesystem::exists(full_path))
            {
                m_logger.error("File does not exist: ", full_path);
                throw std::runtime_error("Failed to find file: " + full_path);
            }

            // Load image and texture
            Image image = LoadImage(full_path.c_str());
            if (!image.data)
            {
                m_logger.error("Failed to load image: ", full_path);
                throw std::runtime_error("Failed to load image: " + full_path);
            }

            m_texture = LoadTextureFromImage(image);
            if (!m_texture.id)
            {
                m_logger.error("Failed to load texture from image: ", full_path);
                UnloadImage(image); // Free resources if texture loading fails
                throw std::runtime_error("Failed to load texture from image: " + full_path);
            }
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

            // Construct the full path for the image
            std::string file_path = "assets/gates/test_xor.png"; // Use relative path
            std::string full_path = (std::filesystem::path(PROJECT_ROOT_DIR) / file_path).string();

            // Check if the file exists
            if (!std::filesystem::exists(full_path))
            {
                m_logger.error("File does not exist: ", full_path);
                throw std::runtime_error("Failed to find file: " + full_path);
            }

            // Load image and texture
            Image image = LoadImage(full_path.c_str());
            if (!image.data)
            {
                m_logger.error("Failed to load image: ", full_path);
                throw std::runtime_error("Failed to load image: " + full_path);
            }

            m_texture = LoadTextureFromImage(image);
            if (!m_texture.id)
            {
                m_logger.error("Failed to load texture from image: ", full_path);
                UnloadImage(image); // Free resources if texture loading fails
                throw std::runtime_error("Failed to load texture from image: " + full_path);
            }
        }

        void XorGate::evaluate()
        {
            outputs["Out"] = inputs["A"] ^ inputs["B"];
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

            // Construct the full path for the image
            std::string file_path = "assets/gates/test_xand.png"; // Use relative path
            std::string full_path = (std::filesystem::path(PROJECT_ROOT_DIR) / file_path).string();

            // Check if the file exists
            if (!std::filesystem::exists(full_path))
            {
                m_logger.error("File does not exist: ", full_path);
                throw std::runtime_error("Failed to find file: " + full_path);
            }

            // Load image and texture
            Image image = LoadImage(full_path.c_str());
            if (!image.data)
            {
                m_logger.error("Failed to load image: ", full_path);
                throw std::runtime_error("Failed to load image: " + full_path);
            }

            m_texture = LoadTextureFromImage(image);
            if (!m_texture.id)
            {
                m_logger.error("Failed to load texture from image: ", full_path);
                UnloadImage(image); // Free resources if texture loading fails
                throw std::runtime_error("Failed to load texture from image: " + full_path);
            }
        }

        void XandGate::evaluate()
        {
            outputs["Out"] = !(inputs["A"] && inputs["B"]);
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
                conn.targetGate->setInput(conn.targetLogic, sourceValue);
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
