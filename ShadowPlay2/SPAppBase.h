#pragma once
#include "SPGlobal.h"

namespace ShadowPlay
{
    struct SPAppBasePrivate;

    /*
    *   �������Ӧ�ó������
    */
    class SHADOWPLAY_API SPAppBase
    {
    public:
        SPAppBase(/* args */);
        ~SPAppBase();

        void AppInit();
        void AppRun();
        void AppTerminate();

        // Ӧ�ó���������ڴ�������ϱ���ʵ�ֵķ���
        // ����ʼ�������С���ֹ�ͷ�
        // --------------------------------------------------------------
        virtual void AppInitCallback() = 0;
        virtual void AppRunCallback() = 0;
        virtual void AppTerminateCallback() = 0;
        // --------------------------------------------------------------
    private:
        /* data */
        SPAppBasePrivate* p;
    };

    // ���ر������Ӧ�ó������ʵ�ֵ�ʵ����ڷ���
    extern "C" SHADOWPLAY_API SPAppBase * ReturnApp();
}