#ifndef LOGIC_ELEMENT_FACTORY_H
#define LOGIC_ELEMENT_FACTORY_H

#include "LogicElementBase.h"

#include <memory>

namespace LogicElements
{
    class LogicElementFactory
    {
      public:
      static std::shared_ptr<Component> createGate(CircuitElements::ComponentType type, std::string logger_name);
      static std::shared_ptr<Component> createInput(std::string logger_name);

    };
}  // namespace LogicElements

#endif  // LOGIC_ELEMENT_FACTORY_H