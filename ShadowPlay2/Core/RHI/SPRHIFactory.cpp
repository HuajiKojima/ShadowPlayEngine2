#include "ShadowPreCompileHeader.h"
#include "SPRHIFactory.h"

#ifdef SHADOWPLAY_API_VK
#include "SPVulkanRHI.h"
#endif

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
    SPRHIFactory *SPRHIFactory::GetRHIFactoryInstance(GraphicsAPI apiClass)
    {
        static SPRHIFactory* factoryInstance = new SPRHIFactory();
        factoryInstance->FactoryInitalize(apiClass);
        return factoryInstance;
    }
    SPRHI *SPRHIFactory::AllocateRHI()
    {
        SHADOWPLAY_ASSERT(p != nullptr);
        return p->m_rhi;
    }
    void SPRHIFactory::FactoryInitalize(GraphicsAPI apiClass)
    {
        SHADOWPLAY_ASSERT(p != nullptr);
        switch (apiClass)
        {
        case GraphicsAPI::API_NULL:
            p->m_rhi = nullptr;
            break;
        #ifdef SHADOWPLAY_API_VK
        case GraphicsAPI::API_VULKAN:
            p->m_rhi = new SPVulkanRHI();
            break;
        #endif
        #ifdef SHADOWPLAY_API_DIRECTX
        case GraphicsAPI::API_DIRECTX:
            p->m_rhi = nullptr;
            break;
        #endif
        case GraphicsAPI::API_OPENGL:
            p->m_rhi = nullptr;
            break;
        default:
            p->m_rhi = nullptr;
            break;
        }
    }
}