#pragma once
#include "Component.h"

class InputElement : public Component
{
  public:
  InputElement(CircuitElements::ComponentType componentType); // Input 
  void OnLeftClick(const InputEvent& event) override;
  void setInOutPositions();
};  
