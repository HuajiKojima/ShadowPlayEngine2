#pragma once
#include <ShadowPlay.h>

class Application: public ShadowPlay::SPAppBase
{
public:
    Application();
    ~Application();

    virtual void AppInitCallback();
    virtual void AppRunCallback();
    virtual void AppTerminateCallback();

private:
};