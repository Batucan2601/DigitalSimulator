#include "LogicElementBase.h"

#include "Component.h"
#include "ComponentTextures.h"

#ifndef PROJECT_ROOT_DIR
#define PROJECT_ROOT_DIR "/path/to/project/root"  // Replace with the actual project root directory
#endif
#include "appSettings.h"

#include <Controls.h>
#include <Util/Utils.h>
#include "raylibHelper.h"
#include "JsonSerializer.h"

namespace LogicElements
{
    LogicGate::LogicGate(CircuitElements::ComponentType componentType,const std::string& logger_name)
     :Component(logger_name)
    {
        this->m_type = componentType;
        // type = CircuitElements::ComponentType;
        m_texture = compTexture_getTexture(componentType);
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


    void LogicGate::onInputChanged()
    {
        this->evaluate();  // Automatically reevaluate when input changes
    }

    //void LogicGate::OnInputEvent(const InputEvent& event)
    //{
    //    if (event.type == InputType::Mouse)
    //    {
    //        if (event.mouseState == MouseEventState::LeftClick)
    //        {
    //            OnLeftClick(event);
    //        }
    //        if (event.mouseState == MouseEventState::Release)
    //        {
    //            OnRelease(event);
    //        }
    //        if (event.mouseState == MouseEventState::RightClick)
    //        {
    //            OnRightClick(event);
    //        }
    //        if (event.mouseState == MouseEventState::Down)
    //        {
    //            OnDown(event);
    //        }
    //        if (event.mouseState == MouseEventState::Move)
    //        {
    //            OnMove(event);
    //        }
    //        if (event.mouseState == MouseEventState::Enter)
    //        {
    //            OnEnter(event);
    //        }
    //        if (event.mouseState == MouseEventState::Leave)
    //        {
    //            OnExit(event);
    //        }
    //    }

    //    if (event.type == InputType::Keyboard)
    //    {
    //        if (event.keyState == KeyboardEvent::KeyPress)
    //        {
    //            OnKeyPress(event);
    //        }
    //        if (event.keyState == KeyboardEvent::KeyRelease)
    //        {
    //            // OnKeyRelease(event);
    //        }
    //        if (event.keyState == KeyboardEvent::KeyRepeat)
    //        {
    //            // OnKeyRepeat(event);
    //        }
    //    }
    //}

    bool LogicGate::is_connection_clicked(const Vector2& mousePos,
                                          CircuitElements::Connection& possibleConnection)
    {
        if (this->CheckMouseOnInOut(mousePos, possibleConnection))
        {
            return true;
        }
        return false;
    }
    //void LogicGate::OnLeftClick(const InputEvent& event)
    //{
    //    // check bb
    //    Vector2 pos = {(float)event.pos.x, (float)event.pos.y};
    //    bool isCol = CheckCollisionPointRec(pos, this->bd);
    //    if (!isCol)
    //    {
    //        return;
    //    }
    //    RaylibHelper::Show(1); // shows logicGateInfo window
    //    // if it is a inputgate
    //    /*if (this->m_type == CircuitElements::ComponentType::INPUT_0)
    //    {
    //        this->m_type = CircuitElements::ComponentType::INPUT_1;
    //        this->m_texture = logicElementTextures[CircuitElements::ComponentType::INPUT_1];
    //    }
    //    else if (this->m_type == CircuitElements::ComponentType::INPUT_1)
    //    {
    //        this->m_type = CircuitElements::ComponentType::INPUT_0;
    //        this->m_texture = logicElementTextures[CircuitElements::ComponentType::INPUT_0];
    //    } */
    //    // ok first look at the selected handler, check if it is a logic gate
    //    CircuitElements::Connection possibleConnection;
    //    if (!circuit->active_wire.is_visible)  // we are not building a connection
    //    {
    //        // it cannot be a connection end
    //        // it can be a connection start, or gate select
    //        if (this->is_connection_clicked(pos, possibleConnection))
    //        {
    //            // if hits select it
    //            // possibleConnection.circuit = this->circuit;
    //            circuit->addConnection(
    //                possibleConnection.sourceGate, possibleConnection.sourceLogic,
    //                possibleConnection.targetGate, possibleConnection.targetLogic);
    //            circuit->active_wire.is_visible = true;
    //            circuit->active_wire.start = pos;
    //            circuit->active_wire.end = pos;
    //            InputResolver::RegisterHandler(
    //                static_cast<IInputHandler*>(&(circuit->active_wire)));
    //            InputResolver::setSelectedHandler(
    //                (IInputHandler*)&circuit->connections[circuit->connections.size() - 1]);
    //        }
    //        else  // select the gate
    //        {
    //            InputResolver::setSelectedHandler((IInputHandler*)this);
    //        }
    //        return;
    //    }
    //    // check if a connection already selected.
    //    if (auto handler =
    //            dynamic_cast<CircuitElements::Connection*>(InputResolver::getSelectedHandler()))
    //    {
    //        if (this->is_connection_clicked(pos, possibleConnection))
    //        {

    //            // the source should be output
    //            // the target should be an input
    //            bool is_output = false;
    //            bool is_input = false;
    //            for (size_t i = 0; i < handler->sourceGate->outputs.size(); i++)
    //            {
    //                if (handler->sourceGate->outputs[i].name == handler->sourceLogic)
    //                {
    //                    is_output = true;
    //                    break;
    //                }
    //            }
    //            for (size_t i = 0; i < possibleConnection.sourceGate->inputs.size(); i++)
    //            {
    //                if (possibleConnection.sourceGate->inputs[i].name ==
    //                    possibleConnection.sourceLogic)
    //                {
    //                    is_input = true;
    //                    break;
    //                }
    //            }
    //            if (is_output != is_input)  // if one is true one is false
    //            {
    //                return;
    //            }
    //            handler->targetGate = possibleConnection.sourceGate;
    //            handler->targetLogic = possibleConnection.sourceLogic;
    //            handler->is_connected = true;
    //            if (!is_output && !is_input)
    //            {
    //                std::shared_ptr<LogicGate> temp_ptr = std::static_pointer_cast<LogicGate>(handler->sourceGate);
    //                handler->sourceGate = handler->targetGate;
    //                handler->targetGate = temp_ptr;

    //                std::string temp_str = handler->sourceLogic;
    //                handler->sourceLogic = handler->targetLogic;
    //                handler->targetLogic = temp_str;
    //            }

    //            InputResolver::RegisterHandler(static_cast<IInputHandler*>(
    //                &circuit->connections[circuit->connections.size() - 1]));
    //        }
    //    }
    //   
    //}

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
nlohmann::json LogicGate::serialize() const {
    nlohmann::json j;
    j["id"] = getID();
    j["type"] = getType();
    j["position"] = {{"x", getPosition().x}, {"y", getPosition().y}};
    j["inputs"] = getInputs();
    j["outputs"] = getOutputs();
    return j;
}

}  // namespace LogicElements