#pragma once
#include "../SPRHI.h"
#include "D3DRHIResources.h"
#include <SPGlobal.h>

#include <memory>

namespace ShadowPlay
{
    struct SPD3DRHIPrivate;
    class SPD3DSwapChain;

	class SHADOWPLAY_API SPD3DRHI final : public SPRHI, public std::enable_shared_from_this<SPD3DRHI>
    {
    public:
        explicit SPD3DRHI(const SPDirectXBaseRelays& relay);
        ~SPD3DRHI();

        virtual void RHIInit(uint32_t width, uint32_t height, const char* windowTitle);
		virtual void RHILoop();
		virtual void RHITerminate();

        std::shared_ptr<SPD3DSwapChain> CreateSwapChain(const SPSwapChainBaseRelays& relay) const;

    private:
        SPD3DRHIResourcesRelays GetRHIResourcesRelay() const;

	private:
        SPD3DRHIPrivate* p_d3d;
    };
}