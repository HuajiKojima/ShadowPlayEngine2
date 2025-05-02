#pragma once
#include "SPRHI.h"
#include <SPGlobal.h>

namespace ShadowPlay
{
    struct SPD3DRHIPrivate;

	class SHADOWPLAY_API SPD3DRHI final : public SPRHI
    {
    public:
        explicit SPD3DRHI(const SPDirectXBaseRelays& relay);
        ~SPD3DRHI();

        virtual void RHIInit(uint32_t width, uint32_t height, const char* windowTitle);
		virtual void RHILoop();
		virtual void RHITerminate();


	private:
        SPD3DRHIPrivate* p_d3d;
    };
}