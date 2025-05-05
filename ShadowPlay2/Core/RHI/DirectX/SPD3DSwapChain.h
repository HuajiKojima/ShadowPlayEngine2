#pragma once
#include "D3DRHIResources.h"


namespace ShadowPlay 
{
	class SPD3DSwapChain final : public SPD3DRHIResources
	{
	public:
		explicit SPD3DSwapChain(const SPSwapChainBaseRelays& sRelay, const SPD3DRHIResourcesRelays& rRelay);
	private:
#ifdef SHADOWPLAY_PLAT_WIN
		Microsoft::WRL::ComPtr<IDXGISwapChain> m_swapChainInst;
#endif
		bool m_runningPermission = true;
	};
}