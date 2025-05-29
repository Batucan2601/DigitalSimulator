#include "LogicElementBase.h"

#include "Component.h"

#ifndef PROJECT_ROOT_DIR
#define PROJECT_ROOT_DIR "/path/to/project/root"  // Replace with the actual project root directory
#endif
#include "appSettings.h"

#include <Controls.h>
#include <Util/Utils.h>
#include "raylibHelper.h"

namespace LogicElements
{
    std::map<CircuitElements::ComponentType, Texture> logicElementTextures;
    std::shared_ptr<std::vector<CircuitElements::ComponentInfo>> componentInfoList;

    void init_logicTextures()
    {
        init_OutlinedLogicTextures();
        init_FilledLogicTextures();

        componentInfoList = std::make_shared<std::vector<CircuitElements::ComponentInfo>>();
        componentInfoList->push_back(CircuitElements::ComponentInfo("AND Gate", CircuitElements::ComponentType::AND,
                                         &logicElementTextures[CircuitElements::ComponentType::AND],
                                         &logicElementTextures[CircuitElements::ComponentType::AND_FILLED]));
        componentInfoList->push_back(CircuitElements::ComponentInfo("OR Gate", CircuitElements::ComponentType::OR,
                                         &logicElementTextures[CircuitElements::ComponentType::OR],
                                         &logicElementTextures[CircuitElements::ComponentType::OR_FILLED]));
        componentInfoList->push_back(CircuitElements::ComponentInfo("NOT Gate", CircuitElements::ComponentType::NOT,
                                         &logicElementTextures[CircuitElements::ComponentType::NOT],
                                         &logicElementTextures[CircuitElements::ComponentType::NOT_FILLED]));
        componentInfoList->push_back(CircuitElements::ComponentInfo("XOR Gate", CircuitElements::ComponentType::XOR,
                                         &logicElementTextures[CircuitElements::ComponentType::XOR],
                                         &logicElementTextures[CircuitElements::ComponentType::XOR_FILLED]));
        componentInfoList->push_back(CircuitElements::ComponentInfo("XAND Gate", CircuitElements::ComponentType::XAND,
                                         &logicElementTextures[CircuitElements::ComponentType::XAND],
                                         &logicElementTextures[CircuitElements::ComponentType::XAND_FILLED]));
        componentInfoList->push_back(CircuitElements::ComponentInfo("INPUT0 Gate", CircuitElements::ComponentType::INPUT_0,
                                         &logicElementTextures[CircuitElements::ComponentType::INPUT_0],
                                         &logicElementTextures[CircuitElements::ComponentType::INPUT_0]));
        componentInfoList->push_back(CircuitElements::ComponentInfo("INPUT1 Gate", CircuitElements::ComponentType::INPUT_1,
                                         &logicElementTextures[CircuitElements::ComponentType::INPUT_1],
                                         &logicElementTextures[CircuitElements::ComponentType::INPUT_1]));
        componentInfoList->push_back(CircuitElements::ComponentInfo("CLK", CircuitElements::ComponentType::CLK,
                                         &logicElementTextures[CircuitElements::ComponentType::CLK],
                                         &logicElementTextures[CircuitElements::ComponentType::CLK]));
    }

    void init_OutlinedLogicTextures()
    {
        std::string folder_path = "assets/gates/outlined_gates/";  // Use relative path
        std::string file_path;

        file_path = folder_path + "and.png";  // Use relative path
        std::string full_path = (std::filesystem::path(PROJECT_ROOT_DIR) / file_path).string();
        logicElementTextures[CircuitElements::ComponentType::AND] = LoadTexture(full_path.c_str());

        file_path = folder_path + "or.png";  // Use relative path
        full_path = (std::filesystem::path(PROJECT_ROOT_DIR) / file_path).string();
        logicElementTextures[CircuitElements::ComponentType::OR] = LoadTexture(full_path.c_str());

        file_path = folder_path + "not.png";  // Use relative path
        full_path = (std::filesystem::path(PROJECT_ROOT_DIR) / file_path).string();
        logicElementTextures[CircuitElements::ComponentType::NOT] = LoadTexture(full_path.c_str());

        file_path = folder_path + "xand.png";  // Use relative path
        full_path = (std::filesystem::path(PROJECT_ROOT_DIR) / file_path).string();
        logicElementTextures[CircuitElements::ComponentType::XOR] = LoadTexture(full_path.c_str());

        file_path = folder_path + "xor.png";  // Use relative path
        full_path = (std::filesystem::path(PROJECT_ROOT_DIR) / file_path).string();
        logicElementTextures[CircuitElements::ComponentType::XAND] = LoadTexture(full_path.c_str());

        file_path = folder_path + "0.png";  // Use relative path
        full_path = (std::filesystem::path(PROJECT_ROOT_DIR) / file_path).string();
        logicElementTextures[CircuitElements::ComponentType::INPUT_0] = LoadTexture(full_path.c_str());

        file_path = folder_path + "1.png";  // Use relative path
        full_path = (std::filesystem::path(PROJECT_ROOT_DIR) / file_path).string();
        logicElementTextures[CircuitElements::ComponentType::INPUT_1] = LoadTexture(full_path.c_str());

        file_path = folder_path + "1.png";  // Use relative path
        full_path = (std::filesystem::path(PROJECT_ROOT_DIR) / file_path).string();
        logicElementTextures[CircuitElements::ComponentType::CLK] = LoadTexture(full_path.c_str());
    }
    void init_FilledLogicTextures()
    {
        std::string folder_path = "assets/gates/filled_gates/";  // Use relative path
        std::string file_path;
        std::string full_path = (std::filesystem::path(PROJECT_ROOT_DIR) / file_path).string();

        file_path = folder_path + "and.png";  // Use relative path
        full_path = (std::filesystem::path(PROJECT_ROOT_DIR) / file_path).string();
        logicElementTextures[CircuitElements::ComponentType::AND_FILLED] = LoadTexture(full_path.c_str());

        file_path = folder_path + "or.png";  // Use relative path
        full_path = (std::filesystem::path(PROJECT_ROOT_DIR) / file_path).string();
        logicElementTextures[CircuitElements::ComponentType::OR_FILLED] = LoadTexture(full_path.c_str());

        file_path = folder_path + "not.png";  // Use relative path
        full_path = (std::filesystem::path(PROJECT_ROOT_DIR) / file_path).string();
        logicElementTextures[CircuitElements::ComponentType::NOT_FILLED] = LoadTexture(full_path.c_str());

        file_path = folder_path + "xand.png";  // Use relative path
        full_path = (std::filesystem::path(PROJECT_ROOT_DIR) / file_path).string();
        logicElementTextures[CircuitElements::ComponentType::XOR_FILLED] = LoadTexture(full_path.c_str());

        file_path = folder_path + "xor.png";  // Use relative path
        full_path = (std::filesystem::path(PROJECT_ROOT_DIR) / file_path).string();
        logicElementTextures[CircuitElements::ComponentType::XAND_FILLED] = LoadTexture(full_path.c_str());
    }

