#pragma once
#include "../SPRHI.h"
#include <SPGlobal.h>
 namespace ShadowPlay
 {
    struct SPVulkanRHIPrivate;

    class SHADOWPLAY_API SPVulkanRHI final : public SPRHI
    {
    public:
        explicit SPVulkanRHI(const SPVulkanBaseRelays& relay);
        ~SPVulkanRHI();

        virtual void RHIInit(uint32_t width, uint32_t height, const char* windowTitle) override;
        virtual void RHIRendering() override;
        virtual void RHITerminate() override;
    private:
        void CreateVulkanInstance();

        std::unique_ptr<SPVulkanRHIPrivate, void(*)(SPVulkanRHIPrivate*)> p_vk;

    };
 }