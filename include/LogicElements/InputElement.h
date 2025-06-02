#pragma once
#include "Component.h"
#include "JsonSerializer.h"

class InputElement : public Component
{
  public:
  InputElement(); // Input 
  void OnLeftClick(const InputEvent& event) override;
  void OnInputEvent(const InputEvent& event) override;
  void onInputChanged() override;  // Override observer function
  nlohmann::json serialize() const override;
  
  private:
  void setInOutPositions() override;
};  
