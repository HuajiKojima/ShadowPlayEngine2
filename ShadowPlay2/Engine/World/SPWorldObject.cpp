#include "ShadowPreCompileHeader.h"
#include "SPWorldObject.h"

#include "SPComponent.h"

namespace ShadowPlay
{
    struct SPWorldObjectPrivate
    {
        std::vector<SPComponent*> m_componentList;
        int m_compoIDCounter = 0;
    };

    SPWorldObject::SPWorldObject()
    {
        m_pri = new SPWorldObjectPrivate;
    }
    SPWorldObject::~SPWorldObject()
    {
    }
    void SPWorldObject::AddComponent(SPComponent* component)
    {
        if (m_pri == nullptr || component == nullptr) 
        {
            return;
        }
        component->SetComponentID(m_pri->m_compoIDCounter);
        m_pri->m_compoIDCounter += 1;
        m_pri->m_componentList.push_back(component);
    }
}