#pragma once
#include "SPGlobal.h"
#include "Core/Common/SPObject.h"

#include <memory>

namespace ShadowPlay
{
    struct SPAppBasePrivate;

	class SHADOWPLAY_API SPAppBase : public SPObject
    {
    public:
        SPAppBase(/* args */);
        virtual ~SPAppBase();

        void AppInit();
        void AppRun();
        void AppTerminate();

        virtual void AppInitCallback() = 0;
        virtual void AppRunCallback() = 0;
        virtual void AppTerminateCallback() = 0;
    private:
        /* data */
        SPAppBasePrivate* p;
        std::unique_ptr<SPLogger> m_logInstance;
    };

    extern "C" SHADOWPLAY_API SPAppBase * ReturnApp();
}