#include "ShadowPreCompileHeader.h"
#include "SPOpenGLRHI.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace ShadowPlay 
{
	struct SPOpenGLRHIPrivate 
	{
		// The large param is up, smaller is down.
		GLFWwindow* m_window = nullptr;				// 8 Bytes

		bool glInitialzed = true;					// 1 Byte
	};

	// Support change viewport.
	void framebuffer_size_callback(GLFWwindow* window, int width, int height)
	{
		glViewport(0, 0, width, height);
	}

	SPOpenGLRHI::SPOpenGLRHI()
	{
		p_gl = new SPOpenGLRHIPrivate();
	}
	SPOpenGLRHI::~SPOpenGLRHI()
	{
		SHADOWPLAY_ASSERT(p_gl != nullptr);
		delete p_gl;
	}
	void SPOpenGLRHI::RHIInit(uint32_t width, uint32_t height, const char* windowTitle)
	{
		// Window property initialize.
		setPrivate(width, height, windowTitle);
		// glfw initialize.
		// -----------------------------------------------------------------------------
		glfwInit();
		p_gl->m_window = glfwCreateWindow(width, height, windowTitle, NULL, NULL);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		if (p_gl->m_window == nullptr) 
		{
			// TODO: Output the error message.
			p_gl->glInitialzed = false;
			return;
		}

		glfwMakeContextCurrent(p_gl->m_window);
		// -----------------------------------------------------------------------------

		// glad Initialize.
		// -----------------------------------------------------------------------------
		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		{
			// TODO: Output the error message.
			p_gl->glInitialzed = false;
			return;
		}
		// -----------------------------------------------------------------------------

		glfwSetFramebufferSizeCallback(p_gl->m_window, framebuffer_size_callback);
	}
	void SPOpenGLRHI::RHILoop()
	{
		if (!(p_gl->glInitialzed)) 
		{
			return;
		}

		while (!glfwWindowShouldClose(p_gl->m_window))
		{
			glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);

			glfwSwapBuffers(p_gl->m_window);
			glfwPollEvents();
		}
	}
	void SPOpenGLRHI::RHITerminate()
	{
		if (!(p_gl->glInitialzed))
		{
			return;
		}
		glfwTerminate();
	}
}