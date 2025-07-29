#pragma once
#include <stack>
#include <memory>
#include "LogicElements/LogicElements.h"
struct ICommand {
    virtual void undo() = 0;
    virtual void redo() = 0;
    virtual ~ICommand() {}
};

class UndoManager {
public:
    void execute(std::unique_ptr<ICommand> cmd) {
        cmd->redo();  // Do it
        undoStack.push(std::move(cmd));
        clearStack(redoStack);
    }

    void undo() {
        if (!undoStack.empty()) {
            auto cmd = std::move(undoStack.top());
            undoStack.pop();
            cmd->undo();
            redoStack.push(std::move(cmd));
        }
    }

    void redo() {
        if (!redoStack.empty()) {
            auto cmd = std::move(redoStack.top());
            redoStack.pop();
            cmd->redo();
            undoStack.push(std::move(cmd));
        }
    }

    void clear() {
        clearStack(undoStack);
        clearStack(redoStack);
    }

private:
    std::stack<std::unique_ptr<ICommand>> undoStack;
    std::stack<std::unique_ptr<ICommand>> redoStack;

    void clearStack(std::stack<std::unique_ptr<ICommand>>& stack) {
        while (!stack.empty()) stack.pop();
    }
};


class AddGateCommand : public ICommand {
public:
    AddGateCommand(SP_Circuit c, std::shared_ptr<Component> g)
        : circuit(c), gate(g) {}

    void undo() override 
    {
        for (size_t i = 0; i <circuit->gates.size(); i++)
        {
            /* code */
            if (circuit->gates[i]->getID() == gate->getID())
            {
                circuit->gates.erase(circuit->gates.begin() + i);
                break;
            }
        }
        
    }

    void redo() override {
        circuit->gates.push_back(gate);
    }

private:
    SP_Circuit circuit;
    std::shared_ptr<Component> gate;
};



class MoveGateCommand : public ICommand {
public:
    MoveGateCommand(std::shared_ptr<Component> g, Vector2 oldPos, Vector2 newPos)
        : gate(g), from(oldPos), to(newPos) {}

    void undo() override {
        gate->setPosition(from.x, from.y);
    }

    void redo() override {
        gate->setPosition(to.x, to.y);
    }

private:
    std::shared_ptr<Component> gate;
    Vector2 from;
    Vector2 to;
};

