#pragma once

namespace ShadowPlay
{
    struct SPWorldObjectPrivate;

    class SPComponent;

    class SPWorldObject
    {
    public:
        SPWorldObject();
        ~SPWorldObject();

        void AddComponent(SPComponent* component);



    private:
        SPWorldObjectPrivate* m_pri = nullptr;

    };
}