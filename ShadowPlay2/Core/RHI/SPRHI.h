#pragma once
#include <SPGlobal.h>
#include "../Common/SPObject.h"

namespace ShadowPlay
{
    struct SPRHIPrivate;

	class SHADOWPLAY_API SPRHI : public SPObject
    {
    public:

        explicit SPRHI(const SPRHIBaseRelays& relays);
        ~SPRHI();

        virtual void RHIInit(uint32_t width, uint32_t height, const char* windowTitle) {}
        virtual void RHILoop() {}
        virtual void RHITerminate() {}

    protected:
        void setPrivate(uint32_t width, uint32_t height, const char* windowTitle);
        int GetWidth();
        int GetHeight();
        const char* GetWindowTitle();

    private:
        SPRHIPrivate* p = nullptr;
    };
}