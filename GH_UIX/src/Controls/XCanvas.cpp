#include "stdafx.h"
#include "XCanvas.h"
#include "XWindow.h"

CXCanvas::CXCanvas( RenderPtr pRender )
	:
	CXControlContainer( pRender )
{
}

CXCanvas::~CXCanvas()
{
}

void CXCanvas::MakeWindow()
{
	auto pWindow = MakeWindowPtr( pRender );
	AddChildControl( pWindow );
}
