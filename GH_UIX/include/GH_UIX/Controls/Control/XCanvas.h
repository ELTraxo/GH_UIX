#pragma once
#include "XControlContainer.h"

class CXCanvas : public CXControlContainer
{
public:
	CXCanvas( RenderPtr pRender );
	~CXCanvas();
	void MakeWindow();
};

#define MakeCanvasPtr(pRender)\
std::make_shared<Canvas>(pRender)