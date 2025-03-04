#include "LogicElementBase.h"

#include "Component.h"

#ifndef PROJECT_ROOT_DIR
#define PROJECT_ROOT_DIR "/path/to/project/root"  // Replace with the actual project root directory
#endif
#include "appSettings.h"

#include <Controls.h>

extern AppSettings::Settings appSettings;

namespace LogicElements
{
    std::map<GateType, Texture> logicElementTextures;
    std::shared_ptr<std::vector<GateInfo>> gateInfoList;

    void init_logicTextures()
    {
        init_OutlinedLogicTextures();
        init_FilledLogicTextures();

        gateInfoList = std::make_shared<std::vector<GateInfo>>();
        gateInfoList->push_back(GateInfo("AND Gate", GateType::AND,
                                         &logicElementTextures[GateType::AND],
                                         &logicElementTextures[GateType::AND_FILLED]));
        gateInfoList->push_back(GateInfo("OR Gate", GateType::OR,
                                         &logicElementTextures[GateType::OR],
                                         &logicElementTextures[GateType::OR_FILLED]));
        gateInfoList->push_back(GateInfo("NOT Gate", GateType::NOT,
                                         &logicElementTextures[GateType::NOT],
                                         &logicElementTextures[GateType::NOT_FILLED]));
        gateInfoList->push_back(GateInfo("XOR Gate", GateType::XOR,
                                         &logicElementTextures[GateType::XOR],
                                         &logicElementTextures[GateType::XOR_FILLED]));
        gateInfoList->push_back(GateInfo("XAND Gate", GateType::XAND,
                                         &logicElementTextures[GateType::XAND],
                                         &logicElementTextures[GateType::XAND_FILLED]));
        gateInfoList->push_back(GateInfo("INPUT Gate", GateType::INPUT,
                                         &logicElementTextures[GateType::INPUT],
                                         &logicElementTextures[GateType::INPUT_FILLED]));
    }

    void init_OutlinedLogicTextures()
    {
        std::string folder_path = "assets/gates/outlined_gates/";  // Use relative path
        std::string file_path;

        file_path = folder_path + "and.png";  // Use relative path
        std::string full_path = (std::filesystem::path(PROJECT_ROOT_DIR) / file_path).string();
        logicElementTextures[GateType::AND] = LoadTexture(full_path.c_str());

        file_path = folder_path + "or.png";  // Use relative path
        full_path = (std::filesystem::path(PROJECT_ROOT_DIR) / file_path).string();
        logicElementTextures[GateType::OR] = LoadTexture(full_path.c_str());

        file_path = folder_path + "not.png";  // Use relative path
        full_path = (std::filesystem::path(PROJECT_ROOT_DIR) / file_path).string();
        logicElementTextures[GateType::NOT] = LoadTexture(full_path.c_str());

        file_path = folder_path + "xand.png";  // Use relative path
        full_path = (std::filesystem::path(PROJECT_ROOT_DIR) / file_path).string();
        logicElementTextures[GateType::XOR] = LoadTexture(full_path.c_str());

        file_path = folder_path + "xor.png";  // Use relative path
        full_path = (std::filesystem::path(PROJECT_ROOT_DIR) / file_path).string();
        logicElementTextures[GateType::XAND] = LoadTexture(full_path.c_str());

        file_path = folder_path + "not.png";  // Use relative path
        full_path = (std::filesystem::path(PROJECT_ROOT_DIR) / file_path).string();
        logicElementTextures[GateType::INPUT] = LoadTexture(full_path.c_str());
    }
    void init_FilledLogicTextures()
    {
        std::string folder_path = "assets/gates/filled_gates/";  // Use relative path
        std::string file_path;
        std::string full_path = (std::filesystem::path(PROJECT_ROOT_DIR) / file_path).string();

        file_path = folder_path + "and.png";  // Use relative path
        full_path = (std::filesystem::path(PROJECT_ROOT_DIR) / file_path).string();
        logicElementTextures[GateType::AND_FILLED] = LoadTexture(full_path.c_str());

        file_path = folder_path + "or.png";  // Use relative path
        full_path = (std::filesystem::path(PROJECT_ROOT_DIR) / file_path).string();
        logicElementTextures[GateType::OR_FILLED] = LoadTexture(full_path.c_str());

        file_path = folder_path + "not.png";  // Use relative path
        full_path = (std::filesystem::path(PROJECT_ROOT_DIR) / file_path).string();
        logicElementTextures[GateType::NOT_FILLED] = LoadTexture(full_path.c_str());

        file_path = folder_path + "xand.png";  // Use relative path
        full_path = (std::filesystem::path(PROJECT_ROOT_DIR) / file_path).string();
        logicElementTextures[GateType::XOR_FILLED] = LoadTexture(full_path.c_str());

        file_path = folder_path + "xor.png";  // Use relative path
        full_path = (std::filesystem::path(PROJECT_ROOT_DIR) / file_path).string();
        logicElementTextures[GateType::XAND_FILLED] = LoadTexture(full_path.c_str());
    }

