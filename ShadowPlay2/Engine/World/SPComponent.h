#pragma once

namespace ShadowPlay
{
    struct SPComponentPrivate;

    class SPComponent
    {
    public:
        SPComponent();
        ~SPComponent();

        void SetComponentID(int32_t componentID);

        int32_t GetComponentID();

        void SetComponentName(std::string componentName);

        std::string GetComponentName();

    private:
        SPComponentPrivate* m_pri = nullptr;
    };
}