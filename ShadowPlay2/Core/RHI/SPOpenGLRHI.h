#include "SPRHI.h"
#include <SPGlobal.h>
namespace ShadowPlay 
{
	struct SPOpenGLRHIPrivate;

	class SHADOWPLAY_API SPOpenGLRHI :public SPRHI
	{
	public:
		SPOpenGLRHI();
		~SPOpenGLRHI();

		virtual void RHIInit(uint32_t width, uint32_t height, const char* windowTitle);
		virtual void RHILoop();
		virtual void RHITerminate();


	private:
		SPOpenGLRHIPrivate* p_gl;
	};
}