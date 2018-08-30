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

WindowPtr CXCanvas::MakeWindow()
{
	this->pWindow = MakeWindowPtr( pRender );
	pWindow->SetSize( GetSize() );
	AddChildControl( pWindow );
	pWindow->SetIsStandalone( GetIsStandalone() );
	return pWindow;
}

WindowPtr CXCanvas::GetWindow()
{
	return pWindow;
}
