#include "ConfigPreCompileHeader.h"
#include "SPConfig.h"

namespace ShadowPlay
{
    SPConfig::SPConfig()
    {
    }

    SPConfig::~SPConfig()
    {
    }

    uint8_t SPConfig::InitConfig(const char *configFile)
    {
        //In debug mode
        return 0;
    }

    uint8_t SPConfig::InitConfig()
    {
        //In release mode
        return 0;
    }
    SPConfigManager::SPConfigManager()
    {
    }
    SPConfigManager::~SPConfigManager()
    {
    }
    uint8_t SPConfigManager::InitManager()
    {
        return 0;
    }
}