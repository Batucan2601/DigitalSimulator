#ifndef XORGATE_H
#define XORGATE_H
#include <LogicElementBase.h>
#include <filesystem>
namespace LogicElements::Gates
{
    class XorGate : public LogicGate
    {
    public:
        XorGate(std::string &logger_name);

        void evaluate() override;
    };
}
#endif // NOTGATE_H