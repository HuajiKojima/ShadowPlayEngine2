#include "ShadowPreCompileHeader.h"
#include "SPLogger.h"

namespace ShadowPlay
{
    SPLogger::SPLogger(LoggerLevel logLevel):
        m_loggerLevel(logLevel)
    {
		std::clog << "ShadowPlay Engine2 | 0.1.0" << "\n";
		std::clog << "--------------------------" << "\n";
    }
	SPLogger::~SPLogger()
	{
		std::clog << "----------------------------" << "\n";
		std::clog << "ShadowPlay Engine2 shut down" << "\n";
	}
    void SPLogger::Log(LoggerLevel level, const char *msgStr) const
    {
		auto logEnum2String = [](LoggerLevel level) -> const char*
			{
				switch (level)
				{
				case LoggerLevel::LOG_ERROR: return "ERROR";
				case LoggerLevel::LOG_WARNING: return "WARNING";
				case LoggerLevel::LOG_INFO: return "INFO";
				default: return "UNKNOWN";
				}
			};
        if (level > m_loggerLevel) { return; }
		std::clog << "ShadowPlay::" << logEnum2String(level) << "::" << msgStr << "\n";
    }
}