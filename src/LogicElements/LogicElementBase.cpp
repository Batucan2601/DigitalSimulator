#include "LogicElementBase.h"

namespace LogicElements
{
    std::map<GateType, Texture> logicElementTextures;

    void init_logicTextures()
    {
        std::string file_path = "assets/gates/test_and.png";  // Use relative path
        std::string full_path = (std::filesystem::path(PROJECT_ROOT_DIR) / file_path).string();
        logicElementTextures[GateType::AND] = LoadTexture(full_path.c_str());

        file_path = "assets/gates/test_or.png";  // Use relative path
        full_path = (std::filesystem::path(PROJECT_ROOT_DIR) / file_path).string();
        logicElementTextures[GateType::OR] = LoadTexture(full_path.c_str());

        file_path = "assets/gates/test_not.png";  // Use relative paths
        full_path = (std::filesystem::path(PROJECT_ROOT_DIR) / file_path).string();
        logicElementTextures[GateType::NOT] = LoadTexture(full_path.c_str());

        file_path = "assets/gates/test_xand.png";  // Use relative path
        full_path = (std::filesystem::path(PROJECT_ROOT_DIR) / file_path).string();
        logicElementTextures[GateType::XOR] = LoadTexture(full_path.c_str());

        file_path = "assets/gates/test_xor.png";  // Use relative path
        full_path = (std::filesystem::path(PROJECT_ROOT_DIR) / file_path).string();
        logicElementTextures[GateType::XAND] = LoadTexture(full_path.c_str());

        file_path = "assets/gates/test_not.png";  // Use relative path
        full_path = (std::filesystem::path(PROJECT_ROOT_DIR) / file_path).string();
        logicElementTextures[GateType::INPUT] = LoadTexture(full_path.c_str());
    }

    LogicGate::~LogicGate()
    {
        m_logger.info("LogicGate destroyed.");
        // UnloadTexture(m_texture);
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

    const std::unordered_map<std::string, bool>& LogicGate::getInputs() const
    {
        return inputs;
    }

    const std::unordered_map<std::string, bool>& LogicGate::getOutputs() const
    {
        return outputs;
    }

    void LogicGate::setInput(const std::string& name, bool value)
    {
        if (inputs.find(name) != inputs.end())
        {
            inputs[name] = value;
        }
    }

    bool LogicGate::getOutput(const std::string& name) const
    {
        auto it = outputs.find(name);
        return (it != outputs.end()) ? it->second : false;
    }

    // GatePosition &LogicGate::getPositionManager()
    // {
    //     return m_position;
    // }

}  // namespace LogicElements