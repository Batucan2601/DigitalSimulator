#ifndef COMPONENT_H
#define COMPONENT_H
#include <queue>
#include <vector>
#include <list>
#include <algorithm>
#include <raylib.h>
#include <functional>
#include <string>
// Enum to identify the type of input event.
enum class InputType {
    None,
    Mouse,
    Keyboard
};

// Enums for mouse and keyboard event states.
enum class MouseEventState {
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

enum class KeyboardEvent {
    None,
    KeyPress,
    KeyRelease,
    KeyRepeat
};

// Structure representing a 2D coordinate.
struct MousePosition {
    int x;
    int y;
};

// Structure to hold details for a unified input event.
struct InputEvent {
    InputType type = InputType::None;
    // For mouse events
    MouseEventState mouseState = MouseEventState::None;
    MousePosition pos = { 0, 0 };
    // For keyboard events
    KeyboardEvent keyState = KeyboardEvent::None;
    int keyCode = 0;
};


// Unified input handler interface.
class IInputHandler {
public:
    virtual ~IInputHandler() = default;

    // Handles any input event, whether mouse or keyboard.
    virtual void OnInputEvent(const InputEvent& event) = 0;
   
};

class InputResolver {
public:
    // Add a new event to the queue.
    static void PushEvent(const InputEvent& event);

    // Register an input handler.
    static void RegisterHandler(IInputHandler* handler);

    // Unregister an input handler (optional but useful).
    static void UnregisterHandler(IInputHandler* handler);

    // Process all queued events.
    static void resolve();

    static IInputHandler* getSelectedHandler() { return selectedHandler; }
    static void setSelectedHandler(IInputHandler* handler) { selectedHandler = handler; }

    static std::list<IInputHandler*> handlers; // Collection of input handlers.
private:
    static std::queue<InputEvent> queue;
    static IInputHandler* selectedHandler;
    // You can keep additional helper functions if needed.
};
struct Signal {
    std::string name;    // Optional: if you want to name each signal
    bool val;    // The state of the signal
    Vector2 pos;
    Signal(const std::string& n = "", bool l = false)
        : name(n), val(l) {}
    bool operator==(const Signal& other) const {
        return name == other.name && val == other.val;
    }
};

class Component : public IInputHandler
{
public: 
    void setEvaluationFunction(std::function<void(Component&)> evalFunc);
    void OnInputEvent(const InputEvent& event) override;
    Rectangle bd;
    std::vector<Signal> inputs;
    std::vector<Signal> outputs;

};
#endif