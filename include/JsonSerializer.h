#ifndef JSONSERIALIZER_H
#define JSONSERIALIZER_H

#include "../Libraries/json.hpp"
#include "LogicElements.h"
#include "raylib.h"  // Include Raylib for Vector2

#include <fstream>
#include <vector>

namespace jsonParser
{
    using json = nlohmann::json;

    void saveCircuit(const CircuitElements::Circuit& circuit, const std::string& filePath);
    std::shared_ptr<CircuitElements::Circuit> loadCircuit(const std::string& filePath);

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
}  // namespace nlohmann

#endif  // JSONSERIALIZER_H
