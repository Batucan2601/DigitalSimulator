#include "LogicElements.h"

#include "Controls.h"
#include <Util/Utils.h>
#include <raylibHelper.h>
#include "Clock.h"

namespace CircuitElements
{
    void Circuit::addGate(std::shared_ptr<Component> gate)
    {
        this->m_logger.info("Gate added to the circuit.");
        gate->circuit = this;
        gate->id = this->giveNewId();  // Assign a unique ID
        gates.push_back(gate);
    }

    void Circuit::addConnection(std::shared_ptr<Component> sourceGate,
                                const std::string& sourceOutput,
                                std::shared_ptr<Component> targetGate,
                                const std::string& targetInput)
    {
        this->m_logger.info("Connection added to the circuit.");
        Connection c;
        c.sourceGate = sourceGate;
        c.sourceLogic = sourceOutput;
        c.targetGate = targetGate;
        c.targetLogic = targetInput;
        c.circuit = this;
        this->connections.push_back(c);
    }

    void Circuit::removeComponent()
    {
        for (size_t i = 0; i < this->gates.size(); ++i)
        {
            if (this->gates[i]->m_mark_for_deletion)
            {
                // Remove associated connections
                for (size_t j = 0; j < this->connections.size(); ++j)
                {
                    if (this->connections[j].sourceGate == this->gates[i] ||
                        this->connections[j].targetGate == this->gates[i])
                    {
                        this->connections.erase(this->connections.begin() + j);
                        j--;
                    }
                }

                // Remove from gates
                InputResolver::UnregisterHandler(this->gates[i].get());
                this->gates.erase(this->gates.begin() + i);
                i--;
            }
        }
    }
    void Circuit::evaluate()
    {
        bool stabilized = false;
        int iterations = 0;
        const int maxIterations = 100;  // Prevent infinite loops
        
        
        for (auto& component : gates)
        {
            if (auto clock = std::dynamic_pointer_cast<Clock>(component))
            {
                clock->evaluate(); // Simulate interrupt or hardware clock behavior
            }
        }

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
                std::vector<SignalVal> sourceValue = conn.sourceGate->getOutput(conn.sourceLogic);
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

        this->removeComponent();  // Clean up gates marked for deletion

    }
    int Circuit::giveNewId()
    {
        int ret_id = this->id; 
        this->id++;
        return ret_id;
    }
    void Connection::OnInputEvent(const InputEvent& event)
    {
        if (event.type == InputType::Mouse)
        {
            if (event.mouseState == MouseEventState::LeftClick)
            {
                OnLeftClick(event);
            }
            if (event.mouseState == MouseEventState::RightClick)
            {
                OnRightClick(event);
            }
            if (event.mouseState == MouseEventState::Move)
            {
                OnMove(event);
            }
        }
    }
    void Connection::OnLeftClick(const InputEvent& event)
    {
        (void)event;
        // if hovering, create a new wire
        if (hovering.is_hovering)
        {
            CircuitElements::Connection possibleConnection;
            possibleConnection.sourceGate = this->sourceGate;
            possibleConnection.sourceLogic = this->sourceLogic;
            circuit->addConnection(
                possibleConnection.sourceGate, possibleConnection.sourceLogic,
                possibleConnection.targetGate, possibleConnection.targetLogic);
            this->circuit->active_wire.is_visible = true;
            this->circuit->active_wire.start = hovering.pos;
            this->circuit->active_wire.end = hovering.pos; 
            InputResolver::RegisterHandler(
                static_cast<IInputHandler*>(&(circuit->active_wire)));
            InputResolver::setSelectedHandler(
                (IInputHandler*)&circuit->connections[circuit->connections.size() - 1]);
        }
    }
    void Connection::OnRightClick(const InputEvent& event)
    {
        // check bb
        Vector2 pos = {(float)event.pos.x, (float)event.pos.y};
        for (size_t i = 0; i < this->physCon.wires.size()-1; i++)
        {
            Vector2 start = this->physCon.wires[i];
            Vector2 end = this->physCon.wires[i+1];
            Rectangle bd = { std::min(start.x , end.x) , std::min(start.y , end.y) , 
            std::abs(start.x - end.x) + 5 , std::abs(start.y - end.y) + 5 };
            bool isCol = CheckCollisionPointRec(pos, bd);
            if (isCol)
            {
                 InputResolver::setSelectedHandler(this);
                 RaylibHelper::Show(4);
                 return;
            }
        }
        InputResolver::setSelectedHandler(nullptr);
    }
    void Connection::OnMove(const InputEvent& event)
    {
        // check collision with physcons
        size_t wireCount = this->physCon.wires.size();
        if (wireCount < 1) return;  // Nothing to loop over 
        hovering.is_hovering = false;
        for (size_t j = 0; j < this->physCon.wires.size() - 1; j++)
        {
            Vector2 start = this->physCon.wires[j];
            Vector2 end = this->physCon.wires[j + 1];
            Rectangle col = {0, 0, 0, 0};
            float minx = std::min(start.x, end.x);
            float maxx = std::max(start.x, end.x);
            float miny = std::min(start.y, end.y);
            float maxy = std::max(start.y, end.y);
            start = {minx, miny};
            end = {maxx, maxy};
            if (std::abs(end.x - start.x) < AppSettings::appSettings.SPACING_SIZE)
            {
                col = {start.x - AppSettings::appSettings.MOUSE_SELECTION_OFFSET, start.y,
                       (float)(AppSettings::appSettings.SPACING_SIZE + AppSettings::appSettings.MOUSE_SELECTION_OFFSET),
                       std::abs(end.y - start.y)};
            }
            else if (std::abs(end.y - start.y) < AppSettings::appSettings.SPACING_SIZE)
            {
                col = {start.x, start.y + -AppSettings::appSettings.MOUSE_SELECTION_OFFSET,
                       std::abs(end.x - start.x),
                       (float)(AppSettings::appSettings.SPACING_SIZE + AppSettings::appSettings.MOUSE_SELECTION_OFFSET)};
            }
            Vector2 pos = {(float)event.pos.x, (float)event.pos.y};
            if (CheckCollisionPointRec(pos, col))
            {
                hovering.is_hovering = true;
                Rectangle rec = {pos.x, pos.y, 0, 0};
                hovering.pos = Utils::SnapToNearestGrid(rec);
            }
        }
    }
    void ActiveWire::OnInputEvent(const InputEvent& event)
    {
        if (event.type == InputType::Mouse )
        {
            if (event.mouseState == MouseEventState::Move)
            {
                OnMove(event);
            }
            if (event.mouseState == MouseEventState::LeftClick)
            {
                OnLeftClick(event);
            }
            if (event.mouseState == MouseEventState::RightClick)
            {
                OnRightClick(event);
            }
        }
    }
    void ActiveWire::OnMove(const InputEvent& event)
    {
        Rectangle pos_rec = {(float)event.pos.x, (float)event.pos.y, 0, 0};
        this->end = Utils::SnapToNearestGrid(pos_rec);
    }

