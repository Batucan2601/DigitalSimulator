#pragma once
#include "Component.h"
#include "JsonSerializer.h"

class InputElement : public Component
{
  public:
  InputElement(const std::string& logger_name); // Input 
  void onInputChanged() override;  // Override observer function
  void OnLeftClick(const InputEvent& event) override;

  nlohmann::json serialize() const override;
  //ClassLogger m_logger;
  private:
  void setInOutPositions() override;
};  
