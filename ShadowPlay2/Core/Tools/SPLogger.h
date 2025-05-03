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
		~SPLogger();
        void Log(LoggerLevel level, const char* msgStr) const;
    private:
        LoggerLevel m_loggerLevel;
        
    };
}

// Macros for logging
#define LOG_ERROR(msg) GetLogger().Log(ShadowPlay::SPLogger::LoggerLevel::LOG_ERROR, msg)
#define LOG_WARNING(msg) GetLogger().Log(ShadowPlay::SPLogger::LoggerLevel::LOG_WARNING, msg)
#define LOG_INFO(msg) GetLogger().Log(ShadowPlay::SPLogger::LoggerLevel::LOG_INFO, msg)
