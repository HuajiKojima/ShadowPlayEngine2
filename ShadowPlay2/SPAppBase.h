#pragma once
#include "SPGlobal.h"

namespace ShadowPlay
{
    struct SPAppBasePrivate;

    class SHADOWPLAY_API SPAppBase
    {
    public:
        SPAppBase(/* args */);
        ~SPAppBase();

        void AppInit();
        void AppRun();
        void AppTerminate();

        virtual void AppInitCallback() = 0;
        virtual void AppRunCallback() = 0;
        virtual void AppTerminateCallback() = 0;
    private:
        /* data */
        SPAppBasePrivate* p;
    };

    extern "C" SHADOWPLAY_API SPAppBase * ReturnApp();
}