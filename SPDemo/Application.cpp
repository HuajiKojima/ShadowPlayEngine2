#include "Application.h"

struct ApplicationPrivate
{

};

ShadowPlay::SPAppBase * ShadowPlay::ReturnApp()
{
    static Application* app = new Application();
    return app;
}

Application::Application()
{
    p = new ApplicationPrivate();
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
