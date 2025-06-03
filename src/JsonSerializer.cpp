#include "JsonSerializer.h"


SP_Circuit jsonparser_loadCircuit(const std::string& filePath)
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
    std::unordered_map<int, std::shared_ptr<Component>> gateMap;

    // Load gates
    for (const auto& gateJson : j["gates"])
    {
        std::string logger = "LoggerName";
        auto gate = std::make_shared<LogicElements::LogicGate>(gateJson["type"], logger);
        int id = gateJson["id"];
        // Load inputs
        if (gateJson.contains("inputs") && gateJson["inputs"].is_array()) {
            for (const auto& inputJson : gateJson["inputs"]) {
                Signal input;
                input.name = inputJson.value("name", "");
                input.val = inputJson.value("val", false);

                if (inputJson.contains("position") && inputJson["position"].is_object()) {
                    input.pos.x = inputJson["position"].value("x", 0.0f);
                    input.pos.y = inputJson["position"].value("y", 0.0f);
                }

                gate->inputs.push_back(input);
            }
        }

        // Load outputs
        if (gateJson.contains("outputs") && gateJson["outputs"].is_array()) {
            for (const auto& outputJson : gateJson["outputs"]) {
                Signal output;
                output.name = outputJson.value("name", "");
                output.val = outputJson.value("val", false);

                if (outputJson.contains("position") && outputJson["position"].is_object()) {
                    output.pos.x = outputJson["position"].value("x", 0.0f);
                    output.pos.y = outputJson["position"].value("y", 0.0f);
                }

                gate->outputs.push_back(output);
            }
        }
        gate->setPosition(gateJson["position"]["x"], gateJson["position"]["y"]);
        gateMap[id] = gate;  // Store gate in the map
        gate->circuit = circuit.get();
        circuit.get()->gates.push_back(gate);
    }
    for (const auto& gateJson : j["inputs"])
    {
        std::string logger = "LoggerName";
        auto gate = std::make_shared<InputElement>();
        int id = gateJson["id"];
        // Load outputs
        if (gateJson.contains("outputs") && gateJson["outputs"].is_array()) {
            for (const auto& outputJson : gateJson["outputs"]) {
                Signal output;
                output.name = outputJson.value("name", "");
                output.val = outputJson.value("val", false);

                if (outputJson.contains("position") && outputJson["position"].is_object()) {
                    output.pos.x = outputJson["position"].value("x", 0.0f);
                    output.pos.y = outputJson["position"].value("y", 0.0f);
                }

                gate->outputs.push_back(output);
            }
        }
        gate->setPosition(gateJson["position"]["x"], gateJson["position"]["y"]);
        gateMap[id] = gate;  // Store gate in the map
        gate->circuit = circuit.get();
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
        conn.physCon.wires = connJson["wires"].get<std::vector<Vector2>>();
        conn.is_connected = true;
    }

    return circuit;
}
/*void to_json(json& j, const Component& comp)
{
    j = json{{"id", comp.getID()},  // Store ID
                {"type", comp.getType()},
                {"position", {{"x", comp.getPosition().x}, {"y", comp.getPosition().y}}},
                {"inputs", comp.getInputs()},
                {"outputs", comp.getOutputs()}};
}*/
void jsonparser_saveCircuit(const CircuitElements::Circuit& circuit, const std::string& filePath)
{
    json j;
    std::cout << circuit.gates.size() << std::endl;
    // Convert gates to JSON array
    json gatesArray = json::array();
    json inputsArray = json::array();
    for (const auto& gate : circuit.gates)
    {
        json gateJson;
        if (auto logicGate = std::dynamic_pointer_cast<LogicElements::LogicGate>(gate))
        {
            to_json(gateJson, *logicGate);
            gatesArray.push_back(gateJson);
        }
        else if (auto inputElem = std::dynamic_pointer_cast<InputElement>(gate))
        {
            to_json(gateJson, *inputElem);
            inputsArray.push_back(gateJson);
        }
    }
    
    j["gates"] = gatesArray;
    j["inputs"] = inputsArray;
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
void to_json(json& j, const InputElement& gate)
{
    j = json{{"id", gate.getID()},  // Store ID
                {"type", gate.getType()},
                {"position", {{"x", gate.getPosition().x}, {"y", gate.getPosition().y}}},
                {"outputs", gate.getOutputs()}};
} 

void to_json(json& j, const Vector2& v)
{
    j = json{{"x", v.x}, {"y", v.y}};
}
void from_json(const json& j, Vector2& v)
{
    v.x = j.at("x").get<float>();
    v.y = j.at("y").get<float>();
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

inline void from_json(const nlohmann::json& j, Signal& signal)
{
    signal.name = j.at("name").get<std::string>();
    signal.val = j.at("val").get<bool>();
    signal.pos.x = j.at("position").at("x").get<float>();
    signal.pos.y = j.at("position").at("y").get<float>();
}
