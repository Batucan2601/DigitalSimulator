#ifndef LOGICGATEBASE_H
#define LOGICGATEBASE_H

#include "ClassLogger.h"
#include "Component.h"
#include "raylib.h"

#include <GatePosition.h>
#include <filesystem>
#include <functional>
#include <gateObserver.h>
#include <map>
#include <unordered_map>
#include <unordered_set>

namespace CircuitElements
{
    class Circuit;
    class Connection;
}
namespace LogicElements
{
    class Circuit; 
    enum class GateType
    {
        NONE,
        AND,
        AND_FILLED,
        OR,
        OR_FILLED,
        NOT,
        NOT_FILLED,
        XOR,
        XOR_FILLED,
        XAND,
        XAND_FILLED,
        INPUT,
        INPUT_FILLED,
    };

    struct GateInfo
    {
        std::string name;
        GateType type;             // Name of the gate (e.g., "AND Gate")
        Texture* outlinedTexture;  // Default texture
        Texture* filledTexture;    // Alternative texture (e.g., highlighted version)

        GateInfo(std::string name, GateType type, Texture* outlinedText, Texture* filledTex)
            : name(name), type(std::move(type)), outlinedTexture(outlinedText),
              filledTexture(filledTex)
        {
        }
    };

    extern std::shared_ptr<std::vector<GateInfo>> gateInfoList;
    extern std::map<LogicElements::GateType, Texture> logicElementTextures;

    void init_logicTextures();
    void init_OutlinedLogicTextures();
    void init_FilledLogicTextures();
    class LogicGate : public GateObserver , public IInputHandler ,public std::enable_shared_from_this<LogicGate>  // Inherit observer to get updates
    {
      public:
        LogicGate(GateType gateType, std::string& logger_name);
        ~LogicGate();

        void evaluate();

        void setInput(const std::string& name, bool value);
        bool getOutput(const std::string& name) const;

        const std::unordered_map<std::string, bool>& getInputs() const;
        const std::unordered_map<std::string, bool>& getOutputs() const;

        GatePosition& getPositionManager();  // Access GatePosition
        GateType getType() const;
        const Texture2D& getTexture() const;

        GateType m_type;
        Texture2D m_texture;

        void setEvaluationFunction(std::function<void(LogicGate&)> evalFunc);

        Rectangle bd = {0, 0, 100, 100};  // bounding box
        void setPosition(float x, float y);
        Vector2 getPosition() const;

        void addObserver(GateObserver* observer);
        void removeObserver(GateObserver* observer);
        void notifyObservers();

        void onInputChanged() override;  // Override observer function

        // protected:
        std::unordered_map<std::string, bool> inputs;
        std::unordered_map<std::string, bool> outputs;
        // GatePosition m_position; // Manage position and bounding box
        ClassLogger m_logger;
        CircuitElements::Circuit* circuit;

        void OnInputEvent(const InputEvent& event) override;
        void CheckGatePartClicked(
            const Vector2& mousePosition, CircuitElements::Connection& connection);
      protected:
        void OnLeftClick(const InputEvent& event);
        void OnDown(const InputEvent& event);
        void OnRelease(const InputEvent& event);
        void OnMove(const InputEvent& event);
        void OnRightClick(const InputEvent& event);

        std::unordered_set<GateObserver*> observers;       // Stores registered observers
        std::function<void(LogicGate&)> evaluateFunction;  // Stores gate logic
      private:
          bool is_connection_clicked(const Vector2& mousePos, CircuitElements::Connection& possibleConnection);

    };
}  // namespace LogicElements

#endif  // LOGICGATEBASE_H