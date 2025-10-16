#pragma once
#include <SPGlobal.h>
#include "SPProcessEnt.h"

namespace ShadowPlay
{
	class SHADOWPLAY_API SPProcessPoolThread : public SPProcessEnt
	{
		virtual bool Init() override;

        virtual int32_t Run() override;

        virtual void Stop() override;

        virtual void Terminate() override;
	};
}