#include "stdafx.h"
#include "XWindow.h"



CXWindow::CXWindow(RenderPtr pRender)
	:
	CXControlContainer(pRender)
{
	pLabel = MakeLabelPtr( pRender );
	pLabel->SetFormat( DT_LEFT | DT_VCENTER );
	pLabel->SetText( _T( "UIX" ) );
	pFont = MakeFontPtr( pRender->GetDevice(), pFont->GetFace() );
	pFont->SetHeight( 15 );
	pFont->SetWeight( CFontManager::GetFontPtrByID( 0 )->GetWeight() );
	pFont->Create();
	pLabel->SetFont( pFont );
	bDragging = false;
	size = { 300,200 };
	sizeTitlebar.y = 15.0f;
	sizeTitlebar.x = size.x;
	
}


CXWindow::~CXWindow()
{
}

void CXWindow::SetTitlebarHeight( float height )
{
	sizeTitlebar.y = height;
}

float CXWindow::GetTitlebarHeight()
{
	return sizeTitlebar.y;
}

void CXWindow::SetSize( const vec2f & size )
{
	this->size = size;
	sizeTitlebar.x = size.x;
}

bool CXWindow::IsMoving()
{
	return bDragging;
}

vec2f CXWindow::GetMouseDownPos()
{
	return mousePos;
}

void CXWindow::OnRender()
{
	makeAbsPos();
	if ( !pTexture )
	{
		pRender->DrawRect( vAbs, size, bgColor );
		pRender->DrawBox( vAbs, size, borderWidth, borderColor );
		pRender->DrawBox( vAbs, sizeTitlebar, borderWidth, borderColor );
	}
	else
	{
		pTexture->SetPos( vAbs );
		pRender->DrawTexture( pTexture );
	}
	RECT r;
	r.left = (int)(vAbs.x + 1.0f);
	r.top = (int)vAbs.y;
	r.right = (int)(vAbs.x + sizeTitlebar.x - 1.0f);
	r.bottom = (int)(vAbs.y + sizeTitlebar.y);

	pLabel->SetRectAbs( r );
	pLabel->OnRender();
}

void CXWindow::OnMouseMove( float x, float y )
{
	SetHot(shared_from_this());
	if ( bDragging && !bStandaloneWindow)
	{
		makeAbsPos();
		SetPos( { pos.x + ( x-vAbs.x)-mousePos.x, pos.y + ( y - vAbs.y ) - mousePos.y } );
	}
}

void CXWindow::OnMouseDown( uint button, float x, float y )
{
	auto pThis = shared_from_this();
	SetFocused( pThis );
	if ( TitlebarIntersect( x, y ) )
	{
		makeAbsPos();
		mousePos.x = x - vAbs.x;
		mousePos.y = y - vAbs.y;
		bDragging = true;
		SetMovingControl( pThis );
	}
}

void CXWindow::OnMouseUp( uint button, float x, float y )
{
	bDragging = false;
	SetMovingControl( nullptr );
}

bool CXWindow::TitlebarIntersect( float x, float y )
{
	makeAbsPos();
	RECT tb{ 0 };
	tb.left = (int)vAbs.x;
	tb.right = (int)(vAbs.x + size.x);
	tb.top = (int)vAbs.y;
	tb.bottom = (int)(vAbs.y + sizeTitlebar.y);

	if ( x >= tb.left && x <= tb.right )
		if ( y >= tb.top && y <= tb.bottom )
			return true;

	return false;
}
