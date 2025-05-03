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
        : SPObject({ *std::make_unique<SPLogger>(SPLogger::LoggerLevel::LOG_INFO).release() }),
        m_logInstance(&m_objLogger)
    {
        p = new SPAppBasePrivate();

		// Initialize the relay
		SPObjRelays relays
		{
			m_objLogger
		};
		// Initialize the RHI relay
		SPRHIBaseRelays rhiRelays
		{
			relays
		};

        p->m_factoryInstance = SPRHIFactory::GetRHIFactoryInstance(GraphicsAPI::API_OPENGL, rhiRelays);
        p->m_rhiInstance = p->m_factoryInstance->AllocateRHI();		
        GetLogger().Log(SPLogger::LoggerLevel::LOG_INFO, "SPAppBase::SPAppBase");
    }
    SPAppBase::~SPAppBase()
    {
		GetLogger().Log(SPLogger::LoggerLevel::LOG_INFO, "SPAppBase::~SPAppBase");
        p->m_memAllocator->AllocatorTerminator();
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
    }
}