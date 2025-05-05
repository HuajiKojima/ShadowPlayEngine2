#pragma once
#include "../Tools/SPLogger.h"
#include "../../Engine/Math/SPRect.h"

#include <string>

namespace ShadowPlay
{
    class SPD3DRHI;

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

    struct SPDisplayBaseRelays
    {
        SPObjRelays m_baseObjRelay;
		SPRect m_windowRect{};
		std::string m_windowTitle{};
    };

    struct SPRendererBaseRelays
    {
        SPDisplayBaseRelays m_baseDisplayRelay;
    };

    struct SPWin32WindowBaseRelays
    {
        SPDisplayBaseRelays m_baseDisplayRelay;
		SPD3DRHI& m_rhiInst;
    };

	struct SPSwapChainBaseRelays
	{
#ifdef SHADOWPLAY_PLAT_WIN
        void* m_windowHandle{};
#endif // SHADOWPLAY_PLAT_WIN
		SPRect m_viewPortRect{};
	};

}