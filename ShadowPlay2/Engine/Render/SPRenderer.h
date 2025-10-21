#pragma once

#include "../../Core/Common/SPObject.h"

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
		explicit SPRenderer(const SPRendererBaseRelays& relay);
		~SPRenderer();
		void Init(uint32_t api);
		void Rendering();
		void Terminate();

	private:
		std::unique_ptr<SPRendererPrivate, void(*)(SPRendererPrivate*)> m_pri;
	};
}