    LogicGate::LogicGate(GateType gateType, std::string& logger_name)
        : m_type(gateType), m_logger(logger_name)
    {
        static int nextId = 0;
        id = nextId++;  // Assign a unique ID
        Component();
        // type = gateType;
        m_texture = logicElementTextures[gateType];
        m_logger.info("LogicGate created as type: " + std::to_string(static_cast<int>(m_type)));
        InputResolver::RegisterHandler(this);
    }

    LogicGate::~LogicGate()
    {
        m_logger.info("LogicGate destroyed.");
        // UnloadTexture(m_texture);
    }

    void LogicGate::setInOutPositions()
    {
        // output
        int no_of_grid_points = this->bd.width / appSettings.GRID_POINT_SIZE + 1;

        if (this->outputs.size() == 1)
        {
            this->outputs[0].pos = {this->bd.x + this->bd.width, this->bd.y + this->bd.height / 2};
        }
        else if (this->outputs.size() > 1)
        {
            this->outputs[0].pos = {this->bd.x + this->bd.width,
                                    this->bd.y + appSettings.SPACING_SIZE};
            this->outputs[1].pos = {this->bd.x + this->bd.width,
                                    this->bd.y + appSettings.SPACING_SIZE * 3};
        }
        if (this->outputs.size() > 2)
        {
            this->outputs[2].pos = {this->bd.x + this->bd.width,
                                    this->bd.y + appSettings.SPACING_SIZE * 2};
        }
        if (this->outputs.size() > 3)
        {
            this->outputs[3].pos = {this->bd.x + this->bd.width,
                                    this->bd.y + appSettings.SPACING_SIZE * 4};
        }
        if (this->outputs.size() > 4)
        {
            this->outputs[4].pos = {this->bd.x + this->bd.width, this->bd.y};
        }
        if (this->inputs.size() == 1)
        {
            this->inputs[0].pos = {this->bd.x, this->bd.y + this->bd.height / 2};
        }
        else if (this->inputs.size() > 1)
        {
            this->inputs[0].pos = {this->bd.x, this->bd.y + appSettings.SPACING_SIZE};
            this->inputs[1].pos = {this->bd.x, this->bd.y + appSettings.SPACING_SIZE * 3};
        }
        if (this->inputs.size() > 2)
        {
            this->inputs[2].pos = {this->bd.x, this->bd.y + appSettings.SPACING_SIZE * 2};
        }
        if (this->inputs.size() > 3)
        {
            this->inputs[3].pos = {this->bd.x, this->bd.y + appSettings.SPACING_SIZE * 4};
        }
        if (this->inputs.size() > 4)
        {
            this->inputs[4].pos = {this->bd.x, this->bd.y};
        }
    }
    void LogicGate::setPosition(float x, float y)
    {
        bd.x = x;
        bd.y = y;
        this->setInOutPositions();
    }

