#include "ShadowPreCompileHeader.h"
#include "SPAppBase.h"

#include "Core/RHI/SPRHIFactory.h"
#include "Core/Memory/SPMemManager.h"

namespace ShadowPlay
{

    struct SPAppBasePrivate
    {
        SPRHI* m_rhiInstance = nullptr;
        SPRHIFactory* m_factoryInstance = nullptr;
        SPHeapMemAllocator* m_memAllocator = SPHeapMemAllocatorFactory::GetAllocator();
    };

    SPAppBase::SPAppBase()
    {
        p = new SPAppBasePrivate();
        p->m_factoryInstance = SPRHIFactory::GetRHIFactoryInstance(GraphicsAPI::API_OPENGL);
        p->m_rhiInstance = p->m_factoryInstance->AllocateRHI();
        std::cout << 1 << std::endl;
    }
    SPAppBase::~SPAppBase()
    {
        std::cout << 3 << std::endl;
    }
    void SPAppBase::AppInit()
    {
        SHADOWPLAY_ASSERT(p != nullptr);
        p->m_rhiInstance->RHIInit(1280, 720, "ShadowPlay");
        AppInitCallback();
    }
    void SPAppBase::AppRun()
    {
        SHADOWPLAY_ASSERT(p != nullptr);
        AppRunCallback();
        p->m_rhiInstance->RHILoop();
    }
    void SPAppBase::AppTerminate()
    {
        SHADOWPLAY_ASSERT(p != nullptr);
        AppTerminateCallback();
        p->m_rhiInstance->RHITerminate();
        p->m_memAllocator->AllocatorTerminator();
    }
}