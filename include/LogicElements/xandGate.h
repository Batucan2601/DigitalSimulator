#ifndef XANDGATE_H
#define XANDGATE_H
#include <LogicElementBase.h>
#include <filesystem>

namespace LogicElements::Gates
{
    class XandGate : public LogicGate
    {
    public:
        XandGate(std::string &logger_name);

        void evaluate() override;
    };
}
#endif // NOTGATE_H