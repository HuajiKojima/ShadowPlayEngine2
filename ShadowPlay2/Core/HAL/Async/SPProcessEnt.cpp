#include "ShadowPreCompileHeader.h"
#include "SPProcessEnt.h"

namespace ShadowPlay
{
	struct SPProcessEntThreadPrivate;

	SPProcessEntThread* SPProcessEntThread::Create
	(
		SPProcessEnt* processEntInst,
		const char* threadName,
		ASyncUtils::ThreadPriotiry threadPriotiry
	)
	{
		if (processEntInst == nullptr)
		{
			return nullptr;
		}

		SPProcessEntThread* spThread = new SPProcessEntThread();
		if (spThread == nullptr)
		{
			return nullptr;
		}

		spThread->processEntInst = processEntInst;
		spThread->threadPriotiry = threadPriotiry;
		if (threadName != nullptr)
		{
			spThread->threadName = threadName;
		}

		try
		{
			spThread->thread = new std::thread([spThread]()
				{
					if (spThread->processEntInst != nullptr)
					{
						spThread->processEntInst->Run();
					}
				});
			if (spThread->thread == nullptr)
			{
				delete spThread;
				return nullptr;
			}
			// _Get_underlying_id() is a C++23 feature to get the native thread ID
#if _HAS_CXX23
			spThread->threadId = static_cast<uint32_t>(spThread->thread->get_id()._Get_underlying_id()); 
#else
			spThread->threadId = spThread->thread->get_id(); // Fallback if not using C++23
#endif
		}
		catch (...)
		{
			delete spThread;
			return nullptr;
		}

		spThread->SetThreadPriority(threadPriotiry);

		return spThread;
	}

	void SPProcessEntThread::SetThreadPriority(ASyncUtils::ThreadPriotiry threadPriotiry)
	{
		this->threadPriotiry = threadPriotiry;
	}

	void SPProcessEntThread::SuspendThread(bool bShouldPause)
	{
		// TODO: When using the OS-specific thread API, implement the logic here
	}
	void SPProcessEntThread::KillThread(bool bShouldWait)
	{
		// TODO: When using the OS-specific thread API, implement the logic here
	}
	void SPProcessEntThread::WaitForCompletion()
	{
		while (!thread->joinable())
		{
			std::this_thread::yield();
		}
		thread->join();
		delete thread;
		thread = nullptr;
	}
	ASyncUtils::ThreadPriotiry SPProcessEntThread::GetThreadPriority() const
	{
		return threadPriotiry;
	}
	std::string SPProcessEntThread::GetThreadName() const
	{
		return threadName;
	}
#if _HAS_CXX23
	uint32_t SPProcessEntThread::GetNativeThreadId() const
	{
		return threadId;
	}
#else
	std::thread::id SPProcessEntThread::GetNativeThreadId() const
	{
		return threadId;
	}
#endif
}