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
    extern std::shared_ptr<std::vector<CircuitElements::ComponentInfo>> componentInfoList;
    extern std::map<CircuitElements::ComponentType, Texture> logicElementTextures;

    void init_logicTextures();
    void init_OutlinedLogicTextures();
    void init_FilledLogicTextures();
    class LogicGate : public Component,public std::enable_shared_from_this<LogicGate>  // Inherit observer to get updates
    {
      public:
        LogicGate(CircuitElements::ComponentType componentType, std::string& logger_name);
        ~LogicGate();

        void setInput(const std::string& name, bool value);
        bool getOutput(const std::string& name) const;

        const std::vector<Signal>& getInputs() const;
        const std::vector<Signal>& getOutputs() const;

        GatePosition& getPositionManager();  // Access GatePosition
        CircuitElements::ComponentType getType() const;
        const Texture2D& getTexture() const;
        int getID() const;

        CircuitElements::ComponentType m_type;



        void setPosition(float x, float y);
        Vector2 getPosition() const;


        void onInputChanged() override;  // Override observer function

        // protected:

        // GatePosition m_position; // Manage position and bounding box
        ClassLogger m_logger;
        //CircuitElements::Circuit* circuit;



        void OnInputEvent(const InputEvent& event) override;
        bool CheckMouseOnInOut(
            const Vector2& mousePosition, CircuitElements::Connection& connection);

      protected:
        void OnLeftClick(const InputEvent& event);
        void OnDown(const InputEvent& event);
        void OnRelease(const InputEvent& event);
        void OnMove(const InputEvent& event);
        void OnRightClick(const InputEvent& event);
        void OnEnter(const InputEvent& event);
        void OnExit(const InputEvent& event);
        void OnKeyPress(const InputEvent& event);

      private:
          bool is_connection_clicked(const Vector2& mousePos, CircuitElements::Connection& possibleConnection);
          void setInOutPositions();
      private:
        int id;
    };
}  // namespace LogicElements

#endif  // LOGICGATEBASE_H