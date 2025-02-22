#ifndef COMPONENT_H
#define COMPONENT_H
#include <queue>
#include <vector>

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
    Hover
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

class InputResolver
{
    static std::queue<InputEvent> queue;
    void resolve();
};
// Unified input handler interface.
class IInputHandler {
public:
    virtual ~IInputHandler() = default;

    // Handles any input event, whether mouse or keyboard.
    virtual void OnInputEvent(const InputEvent& event) = 0;
   
};
#endif