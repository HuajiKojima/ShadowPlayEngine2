#pragma once
#include "SPAppBase.h"
#include <iostream>


int main(int argc, char** argv)
{
    ShadowPlay::SPAppBase* application = ShadowPlay::ReturnApp();
    application->AppInit();
    application->AppRun();
    application->AppTerminate();
    system("pause");
    return 0;
}