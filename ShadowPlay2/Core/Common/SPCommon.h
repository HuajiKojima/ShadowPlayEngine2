#pragma once
#include "../Tools/SPLogger.h" 

namespace ShadowPlay
{
    struct SPAppBaseRelays
    {
        SPLogger& m_logger;
    };

    struct SPRHIBaseRelays
    {
        SPLogger& m_logger;
    };

    struct SPOpenGLBaseRelays
    {
        SPLogger& m_logger;
    };

    struct SPVulkanBaseRelays
    {
        SPLogger& m_logger;
    };

    struct SPDirectXBaseRelays
    {
        SPLogger& m_logger;
    };

    struct SPMemManagerBaseRelays
    {
        SPLogger& m_logger;
    };

}