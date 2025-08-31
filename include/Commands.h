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
        std::vector<std::shared_ptr<CircuitElements::Connection>> connection;
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
    class RemoveConnectionCommand : public ICommand
    {
        public:
        RemoveConnectionCommand(SP_Circuit c,
        std::weak_ptr<CircuitElements::Connection> con )
        {
            this->con = *con.lock().get();
            this->conPtr = con.lock();
            this->c = c;
        }
         void redo() override 
        {
            InputResolver::UnregisterHandler(this->conPtr);
            c->removeConnection(this->conPtr.get());
        }

        void undo() override 
        {
            
            c->addConnection(con.sourceGate,con.sourceLogic ,
            con.targetGate , con.targetLogic);
            
            InputResolver::RegisterHandler(c->connections[c->connections.size()-1]);
            c->connections[c->connections.size()-1].get()->physCon = con.physCon;
            c->connections[c->connections.size()-1].get()->is_connected = true; 
        }
        private: 
        CircuitElements::Connection con;
        std::shared_ptr<CircuitElements::Connection> conPtr;
        SP_Circuit c; 
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
            std::shared_ptr<CircuitElements::Connection> con = 
            circuit->connections[conIndex];
            InputResolver::UnregisterHandler(con);
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
                    InputResolver::UnregisterHandler(circuit->gates[i]);
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
                if( c->connections[i].get()->sourceGate == g || c->connections[i].get()->targetGate == g )
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
            InputResolver::RegisterHandler(gate);

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
                if( circuit->connections[i].get()->sourceGate == this->gate || 
                circuit->connections[i].get()->targetGate == this->gate )
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

            InputResolver::UnregisterHandler(gate);
            
            std::vector<std::weak_ptr<IInputHandler>> selectedHandler = InputResolver::getSelectedHandler();
            
            for (size_t i = 0; i < selectedHandler.size(); i++)
            {
                if( selectedHandler[i].lock() == gate)
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
                if(this->circuit->connections[i].get()->sourceGate == gate ||
                   this->circuit->connections[i].get()->targetGate == gate)
                {
                    this->connectionsPtr.push_back(this->circuit->connections[i]);
                }
            }
        }

        void undo() override 
        {
            gate->setPosition(from.x, from.y);
            
            for (int i = 0; i < (int)this->connectionsPtr.size(); i++) 
            {
                CircuitElements::Connection* c = this->connectionsPtr[i].lock().get();
                
                Vector2 posStart = c->sourceGate->outputs[ c->sourceGate->getOutputByName(c->sourceLogic) ].pos;
                Vector2 posEnd = c->targetGate->inputs[ c->targetGate->getInputByName(c->targetLogic) ].pos;
                Vector2 pos  = Controls::Generate_straight_lines(posStart , posEnd);
                c->physCon.wires = std::vector<Vector2>{posStart , pos , posEnd};
            }
        }

        void redo() override 
        {
            gate->setPosition(to.x, to.y);
        }

    private:
        SP_Circuit circuit; 
        std::shared_ptr<Component> gate;
        std::vector<std::weak_ptr<CircuitElements::Connection>> connectionsPtr; // for connections
        Vector2 from;
        Vector2 to;
    };

}