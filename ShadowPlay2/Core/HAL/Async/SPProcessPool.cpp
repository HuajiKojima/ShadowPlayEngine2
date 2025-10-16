#include "ShadowPreCompileHeader.h"
#include "SPProcessPool.h"
#include <iostream>

namespace ShadowPlay
{
    bool SPProcessPoolThread::Init()
    {
        return true;
    }
    int32_t SPProcessPoolThread::Run()
    {
        thread_local int x = 0;
        x++;
        std::cout << "Thread ID: " << std::this_thread::get_id() << ", x: " << x << std::endl;
        return 0;
    }
    void SPProcessPoolThread::Stop()
    {
    }
    void SPProcessPoolThread::Terminate()
    {
    }
}