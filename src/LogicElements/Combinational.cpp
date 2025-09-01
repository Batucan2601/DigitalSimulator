#include "Combinational.h"
#include "ComponentTextures.h"

Combinational::Combinational(CircuitElements::ComponentType componentType,const std::string& logger_name)
:Component(logger_name)
{
    this->m_type = componentType;
    m_texture = LogicElements::compTexture_getTexture(componentType);
    m_logger.info("combinational gate as type: " + std::to_string(static_cast<int>(m_type)));
    
}

void Combinational::setInOutPositions()
{
    // output
    // int no_of_grid_points = this->bd.width / AppSettings::appSettings.GRID_POINT_SIZE + 1;
    for (size_t i = 0; i < this->inputs.size(); i++)
    {
        float x = this->bd.x;
        float y = this->bd.y + (i * AppSettings::appSettings.SPACING_SIZE);
        this->inputs[i].pos = {x, y};
    }
    for (size_t i = 0; i < this->outputs.size(); i++)
    {
        float x = this->bd.x + this->bd.width;
        float y = this->bd.y + (i * AppSettings::appSettings.SPACING_SIZE);
        this->outputs[i].pos = {x, y};
    }

    //enable
    float x = this->bd.x + this->bd.width/2;
    float y = this->bd.y;
    this->inputs[this->inputs.size()-1].pos = {x,y};
}
nlohmann::json Combinational::serialize() const {
    nlohmann::json j;
    j["id"] = getID();
    j["type"] = getType();
    j["position"] = {{"x", getPosition().x}, {"y", getPosition().y}};
    //j["inputs"] = getInputs();
    //j["outputs"] = getOutputs();
    return j;
}


void Combinational::onInputChanged()
{
    this->evaluate();
}