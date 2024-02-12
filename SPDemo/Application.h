#pragma once
#include <ShadowPlay.h>

// ˽�г�Ա����װ��˽�г�Ա�ṹ���������ǰ��������
struct ApplicationPrivate;

/* 
    ShadowPlay����Ӧ�ó���淶��
    1. ShadowPlay��������Լ�������ģ����ΪShared Library����ʽ��Ӧ�ó�����á�
    2. ���У�Ӧ�ó�����ڵ㣨ָmain�������ѷ�װ��������ģ�������������������е�SPAppBase�����ṩ��
    3. ��Ҫ����������ģ����������ShadowPlay.h��ͷ�ļ���ͬʱ�����̳��������SPAppBase��Ӧ�ó�������࣬�����������ڴ������ʵ���������Ĵ��鷽����
    4. �ڴ���Ӧ�ó�����������ʵ��ReturnApp()ʵ����ڡ�
    **ע��**��ʵ�������Ӧ�ó�����ڶ���ĳ�ʼ�ڴ����Ӧʹ�ñ�׼new��������������У�������������ڴ���䷽����
    **ע��**���������������ͨ������ָ���Ӧ�ó����������е��ã�����Ӧ�ó����������������������ᱻ���ã�
    ��ֹ�Լ���Դ�ͷŵĴ����������AppTerminateCallback�����
*/
class Application: public ShadowPlay::SPAppBase
{
public:
    Application();
    ~Application();

    // �������ֻص������ֱ�Ϊ��ʼ�������У���ֹ

    // Ӧ�ó�����ĳ�ʼ��
    virtual void AppInitCallback();
    // Ӧ�ó���������У��߼�ѭ���ڣ�
    virtual void AppRunCallback();
    // Ӧ�ó��������ֹ�Լ���Դ�ͷ�
    virtual void AppTerminateCallback();

private:
    ApplicationPrivate* p = nullptr;
};