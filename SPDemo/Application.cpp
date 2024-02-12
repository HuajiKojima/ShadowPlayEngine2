#include "Application.h"
#include <Core/Memory/SPMemManager.h>
#include <XMLTool/XMLParser.h>

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

// ReturnApp()实体入口的实现方法
ShadowPlay::SPAppBase * ShadowPlay::ReturnApp()
{
    static Application* app = new Application();
    return app;
}

Application::Application()
{
    // 由于引擎内核是通过基类指针调用应用程序入口类，所以引擎内存分配器的初始化会早于应用程序入口类的初始化。
    // 故可以在此调用引擎堆内存分配器进行内存分配。
    SHADOWPLAY_ALLOC_HEAPMEM(p, ApplicationPrivate);
    
}

Application::~Application()
{

}

void Application::AppInitCallback()
{
    ShadowPlay::XMLParser::Testing();

    
}

void Application::AppRunCallback()
{
    
}

void Application::AppTerminateCallback()
{
    SHADOWPLAY_DEALLOC_HEAPMEM(p, ApplicationPrivate);
}
