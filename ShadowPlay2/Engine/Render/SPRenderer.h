#pragma once

#include "../../Core/Common/SPObject.h"
#include <memory>

namespace ShadowPlay
{
	struct SPRendererPrivate;

	enum class RenderingAPI
	{
		API_NULL = 0,
#ifdef SHADOWPLAY_API_VK
		API_VULKAN,
#endif
#ifdef SHADOWPLAY_API_DIRECTX
		API_DIRECTX,
#endif
		API_OPENGL
	};

	class SPRenderer : public SPObject
	{
	public:
		explicit SPRenderer(const SPObjRelays& relay);
		~SPRenderer() {}
		void Init(RenderingAPI api);
		void Render();
		void Terminate();

	private:
		SPRendererPrivate* m_pri = nullptr;
	};
}