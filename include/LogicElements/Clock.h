#pragma once
#include "Component.h"
class Clock :  public Component 
{
    public:
        Clock(const std::string& name, unsigned int tickRate );
        //void tick(); // Pure virtual function to be implemented by derived classes
        void reset(); // Pure virtual function to reset the clock
        void evaluate() override; // Override the evaluate function to implement clock behavior
        nlohmann::json serialize() const override;
        void onInputChanged();

    private:
        unsigned int tick_rate; // The rate at which the clock ticks, in Hz
        unsigned int ns; // nanoseconds to wait 
        void setInOutPositions() override;
};