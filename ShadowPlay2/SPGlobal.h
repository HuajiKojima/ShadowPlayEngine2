#pragma once
#ifdef SHADOWPLAY_API_DX
//#include <d3d12.h>
#endif

#ifdef SHADOWPLAY_ACC_DX
#endif

#ifdef SHADOWPLAY_ACC_AVX
#endif

#ifdef SHADOWPLAY_PLAT_WIN

#ifdef SHADOWPLAY_CORE_EXPORT
#define SHADOWPLAY_API __declspec(dllexport)
#else
#define SHADOWPLAY_API __declspec(dllimport)
#endif

#else

#define SHADOWPLAY_API

#endif