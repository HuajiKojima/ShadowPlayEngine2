#pragma once
#include <ShadowPlay.h>

// 私有成员被封装在私有成员结构体里，以下是前向声明。
struct ApplicationPrivate;

/* 
    ShadowPlay挂载应用程序规范：
    1. ShadowPlay引擎核心以及各工具模块作为Shared Library的形式供应用程序调用。
    2. 其中，应用程序入口点（指main函数）已封装在引擎核心，运行主体由引擎核心中的SPAppBase基类提供。
    3. 若要挂载引擎核心，则需包含“ShadowPlay.h”头文件，同时创建继承自虚基类SPAppBase的应用程序入口类，此入口类必须在代码层面实现虚基类里的纯虚方法。
    4. 在创建应用程序入口类后还需实现ReturnApp()实体入口。
    **注意**：实体入口内应用程序入口对象的初始内存分配应使用标准new运算符重载来进行，而不是引擎的内存分配方法。
    **注意**：由于引擎核心是通过基类指针对应用程序入口类进行调用，所以应用程序入口类的析构函数并不会被调用，
    终止以及资源释放的处理方法请放在AppTerminateCallback方法里。
*/
class Application: public ShadowPlay::SPAppBase
{
public:
    Application();
    ~Application();

    // 以下三种回调方法分别为初始化，运行，终止

    // 应用程序类的初始化
    virtual void AppInitCallback();
    // 应用程序类的运行（逻辑循环内）
    virtual void AppRunCallback();
    // 应用程序类的终止以及资源释放
    virtual void AppTerminateCallback();

private:
    ApplicationPrivate* p = nullptr;
};