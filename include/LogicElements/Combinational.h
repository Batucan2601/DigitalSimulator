#pragma once
#include "Component.h"

class Combinational :public Component
{
  public:
        Combinational(CircuitElements::ComponentType componentType,const std::string& logger_name);
        nlohmann::json serialize() const override;
        void onInputChanged();
  private:
        void setInOutPositions() override;
};