    Vector2 LogicGate::getPosition() const
    {
        return {bd.x, bd.y};
    }

    int LogicGate::getID() const
    {
        return id;
    }

    const std::vector<Signal>& LogicGate::getInputs() const
    {
        return inputs;
    }

    const std::vector<Signal>& LogicGate::getOutputs() const
    {
        return outputs;
    }

    void LogicGate::setInput(const std::string& name, bool value)
    {
        for (auto& I : this->inputs)
        {
            if (I.name == name)
            {
                I.val = value;
                notifyObservers();
            }
        }
    }

    bool LogicGate::getOutput(const std::string& name) const
    {
        for (auto& it : this->outputs)
        {
            if (it.name == name)
            {
                return true;
            }
        }
        return false;
    }

    void LogicGate::setEvaluationFunction(std::function<void(LogicGate&)> evalFunc)
    {
        evaluateFunction = evalFunc;
    }

    void LogicGate::evaluate()
    {
        if (evaluateFunction)
        {
            evaluateFunction(*this);
        }
    }

    GateType LogicGate::getType() const
    {
        return m_type;
    }

    const Texture2D& LogicGate::getTexture() const
    {
        return m_texture;
    }

    // GatePosition &LogicGate::getPositionManager()
    // {
    //     return m_position;
    // }

    void LogicGate::addObserver(GateObserver* observer)
    {
        observers.insert(observer);
    }

    void LogicGate::removeObserver(GateObserver* observer)
    {
        observers.erase(observer);
    }

    void LogicGate::notifyObservers()
    {
        for (auto observer : observers)
        {
            observer->onInputChanged();
        }
    }

    void LogicGate::onInputChanged()
    {
        evaluate();  // Automatically reevaluate when input changes
    }

    void LogicGate::OnInputEvent(const InputEvent& event)
    {
        if (event.type == InputType::Mouse)
        {
            if (event.mouseState == MouseEventState::LeftClick)
            {
                OnLeftClick(event);
            }
            if (event.mouseState == MouseEventState::Release)
            {
                OnRelease(event);
            }
            if (event.mouseState == MouseEventState::RightClick)
            {
                OnRightClick(event);
            }
            if (event.mouseState == MouseEventState::Down)
            {
                OnDown(event);
            }
            if (event.mouseState == MouseEventState::Move)
            {
                OnMove(event);
            }
            if (event.mouseState == MouseEventState::Enter)
            {
                OnEnter(event);
            }
            if (event.mouseState == MouseEventState::Leave)
            {
                OnExit(event);
            }
        }

        if (event.type == InputType::Keyboard)
        {
            std::cout << "Keyboard event" << std::endl;
            if (event.keyState == KeyboardEvent::KeyPress)
            {
                OnKeyPress(event);
            }
            if (event.keyState == KeyboardEvent::KeyRelease)
            {
                // OnKeyRelease(event);
            }
            if (event.keyState == KeyboardEvent::KeyRepeat)
            {
                // OnKeyRepeat(event);
            }
        }
    }

