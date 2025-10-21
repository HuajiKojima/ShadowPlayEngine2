#pragma once

#include <SPGlobal.h>

#include <inttypes.h>
#include <thread>
#include <string>
#include <atomic>
#include <condition_variable>

namespace ShadowPlay
{
	namespace ASyncUtils
	{
		enum class SHADOWPLAY_API ThreadPriotiry
		{
			TP_LOWEST,
			TP_BELOW_NORMAL,
			TP_NORMAL,
			TP_ABOVE_NORMAL,
			TP_HIGHEST,
			TP_TIME_CRITICAL,
			TP_NUM
		};
	}
}