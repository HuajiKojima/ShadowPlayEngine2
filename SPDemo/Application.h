#pragma once
#include <ShadowPlay.h>

struct ApplicationPrivate;

class Application: public ShadowPlay::SPAppBase
{
public:
    Application();
    ~Application();

    virtual void AppInitCallback();
    virtual void AppRunCallback();
    virtual void AppTerminateCallback();

private:
    ApplicationPrivate* p = nullptr;
};