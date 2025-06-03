#include "LogicElementBase.h"
#include "Component.h"
#include "ComponentTextures.h"
#ifndef PROJECT_ROOT_DIR
#define PROJECT_ROOT_DIR "/path/to/project/root"  // Replace with the actual project root directory
#endif
#include "appSettings.h"

namespace LogicElements
{
    std::map<CircuitElements::ComponentType, Texture> logicElementTextures;
    std::shared_ptr<std::vector<CircuitElements::ComponentInfo>> componentInfoList;
    void init_OutlinedLogicTextures();
    void init_FilledLogicTextures();
     
    void comptextures_init_logicTextures()
    {
        init_OutlinedLogicTextures();
        init_FilledLogicTextures();

        componentInfoList = std::make_shared<std::vector<CircuitElements::ComponentInfo>>();
        componentInfoList->push_back(CircuitElements::ComponentInfo("AND Gate", CircuitElements::ComponentType::AND,
                                         &logicElementTextures[CircuitElements::ComponentType::AND],
                                         &logicElementTextures[CircuitElements::ComponentType::AND_FILLED]));
        componentInfoList->push_back(CircuitElements::ComponentInfo("OR Gate", CircuitElements::ComponentType::OR,
                                         &logicElementTextures[CircuitElements::ComponentType::OR],
                                         &logicElementTextures[CircuitElements::ComponentType::OR_FILLED]));
        componentInfoList->push_back(CircuitElements::ComponentInfo("NOT Gate", CircuitElements::ComponentType::NOT,
                                         &logicElementTextures[CircuitElements::ComponentType::NOT],
                                         &logicElementTextures[CircuitElements::ComponentType::NOT_FILLED]));
        componentInfoList->push_back(CircuitElements::ComponentInfo("XOR Gate", CircuitElements::ComponentType::XOR,
                                         &logicElementTextures[CircuitElements::ComponentType::XOR],
                                         &logicElementTextures[CircuitElements::ComponentType::XOR_FILLED]));
        componentInfoList->push_back(CircuitElements::ComponentInfo("XAND Gate", CircuitElements::ComponentType::XAND,
                                         &logicElementTextures[CircuitElements::ComponentType::XAND],
                                         &logicElementTextures[CircuitElements::ComponentType::XAND_FILLED]));
        componentInfoList->push_back(CircuitElements::ComponentInfo("INPUT0 Gate", CircuitElements::ComponentType::INPUT_0,
                                         &logicElementTextures[CircuitElements::ComponentType::INPUT_0],
                                         &logicElementTextures[CircuitElements::ComponentType::INPUT_0]));
        componentInfoList->push_back(CircuitElements::ComponentInfo("INPUT1 Gate", CircuitElements::ComponentType::INPUT_1,
                                         &logicElementTextures[CircuitElements::ComponentType::INPUT_1],
                                         &logicElementTextures[CircuitElements::ComponentType::INPUT_1]));
         componentInfoList->push_back(CircuitElements::ComponentInfo("NOR Gate", CircuitElements::ComponentType::INPUT_1,
                                         &logicElementTextures[CircuitElements::ComponentType::NOR],
                                         &logicElementTextures[CircuitElements::ComponentType::NOR]));
        componentInfoList->push_back(CircuitElements::ComponentInfo("CLK", CircuitElements::ComponentType::CLK,
                                         &logicElementTextures[CircuitElements::ComponentType::CLK],
                                         &logicElementTextures[CircuitElements::ComponentType::CLK]));
    }
    Texture2D compTexture_getTexture(CircuitElements::ComponentType type )
    {
        return logicElementTextures[type];
    }
    void init_OutlinedLogicTextures()
    {
        std::string folder_path = "assets/gates/outlined_gates/";  // Use relative path
        std::string file_path;

        file_path = folder_path + "and.png";  // Use relative path
        std::string full_path = (std::filesystem::path(PROJECT_ROOT_DIR) / file_path).string();
        logicElementTextures[CircuitElements::ComponentType::AND] = LoadTexture(full_path.c_str());

        file_path = folder_path + "or.png";  // Use relative path
        full_path = (std::filesystem::path(PROJECT_ROOT_DIR) / file_path).string();
        logicElementTextures[CircuitElements::ComponentType::OR] = LoadTexture(full_path.c_str());

        file_path = folder_path + "not.png";  // Use relative path
        full_path = (std::filesystem::path(PROJECT_ROOT_DIR) / file_path).string();
        logicElementTextures[CircuitElements::ComponentType::NOT] = LoadTexture(full_path.c_str());

        file_path = folder_path + "xand.png";  // Use relative path
        full_path = (std::filesystem::path(PROJECT_ROOT_DIR) / file_path).string();
        logicElementTextures[CircuitElements::ComponentType::XOR] = LoadTexture(full_path.c_str());

        file_path = folder_path + "xor.png";  // Use relative path
        full_path = (std::filesystem::path(PROJECT_ROOT_DIR) / file_path).string();
        logicElementTextures[CircuitElements::ComponentType::XAND] = LoadTexture(full_path.c_str());

        file_path = folder_path + "xor.png";  // Use relative path
        full_path = (std::filesystem::path(PROJECT_ROOT_DIR) / file_path).string();
        logicElementTextures[CircuitElements::ComponentType::NOR] = LoadTexture(full_path.c_str());

        file_path = folder_path + "0.png";  // Use relative path
        full_path = (std::filesystem::path(PROJECT_ROOT_DIR) / file_path).string();
        logicElementTextures[CircuitElements::ComponentType::INPUT_0] = LoadTexture(full_path.c_str());

        file_path = folder_path + "1.png";  // Use relative path
        full_path = (std::filesystem::path(PROJECT_ROOT_DIR) / file_path).string();
        logicElementTextures[CircuitElements::ComponentType::INPUT_1] = LoadTexture(full_path.c_str());

        file_path = folder_path + "1.png";  // Use relative path
        full_path = (std::filesystem::path(PROJECT_ROOT_DIR) / file_path).string();
        logicElementTextures[CircuitElements::ComponentType::CLK] = LoadTexture(full_path.c_str());
    }
    void init_FilledLogicTextures()
    {
        std::string folder_path = "assets/gates/filled_gates/";  // Use relative path
        std::string file_path;
        std::string full_path = (std::filesystem::path(PROJECT_ROOT_DIR) / file_path).string();

        file_path = folder_path + "and.png";  // Use relative path
        full_path = (std::filesystem::path(PROJECT_ROOT_DIR) / file_path).string();
        logicElementTextures[CircuitElements::ComponentType::AND_FILLED] = LoadTexture(full_path.c_str());

        file_path = folder_path + "or.png";  // Use relative path
        full_path = (std::filesystem::path(PROJECT_ROOT_DIR) / file_path).string();
        logicElementTextures[CircuitElements::ComponentType::OR_FILLED] = LoadTexture(full_path.c_str());

        file_path = folder_path + "not.png";  // Use relative path
        full_path = (std::filesystem::path(PROJECT_ROOT_DIR) / file_path).string();
        logicElementTextures[CircuitElements::ComponentType::NOT_FILLED] = LoadTexture(full_path.c_str());

        file_path = folder_path + "xand.png";  // Use relative path
        full_path = (std::filesystem::path(PROJECT_ROOT_DIR) / file_path).string();
        logicElementTextures[CircuitElements::ComponentType::XOR_FILLED] = LoadTexture(full_path.c_str());

        file_path = folder_path + "xor.png";  // Use relative path
        full_path = (std::filesystem::path(PROJECT_ROOT_DIR) / file_path).string();
        logicElementTextures[CircuitElements::ComponentType::XAND_FILLED] = LoadTexture(full_path.c_str());
    }
}