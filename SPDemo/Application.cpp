#include "Application.h"
#include <Core/Memory/SPMemManager.h>

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

}

Application::~Application()
{
    SHADOWPLAY_DEALLOC_HEAPMEM(p, ApplicationPrivate);
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
