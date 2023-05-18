#include "Application.h"
ShadowPlay::SPAppBase * ShadowPlay::ReturnApp()
{
    static Application* app = new Application();
    return app;
}

Application::Application()
{

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
