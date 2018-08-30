#pragma once
#include "XControlContainer.h"

class CXCanvas : public CXControlContainer
{
	WindowPtr pWindow;
public:
	CXCanvas( RenderPtr pRender );
	~CXCanvas();
	virtual WindowPtr MakeWindow();
	virtual WindowPtr GetWindow();
};

#define MakeCanvasPtr(pRender)\
std::make_shared<Canvas>(pRender)