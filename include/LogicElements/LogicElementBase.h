#ifndef LOGICGATEBASE_H
#define LOGICGATEBASE_H

#include "ClassLogger.h"
#include "raylib.h"

#include <GatePosition.h>
#include <filesystem>
#include <gateObserver.h>
#include <map>
#include <unordered_map>

namespace LogicElements
{
    enum class GateType
    {
        NONE,
        AND,
        OR,
        NOT,
        XOR,
        XAND,
        INPUT
    };

    extern std::map<LogicElements::GateType, Texture> logicElementTextures;
    void init_logicTextures();
    class LogicGate : public GateObserver  // Inherit observer to get updates
    {
      public:
        explicit LogicGate(std::string& logger_name) : m_logger(logger_name) {}
        ~LogicGate();

        virtual void evaluate() = 0;

        void setInput(const std::string& name, bool value);
        bool getOutput(const std::string& name) const;

        const std::unordered_map<std::string, bool>& getInputs() const;
        const std::unordered_map<std::string, bool>& getOutputs() const;

        GatePosition& getPositionManager();  // Access GatePosition

        GateType type;
        Texture2D m_texture;

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

      protected:
        std::unordered_set<GateObserver*> observers;       // Stores registered observers
    };
}  // namespace LogicElements

#endif  // LOGICGATEBASE_H