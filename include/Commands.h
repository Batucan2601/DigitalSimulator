#pragma once
#include <stack>
#include <memory>
#include "Component.h"
#include "Controls.h"
#include "LogicElements/LogicElements.h"
#include "common_types.h"

namespace Command
{ 
    struct ICommand {
        virtual void undo() = 0;
        virtual void redo() = 0;
        virtual ~ICommand() {}
        std::vector<CircuitElements::Connection> connection;
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


    class AddConnectionCommand : public ICommand
    {
        public:
        AddConnectionCommand(SP_Circuit c, std::shared_ptr<Component> srcComp,
        std::shared_ptr<Component> targetComp, std::string sourceString , std::string targetString)
            : circuit(c), srcComp(srcComp), targetComp(targetComp), sourceString(sourceString),
            targetString(targetString) {
                conIndex = -1;
            }

        void undo() override 
        {
            InputResolver::UnregisterHandler((IInputHandler*)&circuit->connections[conIndex]);
            circuit->connections.erase(circuit->connections.begin() + conIndex);
        }

        void redo() override {
            circuit->addConnection(srcComp ,sourceString, targetComp , targetString);
            conIndex = circuit->connections.size()-1;
        }

    private:
        SP_Circuit circuit;
        std::shared_ptr<Component> srcComp;
        std::shared_ptr<Component> targetComp;
        std::string sourceString;
        std::string targetString;
        int conIndex; 
    };

    class AddComponentCommand : public ICommand {
    public:
        AddComponentCommand(SP_Circuit c, std::shared_ptr<Component> g)
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
            circuit->addGate(gate);
        }

    private:
        SP_Circuit circuit;
        std::shared_ptr<Component> gate;
    };

    class RemoveComponentCommand : public ICommand {
    public:
        RemoveComponentCommand(SP_Circuit c, std::shared_ptr<Component> g)
            : circuit(c), gate(g)
        {
            // get the connections
            for(size_t i = 0; i < c->connections.size() ; i++ )
            {
                if( c->connections[i].sourceGate == g || c->connections[i].targetGate == g )
                {
                    this->connection.push_back(c->connections[i]);
                }
            }
        }

        void undo() override 
        {
            circuit->addGate(gate);
            for (size_t i =0; i < this->connection.size(); i++ ) 
            {
                this->circuit->connections.push_back(this->connection[i]);
            }
            InputResolver::RegisterHandler(gate.get());

        }

        void redo() override {
            for (size_t i = 0; i <circuit->gates.size(); i++)
            {
                /* code */
                if (circuit->gates[i]->getID() == gate->getID())
                {
                    circuit->gates.erase(circuit->gates.begin() + i);
                    break;
                }
            }
            std::vector<int> indices;
            for(size_t i = 0; i < circuit->connections.size() ; i++ )
            {
                if( circuit->connections[i].sourceGate == this->gate || circuit->connections[i].targetGate == this->gate )
                {
                    indices.push_back(i);
                }
            }
            //erase
            if( indices.size() != 0)
            {
                for(int i =indices.size()-1; i >= 0 ; i-- ) 
                {
                    circuit->removeConnection(indices[i]);
                }
            }

            InputResolver::UnregisterHandler(gate.get());
            
            std::vector<IInputHandler*> selectedHandler = InputResolver::getSelectedHandler();
            
            for (size_t i = 0; i < selectedHandler.size(); i++)
            {
                if( selectedHandler[i] == gate.get())
                {
                    selectedHandler.erase(selectedHandler.begin() + i );          
                    break; 
                }
            }
            InputResolver::setSelectedHandler(selectedHandler);
        }

    private:
        SP_Circuit circuit;
        std::shared_ptr<Component> gate;
    };

    class MoveComponentCommand : public ICommand {
    public:
        MoveComponentCommand(SP_Circuit circuit ,std::shared_ptr<Component> g, Vector2 oldPos, Vector2 newPos)
            :circuit(circuit), gate(g), from(oldPos), to(newPos) 
        {
            for (size_t i = 0; i < this->circuit->connections.size() ; i++) 
            {
                if(this->circuit->connections[i].sourceGate == gate ||
                   this->circuit->connections[i].targetGate == gate)
                {
                    this->indices.push_back(i);
                }
            }
        }

        void undo() override 
        {
            gate->setPosition(from.x, from.y);
            
            for (int i = 0; i < (int)this->indices.size(); i++) 
            {
                CircuitElements::Connection* c = &this->circuit->connections[this->indices[i]];
                Vector2 newWirePos; 
                if( c->sourceGate == gate)
                {
                    for (size_t j = 0; j < c->sourceGate->outputs.size(); j++)
                    {
                        if( c->sourceGate->outputs[j] == c->sourceLogic)
                        {
                            newWirePos = c->sourceGate->outputs[j].pos;
                            break; 
                        }
                    }
                }
                else //(c->targetGate == gate)
                {
                    for (size_t j = 0; j < c->targetGate->inputs.size(); j++)
                    {
                        if( c->targetGate->inputs[j] == c->targetLogic)
                        {
                            newWirePos = c->targetGate->inputs[j].pos;
                            break; 
                        }
                    }
                }
                Vector2 posDif = {this->to.x - this->from.x ,this->to.y - this->from.y };
                Vector2 oldWirePos = {newWirePos.x - posDif.x ,newWirePos.y - posDif.y};
                for (size_t j = 0; j < c->physCon.wires.size(); j++)
                {
                    if( std::abs(c->physCon.wires[j].x -oldWirePos.x) <= AppSettings::appSettings.SPACING_SIZE 
                        || std::abs(c->physCon.wires[j].y -oldWirePos.y) <= AppSettings::appSettings.SPACING_SIZE)
                    {
                        c->physCon.wires.erase(c->physCon.wires.begin() + j  , c->physCon.wires.end() );
                        //isErased = true;
                        return; 
                    }
                }
            }
        }

        void redo() override 
        {
            gate->setPosition(to.x, to.y);
        }

    private:
        SP_Circuit circuit; 
        std::shared_ptr<Component> gate;
        std::vector<size_t> indices; // for connections
        Vector2 from;
        Vector2 to;
    };

}