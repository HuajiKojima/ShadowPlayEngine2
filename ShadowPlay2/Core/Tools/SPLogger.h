#pragma once
#include "SPGlobal.h"

namespace ShadowPlay
{
    struct SPLoggerPrivate;
    class SHADOWPLAY_API SPLogger final
    {
    public:

        enum class LoggerLevel : uint32_t
        {
            LOG_ERROR = 0,
            LOG_WARNING,
            LOG_INFO,
            LOG_LEVEL_COUNT,
			LOG_ALL = 0XDEADC0DE
        };

        explicit SPLogger(LoggerLevel logLevel = LoggerLevel::LOG_ERROR);
		~SPLogger();
        void Log(LoggerLevel level, const char* msgStr) const;
        void SetLogLevel(LoggerLevel level) { m_loggerLevel = level; }
    private:
        LoggerLevel m_loggerLevel;
        
    };
}

// Macros for logging
#define LOG_ERROR(msg) GetLogger().Log(ShadowPlay::SPLogger::LoggerLevel::LOG_ERROR, msg)
#define LOG_WARNING(msg) GetLogger().Log(ShadowPlay::SPLogger::LoggerLevel::LOG_WARNING, msg)
#define LOG_INFO(msg) GetLogger().Log(ShadowPlay::SPLogger::LoggerLevel::LOG_INFO, msg)
