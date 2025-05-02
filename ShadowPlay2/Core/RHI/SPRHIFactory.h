#pragma once
#include <SPGlobal.h>

#include "SPRHI.h"

namespace ShadowPlay
{
    struct SPRHIFactoryPrivate;

    enum class GraphicsAPI
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

    class SHADOWPLAY_API SPRHIFactory
    {
    public:
        SPRHIFactory();
        ~SPRHIFactory();

        static SPRHIFactory* GetRHIFactoryInstance(GraphicsAPI apiclass, const SPRHIBaseRelays& relay);

        void FactoryInitalize(GraphicsAPI apiclass, const SPRHIBaseRelays& relay);

        SPRHI* AllocateRHI();
    private:

        SPRHIFactoryPrivate* p = nullptr;
    };
}