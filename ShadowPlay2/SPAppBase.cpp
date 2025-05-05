#include "ShadowPreCompileHeader.h"
#include "SPAppBase.h"

#include "Core/RHI/SPRHIFactory.h"
#include "Core/Memory/SPMemManager.h"

#include "Engine/Render/SPRenderer.h"

namespace ShadowPlay
{

    struct SPAppBasePrivate
    {
        SPRHI* m_rhiInstance = nullptr;
        SPRHIFactory* m_factoryInstance = nullptr;
        SPHeapMemAllocator* m_memAllocator = SPHeapMemAllocatorFactory::GetAllocator();
        std::unique_ptr<SPRenderer> m_rendererInstance{};
    };

	void DeleteSPAppBasePrivate(SPAppBasePrivate* p)
	{
		if (p != nullptr)
		{
            delete p;
			p = nullptr;
		}
	}

	SPAppBase::SPAppBase()
        : SPObject({ *std::make_unique<SPLogger>(SPLogger::LoggerLevel::LOG_INFO).release() }),
        m_logInstance(&m_objLogger),
		p(new SPAppBasePrivate(), DeleteSPAppBasePrivate)
    {

		// Initialize the relay
        SPDisplayBaseRelays relays
		{
			m_objLogger, SPRect{ 0, 0, 1280, 720 }, "ShadowPlay"
		};
		// Initialize the renderer
		SPRendererBaseRelays rendererRelays
		{
			relays
		};

        p->m_rendererInstance = std::make_unique<SPRenderer>(rendererRelays);

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
		p->m_rendererInstance->Init(RenderingAPI::API_DIRECTX);
        AppInitCallback();
    }
    void SPAppBase::AppRun()
    {
        SHADOWPLAY_ASSERT(p != nullptr);
        AppRunCallback();
		p->m_rendererInstance->Render();
    }
    void SPAppBase::AppTerminate()
    {
        SHADOWPLAY_ASSERT(p != nullptr);
        AppTerminateCallback();
		p->m_rendererInstance->Terminate();
    }
}