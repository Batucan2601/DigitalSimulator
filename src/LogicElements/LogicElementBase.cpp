#include "LogicElementBase.h"
#include "Component.h"

#ifndef PROJECT_ROOT_DIR
#define PROJECT_ROOT_DIR "/path/to/project/root"  // Replace with the actual project root directory
#endif
#include <Controls.h>

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

    void LogicGate::setPosition(float x, float y)
    {
        bd.x = x;
        bd.y = y;
    }

    Vector2 LogicGate::getPosition() const
    {
        return {bd.x, bd.y};
    }

    const std::unordered_map<std::string, bool>& LogicGate::getInputs() const
    {
        return inputs;
    }

    const std::unordered_map<std::string, bool>& LogicGate::getOutputs() const
    {
        return outputs;
    }

    void LogicGate::setInput(const std::string& name, bool value)
    {
        if (inputs.find(name) != inputs.end())
        {
            inputs[name] = value;
            notifyObservers();
        }
    }

    bool LogicGate::getOutput(const std::string& name) const
    {
        auto it = outputs.find(name);
        return (it != outputs.end()) ? it->second : false;
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
        if (event.type == InputType::Mouse) {
            if (event.mouseState == MouseEventState::LeftClick)
            {
                OnLeftClick(event);
            }
            if (event.mouseState == MouseEventState::Down)
            {
                OnDown(event);
            }
            if (event.mouseState == MouseEventState::Release)
            {
                OnRelease(event);
            }
        }
    }

    bool LogicGate::is_connection_clicked(const Vector2& mousePos , CircuitElements::Connection& possibleConnection)
    {
        this->CheckGatePartClicked(mousePos, possibleConnection);
        if (possibleConnection.sourceLogic == "")  // not intitialized
        {
            return false;
        }
        return true; 

    }
    void LogicGate::OnLeftClick(const InputEvent& event)
    {
        //check bb
        Vector2 pos = { (float)event.pos.x , (float)event.pos.y };
        bool isCol = CheckCollisionPointRec(pos, this->bd);
        if (!isCol)
        {
            return;
        }
        //ok first look at the selected handler, check if it is a logic gate
        CircuitElements::Connection possibleConnection;
        if (InputResolver::getSelectedHandler() == nullptr)
        {
            // it cannot be a connection end
            // it can be a connection start, or gate select
            if (this->is_connection_clicked(pos, possibleConnection))
            {
                // if hits select it 
                //possibleConnection.circuit = this->circuit;
                circuit->addConnection(possibleConnection.sourceGate, possibleConnection.sourceLogic, possibleConnection.targetGate, possibleConnection.targetLogic);
                circuit->active_wire.is_visible = true; 
                circuit->active_wire.start = pos; 
                circuit->active_wire.end = pos; 
                InputResolver::RegisterHandler(static_cast<IInputHandler*>(&(circuit->active_wire)));
                InputResolver::setSelectedHandler((IInputHandler*)&circuit->connections[circuit->connections.size() - 1]);
            }
            else // select the gate 
            {
                InputResolver::setSelectedHandler((IInputHandler*)this);
            }
            return; 
        }
        // check if a connection already selected.
        if (auto handler = dynamic_cast<CircuitElements::Connection*>(InputResolver::getSelectedHandler()))
        {
            if (this->is_connection_clicked(pos, possibleConnection))
            {
                handler->targetGate = possibleConnection.sourceGate;
                handler->targetLogic = possibleConnection.sourceLogic;
                handler->is_connected = true; 
                InputResolver::RegisterHandler(static_cast<IInputHandler*>(&circuit->connections[circuit->connections.size() - 1]));
            }
        }
        // connection logic
        
        
        
        //select the handler.
        //InputResolver::setSelectedHandler((IInputHandler*)(&circuit->connections[circuit->connections.size() - 1]));
    }
    static Vector2 posBeforeDrag;
    static bool isFirst = true;
    void LogicGate::OnDown(const InputEvent& event)
    {
        if (this == InputResolver::getSelectedHandler())
        {
            this->bd.x = event.pos.x;
            this->bd.y = event.pos.y;
            Rectangle rec = { this->bd.x , this->bd.y , 0 ,0 };
            Vector2 v = Controls::SnapToNearestGrid(rec);
            this->bd.x = v.x;
            this->bd.y = v.y;
            if (isFirst)
            {
                posBeforeDrag = { v.x,v.y };
                isFirst = false;
            }
        }
    }
    void LogicGate::OnRelease(const InputEvent& event)
    {
        if (this == InputResolver::getSelectedHandler())
        {
            InputResolver::setSelectedHandler(nullptr);
            this->bd.x = event.pos.x;
            this->bd.y = event.pos.y;
            Rectangle rec = { this->bd.x , this->bd.y , 0 ,0 };
            Vector2 v = Controls::SnapToNearestGrid(rec);
            bool is_other_gate_exist = false;

            float new_gate_x_start = this->bd.x;
            float new_gate_y_start = this->bd.y;
            float new_gate_x_end = this->bd.x + this->bd.width;
            float new_gate_y_end = this->bd.y + this->bd.height;

            for (auto val : InputResolver::handlers)
            {
                if (auto handler = dynamic_cast<LogicGate*>(val))
                {
                    if (handler == this)
                    {
                        continue; 
                    }
                    // Get the bounding box of the existing gate
                    float existing_gate_x_start = handler->bd.x;
                    float existing_gate_y_start = handler->bd.y;
                    float existing_gate_x_end = handler->bd.x + handler->bd.width;
                    float existing_gate_y_end = handler->bd.y + handler->bd.height;

                    // Check for overlap between the new gate's bounding box and the existing gate's
                    // bounding box
                    if (!(new_gate_x_end <=
                        existing_gate_x_start ||  // New gate is to the left of the existing gate
                        new_gate_x_start >=
                        existing_gate_x_end ||  // New gate is to the right of the existing gate
                        new_gate_y_end <= existing_gate_y_start ||  // New gate is above the existing gate
                        new_gate_y_start >= existing_gate_y_end))
                    {
                        is_other_gate_exist = true;  // Overlap detected, grid is occupied
                        break;
                    }
                }
            }
            if (is_other_gate_exist)
            {
                this->bd.x = posBeforeDrag.x;
                this->bd.y = posBeforeDrag.y;
            }
            else
            {
                this->bd.x = v.x;
                this->bd.y = v.y;
            }
            isFirst = true;
        }
    }
    void LogicGate::CheckGatePartClicked(
        const Vector2& mousePosition, CircuitElements::Connection& connection)
    {
        auto inputTopRegion = Controls::CalculateRegion(this->bd, 0.05, 0.15, 0.2, 0.3);
        auto inputBottomRegion = Controls::CalculateRegion(this->bd, 0.05, 0.15, 0.7, 0.8);
        auto outputRegion = Controls::CalculateRegion(this->bd, 0.85, 0.95, 0.45, 0.55);

        std::shared_ptr<LogicGate> itself = shared_from_this();
        // TODO after dynamic input this should change
        if (CheckCollisionPointRec(mousePosition, inputTopRegion))
        {
            connection.sourceGate = itself;
            connection.sourceLogic = "A";
            Vector2 pos = { inputTopRegion.x, inputTopRegion.y };
            connection.physCon.wires.push_back(pos);
        }
        else if (CheckCollisionPointRec(mousePosition, inputBottomRegion))
        {
            connection.sourceGate = itself;
            connection.sourceLogic = "B";
            Vector2 pos = { inputBottomRegion.x, inputBottomRegion.y };
            connection.physCon.wires.push_back(pos);
        }
        else if (CheckCollisionPointRec(mousePosition, outputRegion))
        {
            connection.sourceGate = itself;
            connection.sourceLogic = "Out";
            Vector2 pos = { outputRegion.x, outputRegion.y };
            connection.physCon.wires.push_back(pos);
        }
    }
}  // namespace LogicElements