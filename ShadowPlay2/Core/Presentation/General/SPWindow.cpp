#include "ShadowPreCompileHeader.h"
#include "SPWindow.h"

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

namespace ShadowPlay 
{
	struct SPWindowPrivate 
	{
		// Private data members for SPWindow
		std::function<void()> m_rhiCallback;
	};

	void PrivateDelete(SPWindowPrivate* pri) 
	{
		if (pri) 
		{
			delete pri;
			pri = nullptr;
		}
	}

	SPWindow::SPWindow(const SPGeneralWindowBaseRelays& relay):
		m_pri(new SPWindowPrivate, PrivateDelete),
		SPDisplay(relay.m_baseDisplayRelay)
	{
		// Constructor implementation
		m_windowRect = relay.m_baseDisplayRelay.m_windowRect;
		m_windowTitle = relay.m_baseDisplayRelay.m_windowTitle;
	}
	SPWindow::~SPWindow() 
	{
		// Destructor implementation
	}
	void SPWindow::Init() 
	{
		// Initialization code
		glfwInit();
		glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
		glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
		m_handle = glfwCreateWindow(static_cast<int>(m_windowRect.width), static_cast<int>(m_windowRect.height), m_windowTitle.c_str(), nullptr, nullptr);
	}
    void SPWindow::Terminate()
    {
		glfwDestroyWindow(reinterpret_cast<GLFWwindow*>(m_handle));
		glfwTerminate();
    }
    void SPWindow::LoopFunc(bool &loopPermission)
    {
		glfwPollEvents();

		m_pri->m_rhiCallback();

		// TODO: Because RHI is running in another thread in th future, loopPermission should be attentioned the async problem. 
		// Maybe use atomic<bool> is better.
		loopPermission = !glfwWindowShouldClose(reinterpret_cast<GLFWwindow*>(m_handle));
    }
	void SPWindow::SetRHICallback(const std::function<void()>& callback)
	{
		SHADOWPLAY_ASSERT(m_pri != nullptr);
		m_pri->m_rhiCallback = callback;
	}
}