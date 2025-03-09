#ifndef LOGIC_ELEMENT_FACTORY_H
#define LOGIC_ELEMENT_FACTORY_H

#include "LogicElementBase.h"

#include <memory>

namespace LogicElements
{
    class LogicElementFactory
    {
      public:
        static LogicGate createGate(GateType type, std::string logger_name);
    };
}  // namespace LogicElements

#endif  // LOGIC_ELEMENT_FACTORY_H