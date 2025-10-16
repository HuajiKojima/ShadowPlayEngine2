#include "ShadowPreCompileHeader.h"
#include "SPWindow.h"

namespace ShadowPlay 
{
	struct SPWindowPrivate 
	{
		// Private data members for SPWindow
	};

	void PrivateDelete(SPWindowPrivate* pri) 
	{
		if (pri) 
		{
			delete pri;
			pri = nullptr;
		}
	}

	SPWindow::SPWindow(const SPRect& rect, const std::string& title):
		m_pri(new SPWindowPrivate, PrivateDelete),
		SPDisplay({ { GetLogger() }, rect, title })
	{
		// Constructor implementation
	}
	SPWindow::~SPWindow() 
	{
		// Destructor implementation
	}
	void SPWindow::Init() 
	{
		// Initialization code
	}
    void SPWindow::Terminate()
    {
    }
    void SPWindow::LoopFunc(bool &loopPermission)
    {
    }
}