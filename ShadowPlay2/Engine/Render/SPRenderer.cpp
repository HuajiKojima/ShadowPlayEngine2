#include "ShadowPreCompileHeader.h"
#include "SPRenderer.h"

#include "../../Core/RHI/SPRHIFactory.h"
#include "../../Core/RHI/DirectX/SPD3DRHI.h"
#include "../../Core/RHI/DirectX/SPD3DSwapChain.h"
#include "../../Core/Presentation/SPDisplay.h"
#include "../../Core/Presentation/Win32/SPWin32Window.h"


namespace ShadowPlay
{
	struct SPRendererPrivate
	{
		std::unique_ptr<SPRHI> m_rhiInst = nullptr;
		std::unique_ptr<SPDisplay> m_displayInst = nullptr;
		std::unique_ptr<SPRHIFactory> m_factoryInst = nullptr;

		SPRect m_windowRect = { 0, 0, 1280, 720 };
		std::string m_windowTitle = "ShadowPlay";

		bool m_runningPermission = true;
	};

	void PrivateDelete(SPRendererPrivate* pri)
	{
		if (pri)
		{
			delete pri;
			pri = nullptr;
		}
	}

	SPRenderer::SPRenderer(const SPRendererBaseRelays& relay) :
		SPObject(relay.m_baseDisplayRelay.m_baseObjRelay),
		m_pri(new SPRendererPrivate(), PrivateDelete)
	{
		m_pri->m_windowRect = relay.m_baseDisplayRelay.m_windowRect;
		m_pri->m_windowTitle = relay.m_baseDisplayRelay.m_windowTitle;
	}
	SPRenderer::~SPRenderer() {}
	void SPRenderer::Init(RenderingAPI api)
	{

		switch (api)
		{
		case ShadowPlay::RenderingAPI::API_NULL:
			break;
		case ShadowPlay::RenderingAPI::API_VULKAN:
			break;
		case ShadowPlay::RenderingAPI::API_DIRECTX:
		{
			m_pri->m_factoryInst = std::unique_ptr<SPRHIFactory>(SPRHIFactory::GetRHIFactoryInstance(GraphicsAPI::API_DIRECTX, { GetLogger() }));
			m_pri->m_rhiInst = std::unique_ptr<SPRHI>(m_pri->m_factoryInst->AllocateRHI());
			m_pri->m_rhiInst->RHIInit(m_pri->m_windowRect.width, m_pri->m_windowRect.height, "ShadowPlay");
			SPWin32WindowBaseRelays windowRelays
			{
				{ GetLogger(), m_pri->m_windowRect, "ShadowPlay" },
				//*reinterpret_cast<SPD3DRHI*>(m_pri->m_rhiInst)
				*reinterpret_cast<SPD3DRHI*>(m_pri->m_rhiInst.get())
			};
			m_pri->m_displayInst = std::make_unique<SPWin32Window>(windowRelays);
			LOG_INFO("SPRenderer::Init");
		}
			break;
		case ShadowPlay::RenderingAPI::API_OPENGL:
			break;
		default:
			break;
		}
	}
	void SPRenderer::Render()
	{
		if (!m_pri->m_runningPermission)
		{
			return;
		}
		LOG_INFO("SPRenderer::Render");
		m_pri->m_rhiInst->RHILoop();
		m_pri->m_displayInst->DisplayRunning();
	}
	void SPRenderer::Terminate()
	{
		if (!m_pri->m_runningPermission)
		{
			return;
		}
		m_pri->m_displayInst->Terminate();
		m_pri->m_rhiInst->RHITerminate();
		LOG_INFO("SPRenderer::Terminate");
	}
}