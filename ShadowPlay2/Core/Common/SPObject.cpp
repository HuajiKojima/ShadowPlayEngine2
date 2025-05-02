#include "ShadowPreCompileHeader.h"
#include "SPObject.h"

namespace ShadowPlay
{
    SPObject::SPObject(const SPObjRelays& relays) :
		m_objLogger(relays.m_logger)
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