#pragma once
#include "SPAppBase.h"
#include <iostream>

// ������ڵ㣬ͨ������ָ��������������Ӧ�ó���
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