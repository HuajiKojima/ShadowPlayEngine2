#include "ShadowPreCompileHeader.h"
#include "SPDisplay.h"

namespace ShadowPlay
{
	void SPDisplay::DisplayRunning()
	{
		while (m_loopPermission)
		{
			LoopFunc(m_loopPermission);
		}
	}
}