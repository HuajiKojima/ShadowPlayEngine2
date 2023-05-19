#pragma once
#include "SPRHI.h"
#include <SPGlobal.h>
 namespace ShadowPlay
 {
    struct SPVulkanRHIPrivate;

    class SHADOWPLAY_API SPVulkanRHI: public SPRHI
    {
    public:
        SPVulkanRHI();
        ~SPVulkanRHI();

        virtual void RHIInit(int width, int height, const char* windowTitle);
        virtual void RHILoop();
        virtual void RHITerminate();
    private:
        void CreateVulkanInstance();

        SPVulkanRHIPrivate* p_vk = nullptr;

    };
 }