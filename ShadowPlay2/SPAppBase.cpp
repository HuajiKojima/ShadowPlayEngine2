#include "ShadowPreCompileHeader.h"
#include "SPAppBase.h"

#include "Core/RHI/SPRHIFactory.h"
#include "Core/Memory/SPMemManager.h"

#include "Engine/Render/SPRenderer.h"

#include <memory>

namespace ShadowPlay
{

    struct SPAppBasePrivate
    {
        SPRHI* m_rhiInstance = nullptr;
        SPRHIFactory* m_factoryInstance = nullptr;
        SPHeapMemAllocator* m_memAllocator = SPHeapMemAllocatorFactory::GetAllocator();
        std::unique_ptr<SPRenderer> m_rendererInstance{};
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

        //p->m_factoryInstance = SPRHIFactory::GetRHIFactoryInstance(GraphicsAPI::API_DIRECTX, rhiRelays);
        //p->m_rhiInstance = p->m_factoryInstance->AllocateRHI();

		p->m_rendererInstance = std::make_unique<SPRenderer>(relays);

        LOG_INFO("SPAppBase::SPAppBase");
    }
    SPAppBase::~SPAppBase()
    {
        LOG_INFO("SPAppBase::~SPAppBase");
        p->m_memAllocator->AllocatorTerminator();
    }
    void SPAppBase::AppInit()
    {
        SHADOWPLAY_ASSERT(p != nullptr);
        //p->m_rhiInstance->RHIInit(1280, 720, "ShadowPlay");
		p->m_rendererInstance->Init(RenderingAPI::API_DIRECTX);
        AppInitCallback();
    }
    void SPAppBase::AppRun()
    {
        SHADOWPLAY_ASSERT(p != nullptr);
        AppRunCallback();
        //p->m_rhiInstance->RHILoop();
		p->m_rendererInstance->Render();
    }
    void SPAppBase::AppTerminate()
    {
        SHADOWPLAY_ASSERT(p != nullptr);
        AppTerminateCallback();
        //p->m_rhiInstance->RHITerminate();
		p->m_rendererInstance->Terminate();
    }
}