#ifndef COMPONENT_H
#define COMPONENT_H
#include <algorithm>
#include <functional>
#include <list>
#include <queue>
#include <raylib.h>
#include <string>
#include <vector>
#include "gateObserver.h"
#include <unordered_set>
#include "ClassLogger.h"
#include <GatePosition.h>
#include <filesystem>
#include <functional>
#include <map>
#include <unordered_map>
#include <unordered_set>
#include "ClassLogger.h"
#include "Signal.h"
#include "../Libraries/json.hpp"

class CircuitController;
// Enum to identify the type of input event.
enum class InputType
{
    None,
    Mouse,
    Keyboard
};

// Enums for mouse and keyboard event states.
enum class MouseEventState
{
    None,
    LeftClick,
    RightClick,
    Move,
    Enter,
    Leave,
    Hover,
    Down,
    Release
};

enum class KeyboardEvent
{
    None,
    KeyPress,
    KeyRelease,
    KeyRepeat
};

// Structure representing a 2pD coordinate.
enum class DragMode { Normal, MarqueeSelecting, DraggingSelection };

// Structure to hold details for a unified input event.
struct InputEvent
{
    InputType type = InputType::None;
    // For mouse events
    MouseEventState mouseState = MouseEventState::None;
    Vector2 pos = {0, 0};
    // For keyboard events
    KeyboardEvent keyState = KeyboardEvent::None;
    bool shift=false, ctrl=false, alt=false;
    bool consumed = false; // if no component got that
    int keyCode = 0;
};

// Unified input handler interface.
class IInputHandler
{
  public:
    virtual ~IInputHandler() = default;

    // Handles any input event, whether mouse or keyboard.
    virtual void OnInputEvent(InputEvent& event) = 0;
};

class InputResolver
{
  public:
    static void Init();
    // Add a new event to the queue.
    static void PushEvent(const InputEvent& event);

    // Register an input handler.
    static void RegisterHandler(std::weak_ptr<IInputHandler> handler);

    // Unregister an input handler (optional but useful).
    static void UnregisterHandler(std::weak_ptr<IInputHandler> handler);

    static bool isStillRegistered(std::weak_ptr<IInputHandler> handler);
    // Process all queued events.
    static void resolve();

    static std::vector<std::weak_ptr<IInputHandler>> getSelectedHandler();
    
    static void setSelectedHandler(std::vector<std::weak_ptr<IInputHandler>> handler);
    
    static DragMode getDragMode();

    static void setDragMode(DragMode dMode);
    
    static bool isBlocked()
    {
        return m_blocked;
    }
    static void Block()
    {
        m_blocked = true;
    }
    static void Unblock()
    {
        m_blocked = false;
    }
    static std::list<std::weak_ptr<IInputHandler>> handlers;  // Collection of input handlers.
  private:
    static std::queue<InputEvent> queue;
    static std::vector<std::weak_ptr<IInputHandler>> selectedHandler;
    inline static DragMode dragMode; 
    static bool m_blocked; 
    // You can keep additional helper functions if needed.
};



namespace CircuitElements
{
    class Circuit;
    enum class ComponentType
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
        NOR,
        INPUT,
        INPUT_FILLED,
        INPUT_0,
        INPUT_1,
        CLK
    };

    struct ComponentInfo
    {
        std::string name;
        ComponentType type;             // Name of the gate (e.g., "AND Gate")
        Texture* outlinedTexture;  // Default texture
        Texture* filledTexture;    // Alternative texture (e.g., highlighted version)

        ComponentInfo(std::string name, CircuitElements::ComponentType type, Texture* outlinedText, Texture* filledTex)
            : name(name), type(std::move(type)), outlinedTexture(outlinedText),
              filledTexture(filledTex)
        {
        }
    };
}
namespace CircuitElements {
    class Connection;
}

class Component : public LogicElements::GateObserver ,  public IInputHandler , public std::enable_shared_from_this<Component>
{
  public:
    Component(const std::string& logger_name)
    : m_logger(logger_name), m_name(logger_name)
    {
        
    }
    Component(std::string& fileName);
    virtual void OnInputEvent(InputEvent& event) override;
    void setInput(const std::string& name, std::vector<SignalVal>  value);
    std::vector<SignalVal> getOutput(const std::string& name) const;
    void addObserver(LogicElements::GateObserver* observer);
    void removeObserver(LogicElements::GateObserver* observer);
    void notifyObservers();
    const std::vector<Signal>& getInputs() const;
    const std::vector<Signal>& getOutputs() const;
    void setEvaluationFunction(std::function<void(Component&)> evalFunc);
    virtual void evaluate();
    bool is_connection_clicked(const Vector2& mousePos,
    CircuitElements::Connection& possibleConnection);
    bool CheckMouseOnInOut(const Vector2& mousePosition,
    CircuitElements::Connection& connection);
    const Texture2D& getTexture() const;
    Rectangle bd = {0, 0, 100, 100};  // bounding box
    int getID() const; 
    Vector2 getPosition() const;
    void setPosition(float x, float y);
    int getInputByName(std::string name) const;
    int getOutputByName(std::string name) const;
    CircuitElements::ComponentType getType() const;
    ClassLogger m_logger; 
    std::vector<Signal> inputs;
    std::vector<Signal> outputs;
    CircuitElements::Circuit* circuit;
    int id;
    CircuitElements::ComponentType m_type;
    Texture2D m_texture;
    std::string m_name; // official name of component, e.g. "my Gate"
    bool m_mark_for_deletion = false; // Flag to mark component for deletion
    bool is_hovered = false; 
    std::unordered_set<GateObserver*> observers;       // Stores registered observers
    std::function<void(Component&)> evaluateFunction;  // Stores gate logic
    std::shared_ptr<CircuitController> controller; // Pointer to the CircuitController for managing circuit operations
    virtual nlohmann::json serialize() const = 0;
    protected:
        virtual void OnLeftClick(const InputEvent& event);
        virtual void OnDown(InputEvent& event);
        virtual void OnRelease(const InputEvent& event);
        virtual void OnMove(const InputEvent& event);
        virtual void OnRightClick(const InputEvent& event);
        virtual void OnEnter(const InputEvent& event);
        virtual void OnExit(const InputEvent& event);
        virtual void OnKeyPress(const InputEvent& event);
    private:
    virtual void setInOutPositions() = 0;  // Pure virtual — must be implemented in derived classes
    std::shared_ptr<Component> hoveredGate;


    
};
#endif