    LogicGate::LogicGate(CircuitElements::ComponentType componentType, std::string& logger_name)
        : m_type(componentType), m_logger(logger_name)
    {
        static int nextId = 0;
        id = nextId++;  // Assign a unique ID
        //Component();
        // type = CircuitElements::ComponentType;
        m_texture = logicElementTextures[componentType];
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
        // int no_of_grid_points = this->bd.width / AppSettings::appSettings.GRID_POINT_SIZE + 1;
        for (size_t i = 0; i < this->inputs.size(); i++)
        {
            float x = this->bd.x;
            float y = this->bd.y + (i * AppSettings::appSettings.SPACING_SIZE);
            this->inputs[i].pos = {x, y};
        }
        this->outputs[0].pos = {this->bd.x + this->bd.width, this->bd.y + this->bd.height / 2};
    }



    CircuitElements::ComponentType LogicGate::getType() const
    {
        return m_type;
    }

    const Texture2D& LogicGate::getTexture() const
    {
        return m_texture;
    }


    void LogicGate::onInputChanged()
    {
        this->evaluate();  // Automatically reevaluate when input changes
    }

    void LogicGate::OnInputEvent(const InputEvent& event)
    {
        std::cout << "LogicGate OnInputEvent called" << std::endl;
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
        RaylibHelper::Show(1); // shows logicGateInfo window
        // if it is a inputgate
        if (this->m_type == CircuitElements::ComponentType::INPUT_0)
        {
            this->m_type = CircuitElements::ComponentType::INPUT_1;
            this->m_texture = logicElementTextures[CircuitElements::ComponentType::INPUT_1];
        }
        else if (this->m_type == CircuitElements::ComponentType::INPUT_1)
        {
            this->m_type = CircuitElements::ComponentType::INPUT_0;
            this->m_texture = logicElementTextures[CircuitElements::ComponentType::INPUT_0];
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
                    std::shared_ptr<LogicGate> temp_ptr = std::static_pointer_cast<LogicGate>(handler->sourceGate);
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
       
    }

    bool LogicGate::CheckMouseOnInOut(const Vector2& mousePosition,
                                      CircuitElements::Connection& connection)
    {
        std::cout << "CheckMouseOnInOut called" << std::endl;
        std::shared_ptr<Component> itself = std::enable_shared_from_this<Component>::shared_from_this();
        std::cout << "itself: " << itself.get() << std::endl;
        Rectangle rec;
        for (size_t i = 0; i < inputs.size(); i++)
        {
            rec.x = inputs[i].pos.x - AppSettings::appSettings.IN_OUT_RECT_WIDTH;
            rec.y = inputs[i].pos.y - AppSettings::appSettings.IN_OUT_RECT_WIDTH;
            rec.width = AppSettings::appSettings.IN_OUT_INTERACTION;
            rec.height = AppSettings::appSettings.IN_OUT_INTERACTION;
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
            rec.x = outputs[i].pos.x - AppSettings::appSettings.IN_OUT_RECT_WIDTH;
            rec.y = outputs[i].pos.y - AppSettings::appSettings.IN_OUT_RECT_WIDTH;
            rec.width = AppSettings::appSettings.IN_OUT_INTERACTION;
            rec.height = AppSettings::appSettings.IN_OUT_INTERACTION;
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