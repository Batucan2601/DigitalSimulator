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
    class LogicGate : public Component // Inherit observer to get updates
    {
      public:
        LogicGate(CircuitElements::ComponentType componentType, std::string& logger_name);
        ~LogicGate();

        GatePosition& getPositionManager();  // Access GatePosition
        CircuitElements::ComponentType getType() const;
        const Texture2D& getTexture() const;
        CircuitElements::ComponentType m_type;
        Vector2 getPosition() const;
        void onInputChanged() override;  // Override observer function
        ClassLogger m_logger;
        void OnInputEvent(const InputEvent& event) override;
        bool CheckMouseOnInOut(
            const Vector2& mousePosition, CircuitElements::Connection& connection);

      protected:
        void OnLeftClick(const InputEvent& event) override;
        void OnDown(const InputEvent& event) override;
        void OnRelease(const InputEvent& event) override;
        void OnMove(const InputEvent& event) override;
        void OnRightClick(const InputEvent& event) override;
        void OnEnter(const InputEvent& event) override;
        void OnExit(const InputEvent& event) override;
        void OnKeyPress(const InputEvent& event) override;

      private:
          bool is_connection_clicked(const Vector2& mousePos, CircuitElements::Connection& possibleConnection);
          void setInOutPositions() override;
    };
}  // namespace LogicElements

#endif  // LOGICGATEBASE_H