#include "ShadowPreCompileHeader.h"
#include "SPRHIFactory.h"

#ifdef SHADOWPLAY_API_VK
#include "Vulkan/SPVulkanRHI.h"
#endif

#ifdef SHADOWPLAY_API_DIRECTX
#include "DirectX/SPD3DRHI.h"
#endif

#include "OpenGL/SPOpenGLRHI.h"

#include "../Common/SPCommon.h"

namespace ShadowPlay
{
    struct SPRHIFactoryPrivate
    {
        SPRHI* m_rhi;
    };

	void DeleteSPRHIFactoryPrivate(SPRHIFactoryPrivate* p)
	{
		if (p != nullptr)
		{
			delete p;
			p = nullptr;
		}
	}

    SPRHIFactory::SPRHIFactory():
		p(new SPRHIFactoryPrivate(), DeleteSPRHIFactoryPrivate)
	{
		
    }
    SPRHIFactory::~SPRHIFactory()
    {
        
    }
    SPRHIFactory* SPRHIFactory::GetRHIFactoryInstance(uint32_t apiclass, const SPRHIBaseRelays& relay)
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
    void SPRHIFactory::FactoryInitalize(uint32_t apiClass, const SPRHIBaseRelays& relay)
    {
        SHADOWPLAY_ASSERT(p != nullptr);
        switch (apiClass)
        {
        case GRAPHICS_API_NULL:
            p->m_rhi = nullptr;
            break;
        #ifdef SHADOWPLAY_API_VK
        case GRAPHICS_API_VK: 
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
        case GRAPHICS_API_DIRECTX:
        {
            SPDirectXBaseRelays dxRelays
            {
				relay
            };
            p->m_rhi = new SPD3DRHI(dxRelays);
        }
            break;
        #endif
        default:
            p->m_rhi = nullptr;
            break;
        }
    }
}