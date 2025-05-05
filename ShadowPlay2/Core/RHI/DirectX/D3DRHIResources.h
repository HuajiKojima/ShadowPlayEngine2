#pragma once
#include <SPGlobal.h>
#include "../../Common/SPObject.h"

#ifdef SHADOWPLAY_PLAT_WIN
#include <d3d11.h>
#endif // SHADOWPLAY_PLAT_WIN

namespace ShadowPlay 
{
	class SPD3DRHI;

	struct SPD3DRHIResourcesRelays
	{
		SPObjRelays m_baseObjRelay;
		SPD3DRHI& m_rhiInst;
#ifdef SHADOWPLAY_PLAT_WIN
		ID3D11Device& m_device;
		IDXGIFactory& m_factory;
#endif // SHADOWPLAY_PLAT_WIN
	};

	// This class is used to manage the DirectX 3D resources.
	class SPD3DRHIResources : public SPObject
	{
	public:
		explicit SPD3DRHIResources(const SPD3DRHIResourcesRelays& relay) :
			SPObject(relay.m_baseObjRelay),
#ifdef SHADOWPLAY_PLAT_WIN
			m_renderingDevice(relay.m_device),
			m_dxgiFactory(relay.m_factory)
#endif // SHADOWPLAY_PLAT_WIN
		{
		}
	
	protected:
		std::shared_ptr<const SPD3DRHI> m_engineRHIInst;
#ifdef SHADOWPLAY_PLAT_WIN
		ID3D11Device& m_renderingDevice;
		IDXGIFactory& m_dxgiFactory;
#endif // SHADOWPLAY_PLAT_WIN

	};
}