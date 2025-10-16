#pragma once

#include <SPGlobal.h>

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