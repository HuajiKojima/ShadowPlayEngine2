#pragma once

#include "../SPDisplay.h"
#include "../../../Engine/Math/SPRect.h"

namespace ShadowPlay
{
	struct SPWindowPrivate;
	class SPWindow : public SPDisplay
	{
	public:
		explicit SPWindow(const SPGeneralWindowBaseRelays& relay);
		~SPWindow() override;

		void Init() override;
		void Terminate() override;
		void LoopFunc(bool& loopPermission) override;

		void SetRHICallback(const std::function<void()>& callback) override;

	protected:
		SPRect m_windowRect;
		std::string m_windowTitle;
		void* m_handle;

	private:
		std::unique_ptr<SPWindowPrivate, void(*)(SPWindowPrivate*)> m_pri;
	};
}