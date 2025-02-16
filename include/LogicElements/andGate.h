#ifndef AND_GATE_H
#define AND_GATE_H

#include <LogicElementBase.h>
#include <filesystem>

namespace LogicElements::Gates
{
    class AndGate : public LogicGate
    {
    public:
        AndGate(std::string &logger_name);

        void evaluate() override;
    };
}

#endif // AND_GATE_H