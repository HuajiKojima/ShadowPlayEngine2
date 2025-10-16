
#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <inttypes.h>
#include <thread>
#include <atomic>
#include <condition_variable>

#ifdef SHADOWPLAY_PLAT_WIN
#include <windows.h>
#include <wrl.h>
#endif