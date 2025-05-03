#include "ShadowPreCompileHeader.h"
#include "SPD3DRHI.h"
#include "SPD3DRHIUtils.h"

#ifdef SHADOWPLAY_PLAT_WIN
#include <d3d11.h>
#include <d3d11shader.h>
#include <wrl.h>

static LRESULT CALLBACK WindowProcCallback(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam) 
{
    switch (msg)
    {
    case WM_CLOSE:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hwnd, msg, wparam, lparam);
        break;
    }
    return 0;
}

#endif

namespace ShadowPlay
{
    struct SPD3DRHIPrivate
    {
#ifdef SHADOWPLAY_PLAT_WIN
        WNDCLASSEX* m_windowContext = nullptr;
        HANDLE m_windowPtr;

        Microsoft::WRL::ComPtr<ID3D11Device> m_d3dDevice;
        Microsoft::WRL::ComPtr<ID3D11DeviceContext> m_d3dDeviceCtx;
        Microsoft::WRL::ComPtr<IDXGIDevice> m_dxgiDevice;
		Microsoft::WRL::ComPtr<IDXGIFactory> m_dxgiFactory;
		Microsoft::WRL::ComPtr<IDXGIAdapter> m_dxgiAdapter;

#endif
        bool m_runningPermission = true;
        bool m_renderLoop = true;
    };

	SPD3DRHI::SPD3DRHI(const SPDirectXBaseRelays& relay)
		: SPRHI(relay.m_baseRHIRelay)
    {
        p_d3d = new SPD3DRHIPrivate();
    }
    SPD3DRHI::~SPD3DRHI()
    {
        delete p_d3d;
    }
    void SPD3DRHI::RHIInit(uint32_t width, uint32_t height, const char *windowTitle)
    {
		SHADOWPLAY_ASSERT(p_d3d != nullptr);

#ifdef SHADOWPLAY_PLAT_WIN
        // Win32 window initialize.
        p_d3d->m_windowContext = new WNDCLASSEX();
        p_d3d->m_windowContext->cbSize = sizeof(WNDCLASSEX);
        p_d3d->m_windowContext->lpszClassName = windowTitle;
        p_d3d->m_windowContext->lpfnWndProc = &WindowProcCallback;
        auto windowClassID = RegisterClassEx(p_d3d->m_windowContext);

        if (!windowClassID) 
        {
			LOG_ERROR("Create Win32 window failed.");
            p_d3d->m_runningPermission = false;
            return;
        }

        RECT windowRC{ 0, 0, width, height };
        AdjustWindowRect(&windowRC, WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU, false);

        p_d3d->m_windowPtr = CreateWindowEx(
            NULL, 
            MAKEINTATOM(windowClassID), 
            windowTitle,
            WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU, CW_USEDEFAULT, CW_USEDEFAULT,
            windowRC.right - windowRC.left, windowRC.bottom - windowRC.top,
            NULL, NULL, NULL, NULL);

        // DirectX 11 3D API initialize.
        D3D_FEATURE_LEVEL apiFeatureLevel;
        UINT createDeviceFlags = 0;

        D3D_FEATURE_LEVEL featureLevels[] = {
            /*D3D_FEATURE_LEVEL_12_2,
            D3D_FEATURE_LEVEL_12_1,
            D3D_FEATURE_LEVEL_12_0,*/
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

        ShowWindow(static_cast<HWND>(p_d3d->m_windowPtr), SW_SHOW);
#endif
    }
    void SPD3DRHI::RHILoop()
    {
		SHADOWPLAY_ASSERT(p_d3d != nullptr);

        if (!p_d3d->m_runningPermission) 
        {
            return;
        }
#ifdef SHADOWPLAY_PLAT_WIN
        MSG windowMsg;
        while (p_d3d->m_renderLoop) 
        {
            while (PeekMessage(&windowMsg, NULL, 0, 0, PM_REMOVE)) 
            {
                if (windowMsg.message == WM_QUIT) 
                {
                    p_d3d->m_renderLoop = false;
                    break;
                }
                TranslateMessage(&windowMsg);
                DispatchMessage(&windowMsg);
            }
            Sleep(1);
        }
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
        DestroyWindow(static_cast<HWND>(p_d3d->m_windowPtr));
#endif
    }
}