    bool LogicGate::is_connection_clicked(const Vector2& mousePos,
                                          CircuitElements::Connection& possibleConnection)
    {
        if (this->CheckMouseOnInOut(mousePos, possibleConnection))
        {
            return true;
        }
        return false;
    }
    void LogicGate::OnLeftClick(const InputEvent& event)
    {
        // check bb
        Vector2 pos = {(float)event.pos.x, (float)event.pos.y};
        bool isCol = CheckCollisionPointRec(pos, this->bd);
        if (!isCol)
        {
            return;
        }
        // ok first look at the selected handler, check if it is a logic gate
        CircuitElements::Connection possibleConnection;
        if (!circuit->active_wire.is_visible)  // we are not building a connection
        {
            // it cannot be a connection end
            // it can be a connection start, or gate select
            if (this->is_connection_clicked(pos, possibleConnection))
            {
                // if hits select it
                // possibleConnection.circuit = this->circuit;
                circuit->addConnection(
                    possibleConnection.sourceGate, possibleConnection.sourceLogic,
                    possibleConnection.targetGate, possibleConnection.targetLogic);
                circuit->active_wire.is_visible = true;
                circuit->active_wire.start = pos;
                circuit->active_wire.end = pos;
                InputResolver::RegisterHandler(
                    static_cast<IInputHandler*>(&(circuit->active_wire)));
                InputResolver::setSelectedHandler(
                    (IInputHandler*)&circuit->connections[circuit->connections.size() - 1]);
            }
            else  // select the gate
            {
                InputResolver::setSelectedHandler((IInputHandler*)this);
            }
            return;
        }
        // check if a connection already selected.
        if (auto handler =
                dynamic_cast<CircuitElements::Connection*>(InputResolver::getSelectedHandler()))
        {
            if (this->is_connection_clicked(pos, possibleConnection))
            {

                // the source should be output
                // the target should be an input
                bool is_output = false;
                bool is_input = false;
                for (size_t i = 0; i < handler->sourceGate->outputs.size(); i++)
                {
                    if (handler->sourceGate->outputs[i].name == handler->sourceLogic)
                    {
                        is_output = true;
                        break;
                    }
                }
                for (size_t i = 0; i < possibleConnection.sourceGate->inputs.size(); i++)
                {
                    if (possibleConnection.sourceGate->inputs[i].name ==
                        possibleConnection.sourceLogic)
                    {
                        is_input = true;
                        break;
                    }
                }
                if (is_output != is_input)  // if one is true one is false
                {
                    return;
                }
                handler->targetGate = possibleConnection.sourceGate;
                handler->targetLogic = possibleConnection.sourceLogic;
                handler->is_connected = true;
                if (!is_output && !is_input)
                {
                    std::shared_ptr<LogicGate> temp_ptr = handler->sourceGate;
                    handler->sourceGate = handler->targetGate;
                    handler->targetGate = temp_ptr;

                    std::string temp_str = handler->sourceLogic;
                    handler->sourceLogic = handler->targetLogic;
                    handler->targetLogic = temp_str;
                }

                InputResolver::RegisterHandler(static_cast<IInputHandler*>(
                    &circuit->connections[circuit->connections.size() - 1]));
            }
        }
        // connection logic

        // select the handler.
        // InputResolver::setSelectedHandler((IInputHandler*)(&circuit->connections[circuit->connections.size()
        // - 1]));
    }
    void LogicGate::OnRightClick(const InputEvent& event)
    {
        InputResolver::setSelectedHandler(nullptr);
    }
    static Vector2 posBeforeDrag;
    static bool isFirst = true;
    static bool isDragging = false;
    Vector2 dif;

