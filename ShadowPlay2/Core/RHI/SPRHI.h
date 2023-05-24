#pragma once
#include <SPGlobal.h>

namespace ShadowPlay
{
    struct SPRHIPrivate;

    class SHADOWPLAY_API SPRHI
    {
    public:

        SPRHI();
        ~SPRHI();

        virtual void RHIInit(uint32_t width, uint32_t height, const char* windowTitle) = 0;
        virtual void RHILoop() = 0;
        virtual void RHITerminate() = 0;

    protected:
        void setPrivate(uint32_t width, uint32_t height, const char* windowTitle);
        int GetWidth();
        int GetHeight();
        const char* GetWindowTItle();

    private:
        SPRHIPrivate* p = nullptr;
    };
}