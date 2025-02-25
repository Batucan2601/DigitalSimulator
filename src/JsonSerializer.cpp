#include "JsonSerializer.h"
using namespace LogicElements;
inline std::string gateTypeToString(LogicElements::GateType type) {
    switch (type) {
    case LogicElements::GateType::NONE:  return "NONE";
    case LogicElements::GateType::AND:   return "AND";
    case LogicElements::GateType::OR:    return "OR";
    case LogicElements::GateType::NOT:   return "NOT";
    case LogicElements::GateType::XOR:   return "XOR";
    case LogicElements::GateType::XAND:  return "XAND";
    case LogicElements::GateType::INPUT: return "INPUT";
    default: return "UNKNOWN";
    }
}
/*inline static LogicElements::LogicGate* gateTypetoClass(LogicElements::GateType type) {
    std::string logger = "";
    switch (type) {
    case LogicElements::GateType::AND:   return LogicElements::Gates::AndGate(logger);
    case LogicElements::GateType::OR:    return LogicElements::Gates::OrGate(logger);
    case LogicElements::GateType::NOT:   return LogicElements::Gates::NotGate(logger);
    case LogicElements::GateType::XOR:   return LogicElements::Gates::XorGate(logger);
    case LogicElements::GateType::XAND:  return LogicElements::Gates::XandGate(logger);
    case LogicElements::GateType::INPUT: return LogicElements::Gates::InputGate(logger);
    default: throw("INVALID CLASS");
    }
} */
inline void to_json(json& j, const Vector2& vec) {
    j = json{
        {"x", vec.x},
        {"y", vec.y}
    };
}
/*inline void to_json(json& j, const Signal& vec) {
    j = json{
       {"name", vec.name},
       {"pos", vec.pos},
       {"val", vec.val},
    };
}*/
inline void to_json(json& j, const Rectangle& rect) {
    j = json{
        {"x", rect.x},
        {"y", rect.y},
        {"width", rect.width},
        {"height", rect.height}
    };
}
/*inline void to_json(json& j, const LogicElements::LogicGate& gate) {
    j = json{
        {"bounding_box", gate.bd}, // Automatic conversion via to_json for Rectangle
        {"type", gateTypeToString(gate.m_type)},
        {"inputs", gate.inputs},
        {"outputs", gate.outputs}
        // You can add more fields here if needed.
    };
}*/

inline void to_json(json& j, const CircuitElements::PhysicalConnection& pc) {
    j = json{
        {"wires", pc.wires}
    };
}

/*inline void to_json(json& j, const CircuitElements::Connection& con) {
    j = json{
        {"sourceGate", con.sourceGate},   // Uses adl_serializer for shared_ptr<LogicGate>
        {"sourceLogic", con.sourceLogic},
        {"targetGate", con.targetGate},   // Ditto.
        {"targetLogic", con.targetLogic},
        {"is_connected", con.is_connected}
    };
} */
