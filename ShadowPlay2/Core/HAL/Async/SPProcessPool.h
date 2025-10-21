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

	class SHADOWPLAY_API SPPoolWork 
	{
	public:
	};

	class SHADOWPLAY_API SPProcessPool
	{
	public:
		bool Create(int32_t threadCount = 8, const std::string& poolName = "DefaultThreadPool");

		void Destroy();

		//void PushTaskToQueue();
	};
}