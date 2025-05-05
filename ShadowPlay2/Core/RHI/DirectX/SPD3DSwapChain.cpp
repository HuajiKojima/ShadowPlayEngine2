#include "ShadowPreCompileHeader.h"
#include "SPD3DSwapChain.h"
namespace ShadowPlay
{
	SPD3DSwapChain::SPD3DSwapChain(const SPSwapChainBaseRelays& sRelay, const SPD3DRHIResourcesRelays& rRelay) : SPD3DRHIResources(rRelay)
	{
#ifdef SHADOWPLAY_PLAT_WIN
		DXGI_SWAP_CHAIN_DESC swapChainDesc = {};
		swapChainDesc.BufferCount = 2;
		swapChainDesc.BufferDesc.Width = std::max(1, sRelay.m_viewPortRect.width);
		swapChainDesc.BufferDesc.Height = std::max(1, sRelay.m_viewPortRect.height);
		swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		
		swapChainDesc.OutputWindow = static_cast<HWND>(sRelay.m_windowHandle);
		swapChainDesc.SampleDesc.Count = 1;
		swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
		swapChainDesc.Windowed = TRUE;

		auto result = m_dxgiFactory.CreateSwapChain(&m_renderingDevice, &swapChainDesc, &m_swapChainInst);
		if (FAILED(result)) 
		{
			std::string errorMessage = "Failed to create swap chain: " + std::to_string(result);
			LOG_ERROR(errorMessage.c_str());
			m_runningPermission = false;
		}
#endif // SHADOWPLAY_PLAT_WIN
	}
}