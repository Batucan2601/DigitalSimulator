#ifndef GATEOBSERVER_H
#define GATEOBSERVER_H

namespace LogicElements
{
    class GateObserver
    {
      public:
        virtual ~GateObserver() = default;
        virtual void onInputChanged() = 0;  // Notify observers when input changes
    };
}  // namespace LogicElements

#endif  // GATEOBSERVER_H