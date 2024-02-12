#include "ShadowPreCompileHeader.h"
#include "SPRHI.h"

namespace ShadowPlay
{
    struct SPRHIPrivate
    {
        // The large param is up, smaller is down.
		const char* m_windowTitle = nullptr;	// 8 Bytes
		int m_windowWidth = 0;					      // 4 Bytes
		int m_windowHeight = 0;					      // 4 Bytes
    };

    SPRHI::SPRHI()
    {
        p = new SPRHIPrivate();
    }

    SPRHI::~SPRHI()
    {
		SHADOWPLAY_ASSERT(p != nullptr);
        delete p;
    }
    void SPRHI::setPrivate(uint32_t width, uint32_t height, const char *windowTitle)
    {
		SHADOWPLAY_ASSERT(p != nullptr);
		p->m_windowWidth = width;
		p->m_windowHeight = height;
		p->m_windowTitle = windowTitle;
    }
    int SPRHI::GetWidth()
    {
		SHADOWPLAY_ASSERT(p != nullptr);
        return p->m_windowWidth;
    }
    int SPRHI::GetHeight()
    {
		SHADOWPLAY_ASSERT(p != nullptr);
        return p->m_windowHeight;
    }
    const char *SPRHI::GetWindowTitle()
    {
		SHADOWPLAY_ASSERT(p != nullptr);
        return p->m_windowTitle;
    }
}