    void ActiveWire::OnLeftClick(const InputEvent& event)
    {
        (void)event;
        if (Connection* d1 = dynamic_cast<Connection*>(InputResolver::getSelectedHandler()))
        {
            if (this->start.x == this->end.x && this->start.y == this->end.y)
            {
                return;
            }
            if (d1->physCon.wires.size() == 0)
            {
                d1->physCon.wires.push_back({this->start.x, this->start.y});
            }
            Vector2 straight_line = Controls::Generate_straight_lines(this->start, this->end);
            if (!(this->start.x == straight_line.x && this->start.y == straight_line.y))
            {
                d1->physCon.wires.push_back(straight_line);
            }
            if (straight_line.x == this->end.x && straight_line.y == this->end.y)
            {
                return;
            }
            d1->physCon.wires.push_back({this->end.x, this->end.y});
            Rectangle pos_rec = {this->end.x, this->end.y, 0, 0};
            this->start = Utils::SnapToNearestGrid(pos_rec);

            if (d1->is_connected)
            {
                this->is_visible = false;
                InputResolver::setSelectedHandler(nullptr);
            }
        }
    }
    void ActiveWire::OnRightClick(const InputEvent& event)
    {
        (void)event;
        if (this == (InputResolver::getSelectedHandler()))
        {
            InputResolver::UnregisterHandler(this);
        }
    }
}  // namespace CircuitElements
