#pragma once

#include <SPGlobal.h>
#include "AsyncUtils.h"

namespace ShadowPlay
{
	// Abstract base class for process entities.
	class SHADOWPLAY_API SPProcessEnt
	{
	public:
		SPProcessEnt() = default;
		virtual ~SPProcessEnt(){};

		virtual bool Init()
		{
			return true;
		}

		virtual int32_t Run() = 0;
		virtual void Stop() { /* TODO: When using the OS - specific thread API, implement the logic here */ }
		virtual void Terminate(){ /* TODO: When using the OS - specific thread API, implement the logic here */ }
	};

	struct SPProcessEntThreadPrivate;

	class SHADOWPLAY_API SPProcessEntThread final
	{
	public:

		std::thread* thread = nullptr;

		static SPProcessEntThread* Create
		(
			SPProcessEnt* processEntInst,
			const char* threadName = nullptr,
			ASyncUtils::ThreadPriotiry threadPriotiry = ASyncUtils::ThreadPriotiry::TP_NORMAL
		);

		void SetThreadPriority(ASyncUtils::ThreadPriotiry threadPriotiry);

		void SuspendThread(bool bShouldPause);

		void KillThread(bool bShouldWait = true);

		void WaitForCompletion();

		ASyncUtils::ThreadPriotiry GetThreadPriority() const;

		std::string GetThreadName() const;

#if _HAS_CXX23
		uint32_t GetNativeThreadId() const;
#else
		std::thread::id GetNativeThreadId() const;
#endif

	private:
#if _HAS_CXX23
		uint32_t threadId = 0;
#else
		std::thread::id threadId{}; // Fallback if not using C++23
#endif
		std::string threadName = "ShadowPlayRuntimeThread";
		ASyncUtils::ThreadPriotiry threadPriotiry = ASyncUtils::ThreadPriotiry::TP_NORMAL;
		SPProcessEnt* processEntInst = nullptr;
	};
}