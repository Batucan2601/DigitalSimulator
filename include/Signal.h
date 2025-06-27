#pragma once
#include "raylib.h"
#include <string>
#include <vector>
enum class SignalVal
{
    SIGNAL_0,
    SIGNAL_1,
    SIGNAL_X,
    SIGNAL_Z
};
enum class SignalType
{
    INPUT,
    OUTPUT,
    INTERNAL
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

inline std::vector<SignalVal> signal_and(std::vector<SignalVal> a, std::vector<SignalVal> b )
{
    if( a.size() != b.size() )
    {
        throw std::invalid_argument("Signal vectors must be of the same size for AND operation.");
    }
    std::vector<SignalVal> result(a.size(), SignalVal::SIGNAL_Z);
    for (size_t i = 0; i <a.size() ; i++)
    {
        result[i] = (signal_and(a[i], b[i]));
    }
    return result;
}

inline std::vector<SignalVal> signal_or(std::vector<SignalVal> a, std::vector<SignalVal> b )
{
    if( a.size() != b.size() )
    {
        throw std::invalid_argument("Signal vectors must be of the same size for AND operation.");
    }
    std::vector<SignalVal> result(a.size(), SignalVal::SIGNAL_Z);
    for (size_t i = 0; i <a.size() ; i++)
    {
        result[i] = (signal_or(a[i], b[i]));
    }
    return result;
}

inline std::vector<SignalVal> signal_not(std::vector<SignalVal> a)
{
    std::vector<SignalVal> result(a.size(), SignalVal::SIGNAL_Z);
    for (size_t i = 0; i <a.size() ; i++)
    {
        result[i] = (signal_not(a[i]));
    }
    return result;
}

inline std::vector<SignalVal> signal_xor(std::vector<SignalVal> a, std::vector<SignalVal> b )
{
    if( a.size() != b.size() )
    {
        throw std::invalid_argument("Signal vectors must be of the same size for AND operation.");
    }
    std::vector<SignalVal> result(a.size(), SignalVal::SIGNAL_Z);
    for (size_t i = 0; i <a.size() ; i++)
    {
        result[i] = (signal_xor(a[i], b[i]));
    }
    return result;
}


struct Signal
{
    std::string name;
    Vector2 pos;
    std::vector<SignalVal> val;
    SignalType type = SignalType::INTERNAL;

    Signal(const std::string& n = "", SignalVal l = SignalVal::SIGNAL_Z)
        : name(n), val{l}
    {
    }

    bool operator==(const Signal& other) const
    {
        return name == other.name && val == other.val;
    }
};


