#include "SPWin32Window.h"

#include "../../RHI/DirectX/SPD3DSwapChain.h"
#include "../../RHI/DirectX/SPD3DRHI.h"

#ifdef SHADOWPLAY_PLAT_WIN
#include <windows.h>

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
	struct SPWin32WindowPrivate 
	{
#ifdef SHADOWPLAY_PLAT_WIN
		WNDCLASSEX* m_windowContext = nullptr;
		HWND m_windowPtr;
		MSG m_windowMsg;
#endif
		std::shared_ptr<SPD3DSwapChain> m_swapChainInst; 
		bool m_runningPermission = true;
	};

	SPWin32Window::SPWin32Window(const SPWin32WindowBaseRelays& relay) :
		SPDisplay(relay.m_baseDisplayRelay),
		m_windowRect(relay.m_baseDisplayRelay.m_windowRect),
		m_windowTitle(relay.m_baseDisplayRelay.m_windowTitle),
		m_pri(new SPWin32WindowPrivate())
	{
		Init();
		m_pri->m_swapChainInst = relay.m_rhiInst.CreateSwapChain({m_handle, m_windowRect});

	}

	void SPWin32Window::Init()
	{
		SHADOWPLAY_ASSERT(m_pri != nullptr);
#ifdef SHADOWPLAY_PLAT_WIN
		// Win32 window initialize.
		m_pri->m_windowContext = new WNDCLASSEX();
		m_pri->m_windowContext->cbSize = sizeof(WNDCLASSEX);
		m_pri->m_windowContext->lpszClassName = m_windowTitle.c_str();
		m_pri->m_windowContext->lpfnWndProc = &WindowProcCallback;
		auto windowClassID = RegisterClassEx(m_pri->m_windowContext);

		if (!windowClassID)
		{
			LOG_ERROR("Create Win32 window failed.");
			m_pri->m_runningPermission = false;
			return;
		}

		RECT windowRC{ 0, 0, m_windowRect.width, m_windowRect.height };
		AdjustWindowRect(&windowRC, WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU, false);

		m_handle = CreateWindowEx(
			NULL,
			MAKEINTATOM(windowClassID),
			m_windowTitle.c_str(),
			WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU, CW_USEDEFAULT, CW_USEDEFAULT,
			windowRC.right - windowRC.left, windowRC.bottom - windowRC.top,
			NULL, NULL, NULL, NULL);

		ShowWindow(static_cast<HWND>(m_handle), SW_SHOW);

#endif

	}

	void SPWin32Window::Terminate()
	{
		SHADOWPLAY_ASSERT(m_pri != nullptr);
#ifdef SHADOWPLAY_PLAT_WIN
		DestroyWindow(static_cast<HWND>(m_handle));
#endif // SHADOWPLAY_PLAT_WIN
	}

	void SPWin32Window::LoopFunc(bool& loopPermission)
	{
		SHADOWPLAY_ASSERT(m_pri != nullptr);
#ifdef SHADOWPLAY_PLAT_WIN
		while (PeekMessage(&m_pri->m_windowMsg, NULL, 0, 0, PM_REMOVE))
		{
			if (m_pri->m_windowMsg.message == WM_QUIT)
			{
				loopPermission = false;
				break;
			}
			TranslateMessage(&m_pri->m_windowMsg);
			DispatchMessage(&m_pri->m_windowMsg);
		}
		Sleep(1);
#endif // SHADOWPLAY_PLAT_WIN
	}
}
