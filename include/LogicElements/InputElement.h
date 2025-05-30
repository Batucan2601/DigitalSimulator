#pragma once
#include "Component.h"

class InputElement : public Component
{
  public:
  InputElement(); // Input 
  void OnLeftClick(const InputEvent& event) override;
  void OnInputEvent(const InputEvent& event) override;
  void onInputChanged() override;  // Override observer function

  private:
  void setInOutPositions() override;
};  
