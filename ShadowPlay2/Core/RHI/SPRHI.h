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

        virtual void RHIInit(int width, int height, const char* windowTitle) = 0;
        virtual void RHILoop() = 0;
        virtual void RHITerminate() = 0;

    protected:
        void setPrivate(int width, int height, const char* windowTitle);
        int GetWidth();
        int GetHeight();
        const char* GetWindowTItle();

    private:
        SPRHIPrivate* p = nullptr;
    };
}