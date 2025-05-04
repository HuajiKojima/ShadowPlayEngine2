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
		SPRHI* m_rhiInst = nullptr;
		SPDisplay* m_displayInst = nullptr;
		SPRHIFactory* m_factoryInst = nullptr;
		bool m_runningPermission = true;
	};

	SPRenderer::SPRenderer(const SPObjRelays& relay) : SPObject(relay) 
	{
		m_pri = new SPRendererPrivate();
	}
	void SPRenderer::Init(RenderingAPI api)
	{
		m_pri->m_factoryInst = SPRHIFactory::GetRHIFactoryInstance(GraphicsAPI::API_DIRECTX, { GetLogger() });

		switch (api)
		{
		case ShadowPlay::RenderingAPI::API_NULL:
			break;
		case ShadowPlay::RenderingAPI::API_VULKAN:
			break;
		case ShadowPlay::RenderingAPI::API_DIRECTX:
		{
			m_pri->m_rhiInst = m_pri->m_factoryInst->AllocateRHI();
			m_pri->m_rhiInst->RHIInit(1280, 720, "ShadowPlay");
			SPWin32WindowBaseRelays windowRelays
			{
				{ GetLogger(), SPRect{0, 0, 1280, 720}, "ShadowPlay" },
				*reinterpret_cast<SPD3DRHI*>(m_pri->m_rhiInst)
			};
			m_pri->m_displayInst = new SPWin32Window(windowRelays);
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
		m_pri->m_rhiInst->RHILoop();
		m_pri->m_displayInst->DisplayRunning();
		LOG_INFO("SPRenderer::Render");
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