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
#include "../Libraries/json.hpp"
#include "JsonSerializer.h"

namespace CircuitElements
{
    class Circuit;
    class Connection;
}
namespace LogicElements
{
    class Circuit; 
    class LogicGate : public Component // Inherit observer to get updates
    {
      public:
        LogicGate(CircuitElements::ComponentType componentType, std::string& logger_name);
        ~LogicGate();
        void onInputChanged() override;  // Override observer function
        void OnInputEvent(const InputEvent& event) override;
        bool CheckMouseOnInOut(
            const Vector2& mousePosition, CircuitElements::Connection& connection);
        ClassLogger m_logger;
        nlohmann::json serialize() const override;
        protected:
        void OnLeftClick(const InputEvent& event) override;

      private:
          bool is_connection_clicked(const Vector2& mousePos, CircuitElements::Connection& possibleConnection);
          void setInOutPositions() override;
    };
}  // namespace LogicElements

#endif  // LOGICGATEBASE_H