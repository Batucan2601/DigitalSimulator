#ifndef COMPONENT_H
#define COMPONENT_H
#include <algorithm>
#include <functional>
#include <list>
#include <memory>
#include <queue>
#include <raylib.h>
#include <string>
#include <vector>
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

// Structure representing a 2D coordinate.
struct MousePosition
{
    int x;
    int y;
};

// Structure to hold details for a unified input event.
struct InputEvent
{
    InputType type = InputType::None;
    // For mouse events
    MouseEventState mouseState = MouseEventState::None;
    MousePosition pos = {0, 0};
    // For keyboard events
    KeyboardEvent keyState = KeyboardEvent::None;
    int keyCode = 0;
};

// Unified input handler interface.
class IInputHandler
{
  public:
    virtual ~IInputHandler() = default;

    // Handles any input event, whether mouse or keyboard.
    virtual void OnInputEvent(const InputEvent& event) = 0;
};

class InputResolver
{
  public:
    // Add a new event to the queue.
    static void PushEvent(const InputEvent& event);

    // Register an input handler.
    static void RegisterHandler(IInputHandler* handler);

    // Unregister an input handler (optional but useful).
    static void UnregisterHandler(IInputHandler* handler);

    // Process all queued events.
    static void resolve();

    static IInputHandler* getSelectedHandler()
    {
        return selectedHandler;
    }
    static void setSelectedHandler(IInputHandler* handler)
    {
        selectedHandler = handler;
    }

    static std::list<IInputHandler*> handlers;  // Collection of input handlers.
  private:
    static std::queue<InputEvent> queue;
    static IInputHandler* selectedHandler;
    // You can keep additional helper functions if needed.
};
struct Signal
{
    std::string name;  // Optional: if you want to name each signal
    bool val;          // The state of the signal
    Vector2 pos;
    Signal(const std::string& n = "", bool l = false) : name(n), val(l) {}
    bool operator==(const Signal& other) const
    {
        return name == other.name && val == other.val;
    }
};

class Component;

namespace CircuitElements
{
    class Circuit;

    struct HoveringWire
    {
        bool is_hovering;
        Vector2 pos;
    };
    struct PhysicalConnection
    {
        std::vector<Vector2> wires;
    };
    class Connection : public IInputHandler
    {
      public:
        std::shared_ptr<Component> sourceGate;
        std::string sourceLogic;
        std::shared_ptr<Component> targetGate;
        std::string targetLogic;
        PhysicalConnection physCon;
        HoveringWire hovering{false, {0.0f, 0.0f}};  // when this variable is uninitialized, it
        // causes a crash when rendering the is_hovering wires in the circuit
        CircuitElements::Circuit* circuit;  // = nullptr;
        bool is_connected = false;
        void OnInputEvent(const InputEvent& event) override;
        void OnLeftClick(const InputEvent& event);
        void OnMove(const InputEvent& event);
    };
}  // namespace CircuitElements
class Component : public IInputHandler
{
  public:
    Component() {};
    Component(std::string& fileName) {};
    void allocateConnection();
    void setEvaluationFunction(std::function<void(Component&)> evalFunc);
    void OnInputEvent(const InputEvent& event) override;
    void addComponent(const std::shared_ptr<Component>& comp);
    void addConnection(const CircuitElements::Connection& comp);
    virtual void Draw();
    void evaluate();
    const std::vector<Signal>& getInputs() const;
    const std::vector<Signal>& getOutputs() const;
    int getID() const;
    void setInput(const std::string& name, bool value);
    bool getOutput(const std::string& name) const;

    void setPosition(float x, float y)
    {
        bd.x = x;
        bd.y = y;
    };  // TODO: Implement this
    Rectangle bd;
    int id;
    std::vector<Signal> inputs;
    std::vector<Signal> outputs;
    std::vector<CircuitElements::Connection> connections;
    std::vector<std::shared_ptr<Component>> components;
    std::shared_ptr<CircuitElements::Circuit> circuit;

    bool is_hovered = false;
};
#endif