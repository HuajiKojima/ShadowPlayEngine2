#pragma once
#include <SPGlobal.h>
#include "SPCommon.h"

namespace ShadowPlay
{
    // Base class for all objects in the ShadowPlay engine
    // This class is not intended to be instantiated directly, but rather to be inherited by other classes.
    class SHADOWPLAY_API SPObject
    {
    public:
        SPObject(SPLogger& logger);
        virtual ~SPObject();

        // Disable copy constructor and assignment operator
        SPObject(const SPObject&) = delete;
        SPObject& operator=(const SPObject&) = delete;

        // Disable move constructor and assignment operator
        SPObject(SPObject&&) = delete;
        SPObject& operator=(SPObject&&) = delete;

        virtual SPLogger& GetLogger() const final;

	private:
		SPLogger& m_objLogger; // Reference to the relays for logging and other operations
    };
}