#include "ShadowPreCompileHeader.h"
#include "SPObject.h"

#include "SPComponent.h"

namespace ShadowPlay
{
    struct SPObjectPrivate
    {
        std::vector<SPComponent*> m_componentList;
        int m_compoIDCounter = 0;
    };

    SPObject::SPObject()
    {
        m_pri = new SPObjectPrivate;
    }
    SPObject::~SPObject()
    {
    }
    void SPObject::AddComponent(SPComponent* component)
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