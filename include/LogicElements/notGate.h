#ifndef NOTGATE_H
#define NOTGATE_H
#include <LogicElementBase.h>
#include <filesystem>
namespace LogicElements::Gates
{
    class NotGate : public LogicGate
    {
    public:
        NotGate(std::string &logger_name);

        void evaluate() override;
    };
}
#endif // NOTGATE_H