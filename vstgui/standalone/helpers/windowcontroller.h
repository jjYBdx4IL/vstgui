#pragma once

#include "../iwindowcontroller.h"

//------------------------------------------------------------------------
namespace VSTGUI {
namespace Standalone {

//------------------------------------------------------------------------
class WindowControllerAdapter : public IWindowController
{
public:
	void onSizeChanged (const IWindow& window, const CPoint& newSize) override {}
	void onPositionChanged (const IWindow& window, const CPoint& newPosition) override {}
	void onShow (const IWindow& window) override {}
	void onHide (const IWindow& window) override {}
	void onClosed (const IWindow& window) override {}
	void onActivated (const IWindow& window) override {}
	void onDeactivated (const IWindow& window) override {}
	CPoint constraintSize (const IWindow& window, const CPoint& newSize) override
	{
		return newSize;
	}
	bool canClose (const IWindow& window) const override { return true; }
	void beforeShow (IWindow& window) override {}
	void onSetContentView (IWindow& window, const SharedPointer<CFrame>& contentView) override {};
};


//------------------------------------------------------------------------
} // Standalone
} // VSTGUI
