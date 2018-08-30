#include "stdafx.h"
#include "XDropdown.h"



CXDropdown::CXDropdown( RenderPtr pRender )
	:
	CXControl( pRender )
{
	pTextbox = MakeTextboxPtr( pRender );
	pButton = MakeButtonPtr( pRender );
	pList = MakeListBoxPtr( pRender );
	sizeTextbox.y = 20.f;
	sizeButton = { 15.0f,20.0f };
	sizeList.y = 100.0f;
	bShowList = true;
}


CXDropdown::~CXDropdown()
{
}

void CXDropdown::SetSize( const vec2f & size )
{
	this->size = size;
	
	sizeTextbox.x = size.x - (sizeButton.x - 2.0f);
	pTextbox->SetSize( sizeTextbox );
	
	sizeList.y = size.y - sizeTextbox.y;
	sizeList.x = size.x;
	pList->SetSize( sizeList );
	
	sizeButton.x = size.x - sizeTextbox.x;
	pButton->SetSize( sizeButton );
	
	heights.x = sizeTextbox.y;
	heights.y = size.y;

	
	if ( !bShowList )
		this->size.y = heights.x;
	else
		this->size.y = heights.y;
}

void CXDropdown::SetTextboxSize( const vec2f & size )
{
	sizeTextbox = size;
	pTextbox->SetSize( size );
}

void CXDropdown::SetButtonSize( const vec2f & size )
{
	sizeButton = size;
	pButton->SetSize( size );
}

void CXDropdown::SetListHeight( const float height )
{
	sizeList.y = height;
	pList->SetSize( sizeList );
}

void CXDropdown::AddNewItem( tstring sText )
{
	pList->AddNewItem( sText );
}

void CXDropdown::OnRender()
{
	makeAbsPos();
	pTextbox->SetPos( vAbs );
	pTextbox->OnRender();
	pButton->SetPos( { vAbs.x + sizeTextbox.x, vAbs.y } );
	pButton->OnRender();

	if ( bShowList )
	{
		pList->SetPos( { vAbs.x, vAbs.y + sizeTextbox.y } );
		pList->OnRender();
	}
}

void CXDropdown::OnMouseMove( float x, float y )
{
	SetHot( shared_from_this() );
	if ( bShowList )
	{
		pList->OnMouseMove( x, y );
	}
}

void CXDropdown::OnMouseDown( uint button, float x, float y )
{
	SetFocused( shared_from_this() );
	if ( pButton->PointIntersect( x, y ) )
	{
		bShowList = !bShowList;
		pButton->OnMouseDown( button, x, y );
		return;
	}

	if ( pTextbox->PointIntersect( x, y ) )
	{
		SetFocused( pTextbox );
		pTextbox->OnMouseDown( button, x, y );
	}

	if ( bShowList && pList->PointIntersect(x,y))
	{
		pList->OnMouseDown( button, x, y );
		auto pItem = pList->GetSelected();
		if(pItem)
			pTextbox->SetText( pItem->GetCaption() );
	}
}

void CXDropdown::OnMouseUp( uint button, float x, float y )
{
	if ( bShowList )
	{
		pList->OnMouseUp( button, x, y );
	}
}

void CXDropdown::OnMouseWheel( WPARAM wParam, LPARAM lParam )
{
	if ( bShowList )
		pList->OnMouseWheel( wParam, lParam );
}

void CXDropdown::OnKeyDown( WPARAM key, LPARAM extended )
{
	ControlPtr pFocd;
	if ( pTextbox->GetFocused(pFocd) )
		pTextbox->OnKeyDown( key, extended );
}

void CXDropdown::OnKeyUp( WPARAM key, LPARAM extended )
{
	ControlPtr pFocd;
	if ( pTextbox->GetFocused( pFocd ) )
		pFocused->OnKeyUp( key, extended );
}

void CXDropdown::OnChar( WPARAM key, LPARAM extended )
{
	ControlPtr pFocd;
	if ( pTextbox->GetFocused( pFocd ) )
		pFocused->OnChar( key, extended );
}
