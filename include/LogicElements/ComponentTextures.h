#pragma once
#include "LogicElementBase.h"
#include <map>
#include <memory>
namespace LogicElements {
    extern std::map<CircuitElements::ComponentType, Texture> logicElementTextures;
    extern std::shared_ptr<std::vector<CircuitElements::ComponentInfo>> componentInfoList;
    void comptextures_init_logicTextures();
    Texture2D compTexture_getTexture(CircuitElements::ComponentType type );
}