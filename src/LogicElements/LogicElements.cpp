#include "LogicElements.h"
#include "Controls.h"

namespace CircuitElements 
{
    void Circuit::addGate(std::shared_ptr<LogicElements::LogicGate> gate)
    {
        this->m_logger.info("Gate added to the circuit.");
        gate->circuit = this;
        gates.push_back(gate);
    }

    void Circuit::addConnection(std::shared_ptr<LogicElements::LogicGate> sourceGate,
                                const std::string& sourceOutput,
                                std::shared_ptr<LogicElements::LogicGate> targetGate,
                                const std::string& targetInput)
    {
        this->m_logger.info("Connection added to the circuit.");
        Connection c;
        c.sourceGate = sourceGate;
        c.sourceLogic = sourceOutput;
        c.targetGate = targetGate;
        c.targetLogic = targetInput;

        this->connections.push_back(c);
    }

    void Circuit::evaluate()
    {
        bool stabilized = false;
        int iterations = 0;
        const int maxIterations = 100;  // Prevent infinite loops

        while (!stabilized && iterations < maxIterations)
        {
            stabilized = true;
            for (auto& gate : gates)
            {
                gate->evaluate();
                auto previousOutputs = gate->getOutputs();
                gate->evaluate();
                if (gate->getOutputs() != previousOutputs)
                {
                    stabilized = false;
                }
            }
            // Then, update the inputs based on the connections.
            for (auto& conn : connections)
            {
                bool sourceValue = conn.sourceGate->getOutput(conn.sourceLogic);
                if (conn.targetLogic != "")
                {
                    conn.targetGate->setInput(conn.targetLogic, sourceValue);
                }
            }
            iterations++;
        }
        if (iterations == maxIterations)
        {
            // Handle infinite loop case
            throw std::runtime_error("Circuit evaluation did not stabilize.");
        }
    }


    void Connection::OnInputEvent(const InputEvent& event)
    {
        if (event.type == InputType::Mouse) {
            if (event.mouseState == MouseEventState::LeftClick)
            {
                OnLeftClick(event);
            }
        }
    }
    void Connection::OnLeftClick(const InputEvent& event)
    {
        
    }


    void ActiveWire::OnInputEvent(const InputEvent& event)
    {
        if (event.type == InputType::Mouse) {
            if (event.mouseState == MouseEventState::Move)
            {
                OnMove(event);
            }
            if (event.mouseState == MouseEventState::LeftClick)
            {
                OnLeftClick(event);
            }
        }
    }
    void ActiveWire::OnMove(const InputEvent& event)
    {
        Rectangle pos_rec = { event.pos.x , event.pos.y , 0, 0 };
        this->end  = Controls::SnapToNearestGrid(pos_rec);
        
    }

    void ActiveWire::OnLeftClick(const InputEvent& event)
    {
        Vector2 pos = { event.pos.x , event.pos.y};
        Rectangle pos_rec = { event.pos.x , event.pos.y , 0, 0};
        pos = Controls::SnapToNearestGrid(pos_rec);
        if (Connection* d1 = dynamic_cast<Connection*>(InputResolver::getSelectedHandler())) {
            d1->physCon.wires.push_back({ this->start.x, this->start.y });
            Vector2 straight_line = Controls::Generate_straight_lines(this->start,
                this->end);
            d1->physCon.wires.push_back(straight_line);
            d1->physCon.wires.push_back({ this->end.x, this->end.y });
            Rectangle pos_rec = { this->end.x , this->end.y, 0, 0 };
            this->start = Controls::SnapToNearestGrid(pos_rec);
        }
    }
}  // namespace CircuitElements
