#pragma once
#include "raylib.h"
#include <string>
enum class SignalVal
{
    SIGNAL_0,
    SIGNAL_1,
    SIGNAL_X,
    SIGNAL_Z
};

inline SignalVal signal_and(SignalVal a, SignalVal b )
{
    if( a == SignalVal::SIGNAL_Z ||  b == SignalVal::SIGNAL_Z) return SignalVal::SIGNAL_Z;
    if( a == SignalVal::SIGNAL_X ||  b == SignalVal::SIGNAL_X ) return SignalVal::SIGNAL_X;
    if( a == SignalVal::SIGNAL_0 ||  b == SignalVal::SIGNAL_0) return SignalVal::SIGNAL_0;
    return SignalVal::SIGNAL_1;
}
inline SignalVal signal_or(SignalVal a, SignalVal b )
{
    if( a == SignalVal::SIGNAL_Z ||  b == SignalVal::SIGNAL_Z) return SignalVal::SIGNAL_Z;
    if( a == SignalVal::SIGNAL_X ||  b == SignalVal::SIGNAL_X ) return SignalVal::SIGNAL_X;
    if( a == SignalVal::SIGNAL_1 ||  b == SignalVal::SIGNAL_1) return SignalVal::SIGNAL_1;
    return SignalVal::SIGNAL_0;
}
inline SignalVal signal_not(SignalVal a)
{
    if( a == SignalVal::SIGNAL_Z ) return SignalVal::SIGNAL_Z;
    if( a == SignalVal::SIGNAL_X  ) return SignalVal::SIGNAL_X;
    if( a == SignalVal::SIGNAL_1 ) return SignalVal::SIGNAL_0;
    return SignalVal::SIGNAL_1;
}
inline SignalVal signal_xor(SignalVal a, SignalVal b )
{
    if( a == SignalVal::SIGNAL_Z ||  b == SignalVal::SIGNAL_Z) return SignalVal::SIGNAL_Z;
    if( a == SignalVal::SIGNAL_X ||  b == SignalVal::SIGNAL_X ) return SignalVal::SIGNAL_X;
    if( a ==  b) return SignalVal::SIGNAL_0;
    return SignalVal::SIGNAL_1;
}

struct Signal
{
    std::string name;  // Optional: if you want to name each signal
    SignalVal val;          // The state of the signal
    Vector2 pos;
    Signal(const std::string& n = "", SignalVal l = SignalVal::SIGNAL_Z) : name(n), val(l) {}
    bool operator==(const Signal& other) const
    {
        return name == other.name && val == other.val;
    }
};