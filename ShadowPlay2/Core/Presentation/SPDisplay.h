#pragma once
#include <SPGlobal.h>
#include "../Common/SPObject.h"

namespace ShadowPlay
{
	class SHADOWPLAY_API SPDisplay : public SPObject
	{
	public:
		explicit SPDisplay(const SPDisplayBaseRelays& base) : SPObject(base.m_baseObjRelay) {}
		virtual ~SPDisplay() {}
		// Warning: This function is only called once when the display is created.
		virtual void Init() {}
		void DisplayRunning();
		virtual void LoopFunc(bool& loopPermission) {}
		virtual void Terminate() {}

	private:
		bool m_loopPermission = true;
	};
}