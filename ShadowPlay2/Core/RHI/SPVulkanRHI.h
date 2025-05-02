#pragma once
#include "SPRHI.h"
#include <SPGlobal.h>
 namespace ShadowPlay
 {
    struct SPVulkanRHIPrivate;

    class SHADOWPLAY_API SPVulkanRHI final : public SPRHI
    {
    public:
        explicit SPVulkanRHI(const SPVulkanBaseRelays& relay);
        ~SPVulkanRHI();

        virtual void RHIInit(uint32_t width, uint32_t height, const char* windowTitle);
        virtual void RHILoop();
        virtual void RHITerminate();
    private:
        void CreateVulkanInstance();

        SPVulkanRHIPrivate* p_vk = nullptr;

    };
 }