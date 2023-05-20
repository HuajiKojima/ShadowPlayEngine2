#pragma once
#ifdef SHADOWPLAY_PLAT_WIN

#ifdef SHADOWPLAY_CORE_EXPORT
#define SHADOWPLAY_API __declspec(dllexport)
#else
#define SHADOWPLAY_API __declspec(dllimport)
#endif

#else

#define SHADOWPLAY_API

#endif

#ifdef SHADOWPLAY_DEBUG
#define SHADOWPLAY_ASSERT(condition)\
if(condition)\
{\
	NULL;\
}\
else\
{\
	SPAssert(__FILE__, __LINE__);\
}

inline void SPAssert(const char* fileName, unsigned int lineNum)
{
	fflush(stdout);
	fprintf(stderr, "\nSHADOWPLAY::ASSERT::FATAL::%s, line %u", fileName, lineNum);
	fflush(stderr);
	abort();
}
#else
#define SHADOWPLAY_ASSERT(condition)
#endif