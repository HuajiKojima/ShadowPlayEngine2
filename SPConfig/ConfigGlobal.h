#pragma once

#ifdef SHADOWPLAY_PLAT_WIN

#ifdef SHADOWPLAY_CONFIG_EXPORT

#define SHADOWPLAY_API __declspec(dllexport)

#else

#define SHADOWPLAY_API __declspec(dllimport)

#endif

#else

#define SHADOWPLAY_API

#endif