    void UpdateConnection(LogicGate* gate)
    {
        for (size_t i = 0; i < gate->circuit->connections.size(); i++)
        {
            CircuitElements::Connection* c = &gate->circuit->connections[i];
            if (c->sourceGate.get() == gate)
            {
                std::string name = c->sourceLogic;
                for (size_t j = 0; j < gate->outputs.size(); j++)
                {
                    if (name == gate->outputs[j].name)
                    {
                        Rectangle rec = {gate->outputs[j].pos.x, gate->outputs[j].pos.y, 0, 0};
                        Vector2 newPos = Controls::SnapToNearestGrid(rec);
                        Vector2 newLine =
                            Controls::Generate_straight_lines(newPos, c->physCon.wires[0]);
                        c->physCon.wires.insert(c->physCon.wires.begin(), newPos);
                        if (!(newLine.x == c->physCon.wires[0].x &&
                              newLine.y == c->physCon.wires[0].y))
                        {
                            c->physCon.wires.insert(c->physCon.wires.begin() + 1, newLine);
                        }
                    }
                }
            }
            if (c->targetGate.get() == gate)
            {
                std::string name = c->targetLogic;
                for (size_t j = 0; j < gate->inputs.size(); j++)
                {
                    if (name == gate->inputs[j].name)
                    {
                        Rectangle rec = {gate->inputs[j].pos.x, gate->inputs[j].pos.y, 0, 0};
                        Vector2 newPos = Controls::SnapToNearestGrid(rec);
                        int last_index = c->physCon.wires.size() - 1;
                        Vector2 newLine =
                            Controls::Generate_straight_lines(newPos, c->physCon.wires[last_index]);
                        c->physCon.wires.push_back(newLine);
                        if (!(newLine.x == c->physCon.wires[last_index].x &&
                              newLine.y == c->physCon.wires[last_index].y))
                        {
                            c->physCon.wires.push_back(newPos);
                        }
                    }
                }
            }
        }
    }
    void ReducePhysicalWires(LogicGate* gate)
    {
        for (size_t i = 0; i < gate->circuit->connections.size(); i++)
        {
            CircuitElements::Connection* c = &gate->circuit->connections[i];
            if (c->sourceGate.get() == gate || c->targetGate.get() == gate)
            {
                std::vector<unsigned int> indices_destroyed;
                for (int j = c->physCon.wires.size() - 1; j > 1; j--)
                {
                    Vector2 end = c->physCon.wires[j];
                    Vector2 mid = c->physCon.wires[j - 1];
                    Vector2 start = c->physCon.wires[j - 2];

                    if (mid.x == start.x && mid.y == start.y)
                    {
                        indices_destroyed.push_back(j - 1);
                    }
                }
                for (size_t j = 0; j < indices_destroyed.size(); j++)
                {
                    c->physCon.wires.erase(c->physCon.wires.begin() + indices_destroyed[j]);
                }
                indices_destroyed.clear();
                for (int j = c->physCon.wires.size() - 1; j > 1; j--)
                {
                    Vector2 end = c->physCon.wires[j];
                    Vector2 mid = c->physCon.wires[j - 1];
                    Vector2 start = c->physCon.wires[j - 2];
                    if ((mid.y == start.y && mid.y == end.y) ||
                        (mid.x == start.x && mid.x == end.x))
                    {
                        indices_destroyed.push_back(j - 1);
                    }
                }
                for (size_t j = 0; j < indices_destroyed.size(); j++)
                {
                    c->physCon.wires.erase(c->physCon.wires.begin() + indices_destroyed[j]);
                }
            }
        }
    }
    void LogicGate::OnDown(const InputEvent& event)
    {
        if (this == InputResolver::getSelectedHandler())
        {
            Vector2 mousePos = {(float)event.pos.x, (float)event.pos.y};

            if (!isDragging)
            {
                if (CheckCollisionPointRec(mousePos, this->bd))
                {
                    isDragging = true;
                    dif = {this->bd.x - event.pos.x, this->bd.y - event.pos.y};
                }
                else
                {
                    return;
                }
            }
            Rectangle rec = {event.pos.x + dif.x, event.pos.y + dif.y, 0, 0};
            this->setPosition(rec.x, rec.y);
            if (isFirst)
            {
                posBeforeDrag = {rec.x, rec.y};
                isFirst = false;
            }
            // check the connections and their endpoints
            UpdateConnection(this);
            ReducePhysicalWires(this);
        }
    }

