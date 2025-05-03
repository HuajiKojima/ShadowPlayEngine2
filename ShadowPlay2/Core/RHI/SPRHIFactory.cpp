#include "ShadowPreCompileHeader.h"
#include "SPRHIFactory.h"

#ifdef SHADOWPLAY_API_VK
#include "SPVulkanRHI.h"
#endif

#ifdef SHADOWPLAY_API_DIRECTX
#include "SPD3DRHI.h"
#endif

#include "SPOpenGLRHI.h"

#include "../Common/SPCommon.h"

namespace ShadowPlay
{
    struct SPRHIFactoryPrivate
    {
        SPRHI* m_rhi;
    };

    SPRHIFactory::SPRHIFactory()
    {
        p = new SPRHIFactoryPrivate();
    }
    SPRHIFactory::~SPRHIFactory()
    {
        SHADOWPLAY_ASSERT(p != nullptr);
        delete p;
    }
    SPRHIFactory* SPRHIFactory::GetRHIFactoryInstance(GraphicsAPI apiclass, const SPRHIBaseRelays& relay)
    {
        static SPRHIFactory* factoryInstance = new SPRHIFactory();
        factoryInstance->FactoryInitalize(apiclass, relay);
        return factoryInstance;
    }
    SPRHI *SPRHIFactory::AllocateRHI()
    {
        SHADOWPLAY_ASSERT(p != nullptr);
        return p->m_rhi;
    }
    void SPRHIFactory::FactoryInitalize(GraphicsAPI apiClass, const SPRHIBaseRelays& relay)
    {
        SHADOWPLAY_ASSERT(p != nullptr);
        switch (apiClass)
        {
        case GraphicsAPI::API_NULL:
            p->m_rhi = nullptr;
            break;
        #ifdef SHADOWPLAY_API_VK
        case GraphicsAPI::API_VULKAN: 
        {
            SPVulkanBaseRelays vkRelays
            {
                relay
            };
            p->m_rhi = new SPVulkanRHI(vkRelays);
        }
            break;
        #endif
        #ifdef SHADOWPLAY_API_DIRECTX
        case GraphicsAPI::API_DIRECTX:
        {
            SPDirectXBaseRelays dxRelays
            {
				relay
            };
            p->m_rhi = new SPD3DRHI(dxRelays);
        }
            break;
        #endif
        case GraphicsAPI::API_OPENGL:
        {
            SPOpenGLBaseRelays glRelays
            {
                relay
            };
            p->m_rhi = new SPOpenGLRHI(glRelays);
        }
            break;
        default:
            p->m_rhi = nullptr;
            break;
        }
    }
}