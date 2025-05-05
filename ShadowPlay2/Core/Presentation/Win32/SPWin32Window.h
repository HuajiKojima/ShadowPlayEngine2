#pragma once
#include "../SPDisplay.h"
#include "../../../Engine/Math/SPRect.h"

namespace ShadowPlay 
{
	struct SPWin32WindowPrivate;

	class SPWin32Window : public SPDisplay
	{
	public:
		explicit SPWin32Window(const SPWin32WindowBaseRelays& relay);
		~SPWin32Window();
		void Init() override;
		void Terminate() override;
		void LoopFunc(bool& loopPermission) override;

	protected:
		SPRect m_windowRect;
		std::string m_windowTitle;
		void* m_handle;

	private:
		std::unique_ptr<SPWin32WindowPrivate, void(*)(SPWin32WindowPrivate*)> m_pri;
	};
}