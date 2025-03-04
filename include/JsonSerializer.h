#ifndef JSONSERIALIZER_H
#define JSONSERIALIZER_H

#include "../Libraries/json.hpp"
#include "Component.h"
#include "LogicElements.h"
#include "raylib.h"  // Include Raylib for Vector2

#include <common_types.h>
#include <fstream>
#include <vector>

namespace jsonParser
{
    using json = nlohmann::json;

    void saveCircuit(const CircuitElements::Circuit& circuit, const std::string& filePath);
    SP_Circuit loadCircuit(const std::string& filePath);

    // Explicitly declare to_json functions
    void to_json(json& j, const LogicElements::LogicGate& gate);
    void to_json(json& j, const CircuitElements::Connection& conn);

}  // namespace jsonParser

// Define to_json for Raylib's Vector2 in nlohmann/json's namespace
namespace nlohmann
{
    template<>
    struct adl_serializer<Vector2>
    {
        static void to_json(json& j, const Vector2& v)
        {
            j = json{{"x", v.x}, {"y", v.y}};
        }

        static void from_json(const json& j, Vector2& v)
        {
            j.at("x").get_to(v.x);
            j.at("y").get_to(v.y);
        }
    };

    template<>
    struct adl_serializer<Signal>
    {
        static void to_json(json& j, const Signal& signal)
        {
            j = json{{"name", signal.name},
                     {"val", signal.val},
                     {"position", signal.pos}};  // `Vector2` will be automatically serialized
        }

        static void from_json(const json& j, Signal& signal)
        {
            j.at("name").get_to(signal.name);
            j.at("val").get_to(signal.val);
            j.at("position")
                .get_to(
                    signal.pos);  // `Vector2` deserialization handled by its own `adl_serializer`
        }
    };

}  // namespace nlohmann

#endif  // JSONSERIALIZER_H
