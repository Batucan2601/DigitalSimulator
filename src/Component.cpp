#include "Component.h"
// Define static members.
std::queue<InputEvent> InputResolver::queue;
std::list<IInputHandler*> InputResolver::handlers; // I do not really know what thefuck that is about
IInputHandler* InputResolver::selectedHandler = nullptr;
void InputResolver::PushEvent(const InputEvent& event) {
    queue.push(event);
}

void InputResolver::RegisterHandler(IInputHandler* handler) {
    // Optionally check if the handler is already registered.
    handlers.push_back(handler);
}

void InputResolver::UnregisterHandler(IInputHandler* handler) {
    // Remove handler from the vector.
    handlers.erase(std::remove(handlers.begin(), handlers.end(), handler), handlers.end());
}

void InputResolver::resolve() {
    while (!queue.empty()) {
        InputEvent event = queue.front();
        queue.pop();
        // Dispatch the event to all registered handlers.
        int i = 0;
        for (auto handler : handlers) {
            if (handler) {
                handler->OnInputEvent(event);
            }
        }
    }
}


void Component::OnInputEvent(const InputEvent& event)
{

}