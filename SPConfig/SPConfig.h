#pragma once
#include "ConfigGlobal.h"
namespace ShadowPlay
{
    class SHADOWPLAY_API SPConfig
    {
    public:
        SPConfig();
        ~SPConfig();

        uint8_t InitConfig(const char* configFile);
        uint8_t InitConfig();
    };

    class SHADOWPLAY_API SPConfigManager
    {
    public:
        SPConfigManager();
        ~SPConfigManager();

        uint8_t InitManager();

    };
}