#pragma once
#include "SPGlobal.h"

namespace ShadowPlay
{
    struct SPAppBasePrivate;

    /*
    *   引擎核心应用程序基类
    */
    class SHADOWPLAY_API SPAppBase
    {
    public:
        SPAppBase(/* args */);
        ~SPAppBase();

        void AppInit();
        void AppRun();
        void AppTerminate();

        // 应用程序入口类在代码层面上必须实现的方法
        // 即初始化、运行、终止释放
        // --------------------------------------------------------------
        virtual void AppInitCallback() = 0;
        virtual void AppRunCallback() = 0;
        virtual void AppTerminateCallback() = 0;
        // --------------------------------------------------------------
    private:
        /* data */
        SPAppBasePrivate* p;
    };

    // 挂载本引擎的应用程序必须实现的实体入口方法
    extern "C" SHADOWPLAY_API SPAppBase * ReturnApp();
}