#include "LogicElements.h"

#include "Controls.h"

extern AppSettings::Settings settings;

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
        if (event.type == InputType::Mouse)
        {
            if (event.mouseState == MouseEventState::LeftClick)
            {
                OnLeftClick(event);
            }
            if (event.mouseState == MouseEventState::Move)
            {
                OnMove(event);
            }
        }
    }
    void Connection::OnLeftClick(const InputEvent& event)
    {
        // if hovering, create a new wire
        if (hovering.is_hovering)
        {
            /*CircuitElements::Connection possibleConnection;
            possibleConnection.sourceGate = this->sourceGate;
            possibleConnection.sourceLogic = this->sourceLogic;
            possibleConnection.circuit = this->circuit;
            // if hits select it
            circuit->addConnection(possibleConnection.sourceGate, possibleConnection.sourceLogic,
            possibleConnection.targetGate, possibleConnection.targetLogic);
            circuit->active_wire.is_visible = true;
            circuit->active_wire.start = hovering.pos;
            circuit->active_wire.end = hovering.pos; */
            // InputResolver::RegisterHandler(static_cast<IInputHandler*>(&(circuit->active_wire)));
            // InputResolver::setSelectedHandler((IInputHandler*)&circuit->connections[circuit->connections.size()
            // - 1]);
        }
    }
    void Connection::OnMove(const InputEvent& event)
    {
        // check collision with physcons
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
            if (std::abs(end.x - start.x) < settings.SPACING_SIZE)
            {
                col = {start.x - settings.MOUSE_SELECTION_OFFSET, start.y,
                       (float)(settings.SPACING_SIZE + settings.MOUSE_SELECTION_OFFSET),
                       std::abs(end.y - start.y)};
            }
            else if (std::abs(end.y - start.y) < settings.SPACING_SIZE)
            {
                col = {start.x, start.y + -settings.MOUSE_SELECTION_OFFSET,
                       std::abs(end.x - start.x),
                       (float)(settings.SPACING_SIZE + settings.MOUSE_SELECTION_OFFSET)};
            }
            Vector2 pos = {(float)event.pos.x, (float)event.pos.y};
            if (CheckCollisionPointRec(pos, col))
            {
                hovering.is_hovering = true;
                Rectangle rec = {pos.x, pos.y, 0, 0};
                hovering.pos = Controls::SnapToNearestGrid(rec);
            }
        }
    }
    void ActiveWire::OnInputEvent(const InputEvent& event)
    {
        if (event.type == InputType::Mouse)
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
        this->end = Controls::SnapToNearestGrid(pos_rec);
    }

    void ActiveWire::OnLeftClick(const InputEvent& event)
    {
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
            this->start = Controls::SnapToNearestGrid(pos_rec);

            if (d1->is_connected)
            {
                this->is_visible = false;
                InputResolver::setSelectedHandler(nullptr);
            }
        }
    }
    void ActiveWire::OnRightClick(const InputEvent& event)
    {
        if (this == (InputResolver::getSelectedHandler()))
        {
            InputResolver::UnregisterHandler(this);
        }
    }
}  // namespace CircuitElements
