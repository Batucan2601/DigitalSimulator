#ifndef JSONSERIALIZER_H
#define JSONSERIALIZER_H

#include "../Libraries/json.hpp"
#include "Component.h"
#include "LogicElements.h"
#include "InputElement.h"
#include "raylib.h"  // Include Raylib for Vector2

#include <common_types.h>
#include <fstream>
#include <vector>

namespace LogicElements {
    class LogicGate;
}
class InputElement;

using json = nlohmann::json;

void jsonparser_saveCircuit(CircuitElements::Circuit& circuit, const std::string& filePath);
SP_Circuit jsonparser_loadCircuit(const std::string& filePath);

// Explicitly declare to_json functions
inline void to_json(nlohmann::json& j, const Component& comp) {
    j = comp.serialize();  // Use polymorphism!
}
void to_json(json& j, const LogicElements::LogicGate& gate);
void to_json(json& j, const InputElement& gate);
void to_json(json& j, const Vector2& v);
void to_json(json& j, const CircuitElements::Connection& conn);
void to_json(json& j, const Signal& signal);
void from_json(const json& j, Vector2& v);
inline void from_json(const nlohmann::json& j, Signal& signal);





#endif  // JSONSERIALIZER_H
