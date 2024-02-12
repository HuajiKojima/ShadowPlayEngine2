#pragma once
#include "SPAppBase.h"
#include <iostream>

// 引擎入口点，通过基类指针调用引擎核心与应用程序
int32_t main(int32_t argc, char** argv)
{
    ShadowPlay::SPAppBase* application = ShadowPlay::ReturnApp();
    application->AppInit();
    application->AppRun();
    application->AppTerminate();
    delete application;
    system("pause");
    return 0;
}