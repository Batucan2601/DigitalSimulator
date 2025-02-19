#ifndef JSONSERIALIZER_H
#define JSONSERIALIZER_H
#include "../Libraries/json.hpp"
#include <string>
#include "logicElements.h"
#include <unordered_map>
using json = nlohmann::json;
inline void to_json(json& j, const Rectangle& rec);
inline void to_json(json& j, const LogicElements::LogicGate& gate);
inline void to_json(json& j, const CircuitElements::PhysicalConnection& physicalConnection);
inline void to_json(json& j, const CircuitElements::Connection& connection);
#endif 