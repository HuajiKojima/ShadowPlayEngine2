#include "ShadowPreCompileHeader.h"
#include "SPObject.h"

namespace ShadowPlay
{
    SPObject::SPObject(SPLogger& logger):
		m_objLogger(logger)
    {
    }
    SPLogger& SPObject::GetLogger() const
    {
        return m_objLogger;
    }
    SPObject::~SPObject()
    {

    }


}