#pragma once
#include <SPGlobal.h>

#include "SPVulkanRHI.h"

namespace ShadowPlay
{
    struct SPRHIFactoryPrivate;

    enum class GraphicsAPI
    {
        API_NULL = 0,
        API_VULKAN,
        API_OPENGL,
        API_DIRECTX
    };

    class SHADOWPLAY_API SPRHIFactory
    {
    public:
        SPRHIFactory();
        ~SPRHIFactory();

        static SPRHIFactory* GetRHIFactoryInstance(GraphicsAPI apiclass);

        void FactoryInitalize(GraphicsAPI apiclass);

        SPRHI* AllocateRHI();
    private:

        SPRHIFactoryPrivate* p = nullptr;
    };
}