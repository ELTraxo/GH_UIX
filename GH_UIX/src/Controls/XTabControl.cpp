#include "stdafx.h"
#include "XTabControl.h"

CXTabCanvas::CXTabCanvas( RenderPtr pRender )
	:
	CXControlContainer( pRender )
{
}

CXTabCanvas::~CXTabCanvas()
{
}

void CXTabCanvas::SetIndex( int index )
{
	this->iIndex = index;
}

int CXTabCanvas::GetIndex()
{
	return iIndex;
}

void CXTabCanvas::OnRender()
{
}

//---------------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------------

CXTabButton::CXTabButton( RenderPtr pRender )
	:
	CXButton( pRender )
{
	bSelected = false;
	ActiveColor = 0xFF202020;
}

CXTabButton::~CXTabButton()
{
}

void CXTabButton::SetPos( const vec2f & pos )
{
	if ( GetPrevControl() )
	{
		auto prev = GetPrevControl();
		auto temp = prev->GetPos();
		temp.x += prev->GetWidth();
		this->pos = temp;
	}
	else
		this->pos = pos;

	if ( GetNextControl() )
	{
		TabButtonPtr pNext = std::dynamic_pointer_cast<TabButton>( GetNextControl() );
		pNext->SetPos( pos );
	}
}

void CXTabButton::SetCanvas( TabCanvasPtr pCanvas )
{
	this->pCanvas = pCanvas;
}

TabCanvasPtr CXTabButton::GetCanvas()
{
	return pCanvas;
}

void CXTabButton::SetSelected( ControlPtr pSelected )
{
	if ( !bSelected )
	{
		if ( pSelected.get() == this )
		{
			bSelected = true;
			this->pSelected = std::dynamic_pointer_cast<TabButton>(pSelected);
		}
		else
		{
			bSelected = false;
			this->pSelected = std::dynamic_pointer_cast<TabButton>( pSelected );
		}
	}
	if ( bSelected && pSelected.get() != this )
	{
		bSelected = false;
		this->pSelected = std::dynamic_pointer_cast<TabButton>( pSelected );
	}
}

void CXTabButton::SetSelected( bool bSelected )
{
	this->bSelected = bSelected;
}

bool CXTabButton::IsActive()
{
	return bSelected;
}

void CXTabButton::OnRender()
{
	auto temp = bgColor;
	if ( IsActive() )
		bgColor = ActiveColor;
	CXButton::OnRender();
	bgColor = temp;
}

void CXTabButton::OnMouseDown( uint button, float x, float y )
{
	if ( !bSelected )
		bSelected = true;
	//PostToAll( WM_SETSELECTED, 0, 0, shared_from_this() );
}

//---------------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------------

CXTabControl::CXTabControl( RenderPtr pRender )
	:
	CXControl(pRender)
{
	//pCanvas = MakeControlPtr( pRender );
	//pTabs = MakeButtonPtr( pRender );
	//pTabs->SetPos( 0 );
	tabSize = { 100,35 };
	tabCount = 0;
	//pTabs->SetSize( tabSize );	
	iCurrentTab = 0;
	pActiveTab = nullptr;
}


CXTabControl::~CXTabControl()
{
}

void CXTabControl::SetSize( const vec2f & size )
{
	this->size = size;
	//pCanvas->SetSize( { size.x, size.y - tabSize.y } );
}

TabCanvasPtr CXTabControl::AddTab( tstring tabText )
{
	if ( !pTabs )
	{
		makeAbsPos();
		pTabs = MakeTabButtonPtr( pRender );
		//AddChildControl( pTabs );
		pTabs->SetSize( tabSize );
		pTabs->SetText( tabText );
		pTabs->SetPos( 0 );
		pCanvas = MakeTabCanvasPtr( pRender );
		pCanvas->SetSize( { size.x, size.y - tabSize.y } );
		pCanvas->SetPos( { 0, tabSize.y } );
		//AddChildControl( pCanvas );
		pTabs->SetCanvas( pCanvas );
		tabCount++;
		pTabs->SetSelected( true );
		pActiveTab = pTabs;
		return pCanvas;
	}
	else
	{
		if ( pTabs->GetNextControl() )
		{
			auto next = pTabs->GetNextControl();
			while ( next )
			{
				auto temp = next->GetNextControl();
				if ( temp )
					next = temp;
				else
				{
					auto tab = MakeTabButtonPtr( pRender );
					//AddChildControl( tab );
					tab->SetSize( tabSize );
					tab->SetText( tabText );
					next->SetNextControl( tab );
					tab->SetPrevControl( next );
					tab->SetPos( { pTabs->GetWidth() * tabCount, 0 } );
					auto pCanvas = MakeTabCanvasPtr( pRender );
					pCanvas->SetSize( { size.x, size.y - tabSize.y } );
					pCanvas->SetPos( { 0, tabSize.y } );
					//AddChildControl( pCanvas );
					tab->SetCanvas( pCanvas );
					tabCount++;
					return pCanvas;
				}
			}
		}
		else
		{
			auto tab = MakeTabButtonPtr( pRender );
			//AddChildControl( tab );
			tab->SetSize( tabSize );
			tab->SetText( tabText );
			pTabs->SetNextControl( tab );
			tab->SetPrevControl( pTabs );
			tab->SetPos( { pTabs->GetWidth(), 0 } );
			auto pCanvas = MakeTabCanvasPtr( pRender );
			pCanvas->SetSize( { size.x, size.y - tabSize.y } );
			pCanvas->SetPos( { 0, tabSize.y } );
			//AddChildControl( pCanvas );
			tab->SetCanvas( pCanvas );
			tabCount++;
			return pCanvas;
		}
	}
	return nullptr;
}

void CXTabControl::OnRender()
{
	makeAbsPos();
	auto tabHeight = tabSize.y;
	pRender->DrawRect( vAbs, size, bgColor );
	pRender->DrawBox( vAbs, size, 1.0f, borderColor );
	pRender->DrawLine( { vAbs.x, vAbs.y + tabHeight }, { vAbs.x + size.x, vAbs.y + tabHeight }, borderColor );

	if ( pTabs )
	{
		pTabs->SetPos( vAbs );
		PostToAll( pTabs, WM_RENDER, 0, 0, nullptr );
		////pCanvas = GetSelectedTab()->GetCanvas();
		pCanvas->SetPos( { vAbs.x, vAbs.y + tabSize.y } );
		//pCanvas->SetColor( 0xFFAAAAAA );
		pCanvas->PostMsg( WM_RENDER, 0, 0, nullptr );
	}

}

void CXTabControl::OnMouseMove( float x, float y )
{
	if ( pTabs )
	{
		auto pTab = PostToAll( pTabs, WM_MOUSEMOVE, 0, MAKELPARAM( (int)x, (int)y ), nullptr );
	}
}

void CXTabControl::OnMouseDown( uint button, float x, float y )
{
	if ( pTabs )
	{
		auto temp = PostToAll( pTabs, WM_LBUTTONDOWN, 0, MAKELPARAM( (int)x, (int)y ), nullptr );
		if ( temp )
		{
			if ( pActiveTab )
				pActiveTab->SetSelected( false );
			pActiveTab = std::dynamic_pointer_cast<CXTabButton>( temp );
			pCanvas = pActiveTab->GetCanvas();
		}
	}
}

void CXTabControl::OnMouseUp( uint button, float x, float y )
{
	if ( pTabs )
	{
		PostToAll( pTabs, WM_LBUTTONDOWN, 0, MAKELPARAM( (int)x, (int)y ), nullptr );
	}
}
