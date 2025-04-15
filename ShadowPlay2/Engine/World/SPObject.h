#pragma once

namespace ShadowPlay
{
    struct SPObjectPrivate;

    class SPComponent;

    class SPObject
    {
    public:
        SPObject();
        ~SPObject();

        void AddComponent(SPComponent* component);



    private:
        SPObjectPrivate* m_pri = nullptr;

    };
}