#include "LogicElementBase.h"

#ifndef PROJECT_ROOT_DIR
#define PROJECT_ROOT_DIR "/path/to/project/root"  // Replace with the actual project root directory
#endif

namespace LogicElements
{
    std::map<GateType, Texture> logicElementTextures;
    std::shared_ptr<std::vector<GateInfo>> gateInfoList;

    void init_logicTextures()
    {
        init_OutlinedLogicTextures();
        init_FilledLogicTextures();

        gateInfoList = std::make_shared<std::vector<GateInfo>>();
        gateInfoList->push_back(GateInfo("AND Gate", GateType::AND,
                                         &logicElementTextures[GateType::AND],
                                         &logicElementTextures[GateType::AND_FILLED]));
        gateInfoList->push_back(GateInfo("OR Gate", GateType::OR,
                                         &logicElementTextures[GateType::OR],
                                         &logicElementTextures[GateType::OR_FILLED]));
        gateInfoList->push_back(GateInfo("NOT Gate", GateType::NOT,
                                         &logicElementTextures[GateType::NOT],
                                         &logicElementTextures[GateType::NOT_FILLED]));
        gateInfoList->push_back(GateInfo("XOR Gate", GateType::XOR,
                                         &logicElementTextures[GateType::XOR],
                                         &logicElementTextures[GateType::XOR_FILLED]));
        gateInfoList->push_back(GateInfo("XAND Gate", GateType::XAND,
                                         &logicElementTextures[GateType::XAND],
                                         &logicElementTextures[GateType::XAND_FILLED]));
        gateInfoList->push_back(GateInfo("INPUT Gate", GateType::INPUT,
                                         &logicElementTextures[GateType::INPUT],
                                         &logicElementTextures[GateType::INPUT_FILLED]));
    }

    void init_OutlinedLogicTextures()
    {
        std::string folder_path = "assets/gates/outlined_gates/";  // Use relative path
        std::string file_path;

        file_path = folder_path + "and.png";  // Use relative path
        std::string full_path = (std::filesystem::path(PROJECT_ROOT_DIR) / file_path).string();
        logicElementTextures[GateType::AND] = LoadTexture(full_path.c_str());

        file_path = folder_path + "or.png";  // Use relative path
        full_path = (std::filesystem::path(PROJECT_ROOT_DIR) / file_path).string();
        logicElementTextures[GateType::OR] = LoadTexture(full_path.c_str());

        file_path = folder_path + "not.png";  // Use relative path
        full_path = (std::filesystem::path(PROJECT_ROOT_DIR) / file_path).string();
        logicElementTextures[GateType::NOT] = LoadTexture(full_path.c_str());

        file_path = folder_path + "xand.png";  // Use relative path
        full_path = (std::filesystem::path(PROJECT_ROOT_DIR) / file_path).string();
        logicElementTextures[GateType::XOR] = LoadTexture(full_path.c_str());

        file_path = folder_path + "xor.png";  // Use relative path
        full_path = (std::filesystem::path(PROJECT_ROOT_DIR) / file_path).string();
        logicElementTextures[GateType::XAND] = LoadTexture(full_path.c_str());

        file_path = folder_path + "not.png";  // Use relative path
        full_path = (std::filesystem::path(PROJECT_ROOT_DIR) / file_path).string();
        logicElementTextures[GateType::INPUT] = LoadTexture(full_path.c_str());
    }
    void init_FilledLogicTextures()
    {
        std::string folder_path = "assets/gates/filled_gates/";  // Use relative path
        std::string file_path;
        std::string full_path = (std::filesystem::path(PROJECT_ROOT_DIR) / file_path).string();

        file_path = folder_path + "and.png";  // Use relative path
        full_path = (std::filesystem::path(PROJECT_ROOT_DIR) / file_path).string();
        logicElementTextures[GateType::AND_FILLED] = LoadTexture(full_path.c_str());

        file_path = folder_path + "or.png";  // Use relative path
        full_path = (std::filesystem::path(PROJECT_ROOT_DIR) / file_path).string();
        logicElementTextures[GateType::OR_FILLED] = LoadTexture(full_path.c_str());

        file_path = folder_path + "not.png";  // Use relative path
        full_path = (std::filesystem::path(PROJECT_ROOT_DIR) / file_path).string();
        logicElementTextures[GateType::NOT_FILLED] = LoadTexture(full_path.c_str());

        file_path = folder_path + "xand.png";  // Use relative path
        full_path = (std::filesystem::path(PROJECT_ROOT_DIR) / file_path).string();
        logicElementTextures[GateType::XOR_FILLED] = LoadTexture(full_path.c_str());

        file_path = folder_path + "xor.png";  // Use relative path
        full_path = (std::filesystem::path(PROJECT_ROOT_DIR) / file_path).string();
        logicElementTextures[GateType::XAND_FILLED] = LoadTexture(full_path.c_str());
    }

    LogicGate::LogicGate(GateType gateType, std::string& logger_name)
        : m_type(gateType), m_logger(logger_name)
    {
        // type = gateType;
        m_texture = logicElementTextures[gateType];
        m_logger.info("LogicGate created as type: " + std::to_string(static_cast<int>(m_type)));
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
            notifyObservers();
        }
    }

    bool LogicGate::getOutput(const std::string& name) const
    {
        auto it = outputs.find(name);
        return (it != outputs.end()) ? it->second : false;
    }

    void LogicGate::setEvaluationFunction(std::function<void(LogicGate&)> evalFunc)
    {
        evaluateFunction = evalFunc;
    }

    void LogicGate::evaluate()
    {
        if (evaluateFunction)
        {
            evaluateFunction(*this);
        }
    }

    GateType LogicGate::getType() const
    {
        return m_type;
    }

    const Texture2D& LogicGate::getTexture() const
    {
        return m_texture;
    }

    // GatePosition &LogicGate::getPositionManager()
    // {
    //     return m_position;
    // }

    void LogicGate::addObserver(GateObserver* observer)
    {
        observers.insert(observer);
    }

    void LogicGate::removeObserver(GateObserver* observer)
    {
        observers.erase(observer);
    }

    void LogicGate::notifyObservers()
    {
        for (auto observer : observers)
        {
            observer->onInputChanged();
        }
    }

    void LogicGate::onInputChanged()
    {
        evaluate();  // Automatically reevaluate when input changes
    }

}  // namespace LogicElements