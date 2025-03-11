#ifndef LOGIC_ELEMENT_FACTORY_H
#define LOGIC_ELEMENT_FACTORY_H

#include "LogicElementBase.h"

#include <memory>

namespace CircuitElements
{
    class Circuit; 
}
namespace LogicElements
{
    class LogicElementFactory
    {
      public:
        void initFactory(std::shared_ptr<CircuitElements::Circuit> circuit);
        std::shared_ptr<LogicGate>  createGate(GateType type, std::string logger_name);
        std::shared_ptr<CircuitElements::Circuit> circuit;
    };
}  // namespace LogicElements

#endif  // LOGIC_ELEMENT_FACTORY_H