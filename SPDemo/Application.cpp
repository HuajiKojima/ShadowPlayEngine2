#include "Application.h"
#include <Core/HAL/Memory/SPMemManager.h>
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

void DeleteApplicationPrivate(ApplicationPrivate* p)
{
	if (p != nullptr)
	{
		delete p;
		p = nullptr;
	}
}

ShadowPlay::SPAppBase * ShadowPlay::ReturnApp()
{
    static Application* app = new Application();
    return app;
}

Application::Application():
	SPAppBase(),
	p(new ApplicationPrivate(), DeleteApplicationPrivate)
{
    
    LOG_INFO("Application::Application");
}

Application::~Application()
{
    
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