    void LogicGate::OnRelease(const InputEvent& event)
    {

        if (this == InputResolver::getSelectedHandler())
        {
            if (!isDragging)
            {
                return;
            }
            Rectangle rec = {(float)event.pos.x, (float)event.pos.y, 0, 0};
            Vector2 v = Controls::SnapToNearestGrid(rec);
            bool is_other_gate_exist = false;
            for (auto val : InputResolver::handlers)
            {
                if (auto handler = dynamic_cast<LogicGate*>(val))
                {
                    if (handler == this)
                    {
                        continue;
                    }
                    // Check for overlap between the new gate's bounding box and the existing gate's
                    // bounding box
                    if (CheckCollisionRecs(this->bd, handler->bd))
                    {
                        is_other_gate_exist = true;  // Overlap detected, grid is occupied
                        break;
                    }
                }
            }
            if (is_other_gate_exist)
            {
                this->setPosition(posBeforeDrag.x, posBeforeDrag.y);
            }
            else
            {
                rec.x = v.x + dif.x;
                rec.y = v.y + dif.y;
                Vector2 v = Controls::SnapToNearestGrid(rec);
                this->setPosition(v.x, v.y);
            }
            isFirst = true;
            isDragging = false;
            ReducePhysicalWires(this);
        }
    }
    void LogicGate::OnMove(const InputEvent& event)
    {
        Vector2 mouse_pos = {(float)event.pos.x, (float)event.pos.y};
        CircuitElements::Connection temp;
        if (CheckMouseOnInOut(mouse_pos, temp))
        {
            // this should change the input color
        }
        bool currently_hovered = CheckCollisionPointRec(mouse_pos, this->bd);
        if (currently_hovered && !this->is_hovered)
        {
            this->is_hovered = true;
        }
        else if (!currently_hovered && this->is_hovered)
        {
            this->is_hovered = false;
        }
    }

    void LogicGate::OnEnter(const InputEvent& event)
    {
        // update the circuit->hoveredGate with this object
        (void)event;

        m_logger.info("Mouse entered the gate");
        if (this == InputResolver::getSelectedHandler())
        {
            circuit->hoveredGate = shared_from_this();
        }
    }
    void LogicGate::OnExit(const InputEvent& event)
    {
        (void)event;
        // update the circuit->hoveredGate with nullptr
    }

    void LogicGate::OnKeyPress(const InputEvent& event)
    {
        if (event.keyCode == KeyboardKey::KEY_DELETE)
        {
            if (this == InputResolver::getSelectedHandler())
            {
                // remove the gate
                for (size_t i = 0; i < circuit->connections.size(); i++)
                {
                    if (circuit->connections[i].sourceGate.get() == this ||
                        circuit->connections[i].targetGate.get() == this)
                    {
                        circuit->connections.erase(circuit->connections.begin() + i);
                        i--;
                    }
                }
                for (size_t i = 0; i < circuit->gates.size(); i++)
                {
                    if (circuit->gates[i].get() == this)
                    {
                        circuit->gates.erase(circuit->gates.begin() + i);
                        i--;
                    }
                }
            }
        }
    }

    bool LogicGate::CheckMouseOnInOut(const Vector2& mousePosition,
                                      CircuitElements::Connection& connection)
    {
        std::shared_ptr<LogicGate> itself = shared_from_this();
        Rectangle rec;
        for (size_t i = 0; i < inputs.size(); i++)
        {
            rec.x = inputs[i].pos.x - appSettings.IN_OUT_RECT_WIDTH;
            rec.y = inputs[i].pos.y - appSettings.IN_OUT_RECT_WIDTH;
            rec.width = appSettings.IN_OUT_INTERACTION;
            rec.height = appSettings.IN_OUT_INTERACTION;
            if (CheckCollisionPointRec(mousePosition, rec))
            {
                connection.sourceGate = itself;
                connection.sourceLogic = inputs[i].name;
                Vector2 pos = {rec.x, rec.y};
                connection.physCon.wires.push_back(pos);
                return true;
            }
        }
        for (size_t i = 0; i < outputs.size(); i++)
        {
            rec.x = outputs[i].pos.x - appSettings.IN_OUT_RECT_WIDTH;
            rec.y = outputs[i].pos.y - appSettings.IN_OUT_RECT_WIDTH;
            rec.width = appSettings.IN_OUT_INTERACTION;
            rec.height = appSettings.IN_OUT_INTERACTION;
            if (CheckCollisionPointRec(mousePosition, rec))
            {
                connection.sourceGate = itself;
                connection.sourceLogic = outputs[i].name;
                Vector2 pos = {rec.x, rec.y};
                connection.physCon.wires.push_back(pos);
                return true;
            }
        }
        return false;
    }

}  // namespace LogicElements