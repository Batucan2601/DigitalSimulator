#include "JsonSerializer.h"

namespace jsonParser
{

    std::shared_ptr<CircuitElements::Circuit> loadCircuit(const std::string& filePath)
    {
        std::ifstream file(filePath);
        std::string logger_name = "LoggerName";

        if (!file.is_open())
        {
            std::cerr << "Error: Could not open file for loading!" << std::endl;
            return std::make_shared<CircuitElements::Circuit>(
                logger_name);  // Return an empty circuit
        }

        json j;
        file >> j;
        file.close();

        auto circuit = std::make_shared<CircuitElements::Circuit>(logger_name);

        // Map for fast lookup of gates by ID
        std::unordered_map<int, std::shared_ptr<LogicElements::LogicGate>> gateMap;

        // Load gates
        for (const auto& gateJson : j["gates"])
        {
            std::string logger = "LoggerName";
            auto gate = std::make_shared<LogicElements::LogicGate>(gateJson["type"], logger);
            gate->setPosition(gateJson["position"]["x"], gateJson["position"]["y"]);

            int id = gateJson["id"];
            gateMap[id] = gate;  // Store gate in the map
            circuit.get()->gates.push_back(gate);
        }

        // Load connections
        for (const auto& connJson : j["connections"])
        {
            int sourceID = connJson["sourceGate"];
            int targetID = connJson["targetGate"];

            if (gateMap.find(sourceID) != gateMap.end() && gateMap.find(targetID) != gateMap.end())
            {
                circuit.get()->addConnection(gateMap[sourceID], connJson["sourceLogic"],
                                             gateMap[targetID], connJson["targetLogic"]);
            }

            // Load wire positions
            CircuitElements::Connection& conn = circuit.get()->connections.back();
            conn.physCon.wires = connJson["wires"];
        }

        return circuit;
    }

    void saveCircuit(const CircuitElements::Circuit& circuit, const std::string& filePath)
    {
        json j;

        // Convert gates to JSON array
        json gatesArray = json::array();
        for (const auto& gate : circuit.gates)
        {
            if (gate)
            {
                json gateJson;
                to_json(gateJson, *gate);
                gatesArray.push_back(gateJson);
            }
        }
        j["gates"] = gatesArray;

        // Convert connections to JSON array
        json connectionsArray = json::array();
        for (const auto& conn : circuit.connections)
        {
            json connJson;
            to_json(connJson, conn);
            connectionsArray.push_back(connJson);
        }
        j["connections"] = connectionsArray;

        // Open file and write JSON
        std::ofstream file(filePath);
        if (file.is_open())
        {
            file << j.dump(4);  // Pretty-print JSON with indentation
            file.close();
        }
        else
        {
            std::cerr << "Error: Could not open file for saving!" << std::endl;
        }
    }

    void to_json(json& j, const LogicElements::LogicGate& gate)
    {
        j = json{{"id", gate.getID()},  // Store ID
                 {"type", gate.getType()},
                 {"position", {{"x", gate.getPosition().x}, {"y", gate.getPosition().y}}},
                 {"inputs", gate.getInputs()},
                 {"outputs", gate.getOutputs()}};
    }

    void to_json(json& j, const Vector2& v)
    {
        j = json{{"x", v.x}, {"y", v.y}};
    }

    void to_json(json& j, const CircuitElements::Connection& conn)
    {
        j = json{
            {"sourceGate", conn.sourceGate ? conn.sourceGate->getID() : -1},  // Save gate ID
            {"sourceLogic", conn.sourceLogic},
            {"targetGate", conn.targetGate ? conn.targetGate->getID() : -1},  // Save gate ID
            {"targetLogic", conn.targetLogic},
            {"wires", conn.physCon.wires}  // Save wire positions
        };
    } 


    void to_json(json& j, const Signal& signal)
    {
        j = json{{"name", signal.name},
                 {"val", signal.val},
                 {"position", {{"x", signal.pos.x}, {"y", signal.pos.y}}}};
    }

}  // namespace jsonParser
