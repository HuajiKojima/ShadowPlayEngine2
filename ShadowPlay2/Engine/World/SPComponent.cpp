#include "ShadowPreCompileHeader.h"
#include "SPComponent.h"
namespace ShadowPlay
{
    struct SPComponentPrivate 
    {
        int32_t m_componentID = -1;
        std::string m_componentName;
        
    };

    SPComponent::SPComponent()
    {
        m_pri = new SPComponentPrivate;
    }
    
    SPComponent::~SPComponent()
    {

    }

    void SPComponent::SetComponentID(int32_t componentID)
    {
        if (m_pri == nullptr) 
        {
            return;
        }
        m_pri->m_componentID = componentID;
    }

    int32_t SPComponent::GetComponentID()
    {
        if (m_pri == nullptr)
        {
            return -1;
        }
        return m_pri->m_componentID;
    }

    void SPComponent::SetComponentName(std::string componentName)
    {
        if (m_pri == nullptr)
        {
            return;
        }
        m_pri->m_componentName = componentName;
    }

    std::string SPComponent::GetComponentName()
    {
        if (m_pri == nullptr)
        {
            return std::string();
        }
        return m_pri->m_componentName;
    }
}