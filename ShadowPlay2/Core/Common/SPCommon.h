#pragma once
#include "../Tools/SPLogger.h"
#include "../../Engine/Math/SPRect.h"

namespace ShadowPlay
{
	struct SPObjRelays
	{
		SPLogger& m_logger;
	};

    struct SPAppBaseRelays
    {
        SPObjRelays m_baseObjRelay;
    };

    struct SPRHIBaseRelays
    {
        SPObjRelays m_baseObjRelay;
    };

    struct SPOpenGLBaseRelays
    {
        SPRHIBaseRelays m_baseRHIRelay;
    };

    struct SPVulkanBaseRelays
    {
        SPRHIBaseRelays m_baseRHIRelay;
    };

    struct SPDirectXBaseRelays
    {
        SPRHIBaseRelays m_baseRHIRelay;
    };

    struct SPMemManagerBaseRelays
    {
        SPObjRelays m_baseObjRelay;
    };

	struct SPSwapChainBaseRelays
	{
#ifdef SHADOWPLAY_PLAT_WIN
        void* m_windowHandle{};
#endif // SHADOWPLAY_PLAT_WIN
		SPRect m_viewPortRect{};
	};

}