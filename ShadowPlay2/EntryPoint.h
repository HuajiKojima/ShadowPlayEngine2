#pragma once
#include "SPAppBase.h"
#include <iostream>


int32_t main(int32_t argc, char** argv)
{
    ShadowPlay::SPAppBase* application = ShadowPlay::ReturnApp();
    application->AppInit();
    application->AppRun();
    application->AppTerminate();
    system("pause");
    return 0;
}