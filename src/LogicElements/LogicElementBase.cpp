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

    void OnInputEvent(const InputEvent& event) override {
        if (event.type == InputType::Mouse) {
            // Process mouse events
            switch (event.mouseState) {
            case MouseEventState::LeftClick:
                std::cout << "DigitalLogicComponent: Left Click at ("
                    << event.pos.x << ", " << event.pos.y << ")\n";
                break;
            case MouseEventState::RightClick:
                std::cout << "DigitalLogicComponent: Right Click at ("
                    << event.pos.x << ", " << event.pos.y << ")\n";
                break;
            case MouseEventState::Move:
                std::cout << "DigitalLogicComponent: Mouse Move at ("
                    << event.pos.x << ", " << event.pos.y << ")\n";
                break;
            default:
                std::cout << "DigitalLogicComponent: Other Mouse Event\n";
                break;
            }
        }
    }

}  // namespace LogicElements