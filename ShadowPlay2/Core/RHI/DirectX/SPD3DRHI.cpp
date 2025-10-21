#include "ShadowPreCompileHeader.h"
#include "SPD3DRHI.h"
#include "SPD3DRHIUtils.h"
#include "SPD3DSwapChain.h"

#ifdef SHADOWPLAY_PLAT_WIN
#include <d3d11.h>
#include <d3d11shader.h>
#include <wrl.h>
#endif

namespace ShadowPlay
{
    struct SPD3DRHIPrivate
    {
#ifdef SHADOWPLAY_PLAT_WIN
		// Because all the D3D11 API are COM based, so we need to use the ComPtr to manage the memory.
        Microsoft::WRL::ComPtr<ID3D11Device> m_d3dDevice;
        Microsoft::WRL::ComPtr<ID3D11DeviceContext> m_d3dDeviceCtx;
        Microsoft::WRL::ComPtr<IDXGIDevice> m_dxgiDevice;
		Microsoft::WRL::ComPtr<IDXGIFactory> m_dxgiFactory;
		Microsoft::WRL::ComPtr<IDXGIAdapter> m_dxgiAdapter;
        
        std::shared_ptr<SPD3DSwapChain> m_swapChainInst;

#endif
        bool m_runningPermission = true;
        bool m_renderLoop = true;
    };

	void DeleteSPD3DRHIPrivate(SPD3DRHIPrivate* p)
	{
		if (p != nullptr)
		{
			delete p;
			p = nullptr;
		}
	}

	SPD3DRHI::SPD3DRHI(const SPDirectXBaseRelays& relay):
        SPRHI(relay.m_baseRHIRelay),
		p_d3d(new SPD3DRHIPrivate(), DeleteSPD3DRHIPrivate)
    {
        
    }
    SPD3DRHI::~SPD3DRHI()
    {
		// TODO: Make sure the RHI terminate after the swap chain destroyed.
    }
    void SPD3DRHI::RHIInit(uint32_t width, uint32_t height, const char *windowTitle)
    {
		SHADOWPLAY_ASSERT(p_d3d != nullptr);

#ifdef SHADOWPLAY_PLAT_WIN

        // DirectX 11 3D API initialize.
        D3D_FEATURE_LEVEL apiFeatureLevel;
        UINT createDeviceFlags = 0;

        D3D_FEATURE_LEVEL featureLevels[] = {
            D3D_FEATURE_LEVEL_11_1,
            D3D_FEATURE_LEVEL_11_0,
            D3D_FEATURE_LEVEL_10_1,
            D3D_FEATURE_LEVEL_10_0,
            D3D_FEATURE_LEVEL_9_3,
            D3D_FEATURE_LEVEL_9_2,
            D3D_FEATURE_LEVEL_9_1
        };
        UINT numFeatureLevels = ARRAYSIZE(featureLevels);

#ifdef SHADOWPLAY_DEBUG
        createDeviceFlags = D3D11_CREATE_DEVICE_DEBUG;
#endif // SHADOWPLAY_DEBUG

        // Initialize the D3D11 device.
        D3D_LOG_HRESULT(
            D3D11CreateDevice(
                NULL,
                D3D_DRIVER_TYPE_HARDWARE,
                NULL,
                createDeviceFlags,
                featureLevels,
                numFeatureLevels,
                D3D11_SDK_VERSION,
                &p_d3d->m_d3dDevice,
                &apiFeatureLevel,
                &p_d3d->m_d3dDeviceCtx), 
            "Create D3D device failed.");

		// Query the DXGI device.
		D3D_LOG_HRESULT(
			p_d3d->m_d3dDevice->QueryInterface(IID_PPV_ARGS(&(p_d3d->m_dxgiDevice))),
			"Create DXGI device failed.");

		// Get the DXGI adapter.
        D3D_LOG_HRESULT(
            p_d3d->m_dxgiDevice->GetParent(IID_PPV_ARGS(&(p_d3d->m_dxgiAdapter))),
            "Create DXGI adapter failed.");

		// Get the DXGI factory.
		D3D_LOG_HRESULT(
            p_d3d->m_dxgiAdapter->GetParent(IID_PPV_ARGS(&(p_d3d->m_dxgiFactory))),
            "Create DXGI adapter failed.");
#endif
    }
    void SPD3DRHI::RHIRendering()
    {
		SHADOWPLAY_ASSERT(p_d3d != nullptr);

        if (!p_d3d->m_runningPermission) 
        {
            return;
        }
#ifdef SHADOWPLAY_PLAT_WIN
        
#endif
    }
    void SPD3DRHI::RHITerminate()
    {
        SHADOWPLAY_ASSERT(p_d3d != nullptr);
        if (!p_d3d->m_runningPermission)
        {
            return;
        }
#ifdef SHADOWPLAY_PLAT_WIN

#endif
    }

    std::shared_ptr<SPD3DSwapChain> SPD3DRHI::CreateSwapChain(const SPSwapChainBaseRelays& relay) const
    {
		p_d3d->m_swapChainInst = std::make_shared<SPD3DSwapChain>(relay, GetRHIResourcesRelay());
		return p_d3d->m_swapChainInst;
    }

    SPD3DRHIResourcesRelays SPD3DRHI::GetRHIResourcesRelay() const
    {
        return { {m_objLogger}, const_cast<SPD3DRHI&>(*this), *(p_d3d->m_d3dDevice.Get()), *(p_d3d->m_dxgiFactory.Get())};
    }
}