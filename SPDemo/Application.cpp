#include "Application.h"
#include <Core/Memory/SPMemManager.h>
#include <Core/Tools/SPLogger.h>

#include <functional>
#include <map>

struct MyStruct
{
    int a;
    int b;
};

struct ApplicationPrivate
{
    ApplicationPrivate()
    {
        a = 0;
    }
    int a;
};

ShadowPlay::SPAppBase * ShadowPlay::ReturnApp()
{
    static Application* app = new Application();
    return app;
}

Application::Application()
{
    SHADOWPLAY_ALLOC_HEAPMEM(p, ApplicationPrivate);
    LOG_INFO("Application::Application");
}

Application::~Application()
{
    SHADOWPLAY_DEALLOC_HEAPMEM(p, ApplicationPrivate);
	LOG_INFO("Application::~Application");
}

void Application::AppInitCallback()
{

    
}

void Application::AppRunCallback()
{
    
}

void Application::AppTerminateCallback()
{
    
}
