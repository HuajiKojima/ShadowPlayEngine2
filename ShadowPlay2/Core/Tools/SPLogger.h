#pragma once
#include "SPGlobal.h"

namespace ShadowPlay
{
    struct SPLoggerPrivate;
    class SHADOWPLAY_API SPLogger final
    {
    public:

        enum class LoggerLevel
        {
            LOG_ERROR = 0,
            LOG_WARNING,
            LOG_INFO
        };

        explicit SPLogger(LoggerLevel logLevel = LoggerLevel::LOG_ERROR);
        void Log(LoggerLevel level, const char* msgStr) const;
    private:
        LoggerLevel m_loggerLevel;
        
    };
}