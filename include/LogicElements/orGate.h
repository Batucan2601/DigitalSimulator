#ifndef ORGATE_H
#define ORGATE_H
#include <LogicElementBase.h>
#include <filesystem>
namespace LogicElements::Gates
{
    class OrGate : public LogicGate
    {
    public:
        OrGate(std::string &logger_name);

        void evaluate() override;
    };
}
#endif // ORGATE_H