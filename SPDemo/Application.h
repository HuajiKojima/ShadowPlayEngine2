#pragma once
#include <memory>
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
	std::unique_ptr<ApplicationPrivate, void(*)(ApplicationPrivate*)> p;
};