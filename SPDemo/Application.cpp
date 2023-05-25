#include "Application.h"
#include <Core/Memory/SPMemManager.h>

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
    //p = new ApplicationPrivate();
    ApplicationPrivate* b;

    SHADOWPLAY_ALLOC_HEAPMEM(p, ApplicationPrivate);
    SHADOWPLAY_ALLOC_HEAPMEM(b, ApplicationPrivate);
    SHADOWPLAY_DEALLOC_HEAPMEM(b, ApplicationPrivate);
}

Application::~Application()
{
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
