#pragma once
#include "../SPRHI.h"
#include <SPGlobal.h>
namespace ShadowPlay 
{
	struct SPOpenGLRHIPrivate;

	class SHADOWPLAY_API SPOpenGLRHI final : public SPRHI
	{
	public:
		explicit SPOpenGLRHI(const SPOpenGLBaseRelays& relay);
		~SPOpenGLRHI();

		virtual void RHIInit(uint32_t width, uint32_t height, const char* windowTitle);
		virtual void RHILoop();
		virtual void RHITerminate();


	private:
		std::unique_ptr<SPOpenGLRHIPrivate, void(*)(SPOpenGLRHIPrivate*)> p_gl;
	};
}