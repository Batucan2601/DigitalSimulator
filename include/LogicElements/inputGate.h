#ifndef INPUTGATE_H
#define INPUTGATE_H
#include <LogicElementBase.h>
#include <filesystem>

namespace LogicElements::Gates
{
    class InputGate : public LogicGate
    {
      public:
        InputGate(std::string& logger_name);

        void evaluate() override;
    };
}  // namespace LogicElements::Gates
#endif  // InoutGATE_H