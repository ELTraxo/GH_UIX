#include "stdafx.h"
#include "XControl.h"



CXControl::CXControl( RenderPtr pRender )
{
	this->pRender = pRender;
	this->pFont = CFontManager::GetFontPtrByID( 0 );
	this->pTexture = nullptr;
	this->pos = 0;
	this->size = 0;
	this->bgColor = 0xFF000000;
	this->borderColor = 0xFFFFFFFF;
	this->borderWidth = 1.0f;
	this->isVisible = true;
	this->isHot = false;
	this->pHot = nullptr;
	this->isFocused = false;
	this->pFocused = nullptr;
	this->pParent = nullptr;
	this->pChildren = nullptr;
	this->pNext = nullptr;
	this->pPrev = nullptr;
	this->pFocused = nullptr;
	this->pMoving = nullptr;
	this->bUseRect = false;
	this->rect = RECT{ 0 };
}


CXControl::~CXControl()
{
}

void CXControl::SetRenderer( RenderPtr pRender )
{
	this->pRender = pRender;
}

RenderPtr CXControl::GetRenderer()
{
	return pRender;
}

void CXControl::SetFont( FontPtr pFont )
{
	this->pFont = pFont;
}

FontPtr CXControl::GetFont()
{
	return pFont;
}

void CXControl::SetTexture( TexturePtr pTexture )
{
	this->pTexture = pTexture;
}

TexturePtr CXControl::GetTexture()
{
	return pTexture;
}

void CXControl::SetHotTexture( TexturePtr pTexture )
{
	this->pHotTexture = pTexture;
}

TexturePtr CXControl::GetHotTexture()
{
	return pHotTexture;
}

vec2f CXControl::GetAbsPos( vec2f & pos )
{
	if(GetParent())
		GetParent()->GetAbsPos( pos );

	pos += this->pos;

	return pos;
}

void CXControl::SetPos( const vec2f & pos )
{
	this->pos = pos;
}

vec2f CXControl::GetPos()
{
	return pos;
}

void CXControl::SetSize( const vec2f & size )
{
	this->size = size;
}

vec2f CXControl::GetSize()
{
	return size;
}

float CXControl::GetWidth()
{
	return size.x;
}

float CXControl::GetHeight()
{
	return size.y;
}

vec2f CXControl::GetCenter()
{
	auto center = GetPos();
	center += GetSize() / 2;
	return center;
}

void CXControl::SetColor( Color color )
{
	this->bgColor = color;
}

Color CXControl::GetColor()
{
	return bgColor;
}

void CXControl::SetBorderColor( Color color )
{
	this->borderColor = color;
}

Color CXControl::GetBorderColor()
{
	return borderColor;
}

void CXControl::SetVisible( bool isVisible )
{
	this->isVisible = isVisible;
}

bool CXControl::GetVisible()
{
	return isVisible;
}

void CXControl::SetHot( ControlPtr pControl )
{
	if ( GetParent() )
		GetParent()->SetHot( pControl );
	else
	{
		PostMsg( WM_SETHOT, 0, 0, &pControl );
	}	
}

bool CXControl::GetHot( ControlPtr & pControl )
{
	pControl = pHot;
	return isHot;
}

void CXControl::SetFocused( ControlPtr pControl )
{
	if ( GetParent() )
		GetParent()->SetFocused( pControl );
	else
	{
		PostMsg( WM_SETFOCUSED, 0, 0, &pControl );
	}
}

bool CXControl::GetFocused( ControlPtr & pControl )
{
	pControl = pFocused;
	return isFocused;
}

void CXControl::SetRectAbs( const RECT & rect, bool bUseRect )
{
	this->bUseRect = bUseRect;
	this->rect.left = rect.left;
	this->rect.right = rect.right;
	this->rect.top = rect.top;
	this->rect.bottom = rect.bottom;
}

RECT CXControl::GetRectAbs()
{
	makeAbsPos();
	rect.left = (int)vAbs.x;
	rect.right = (int)(vAbs.x + size.x);
	rect.top = (int)vAbs.y;
	rect.bottom = (int)(vAbs.y + size.y);
	return rect;
}

void CXControl::SetParent( ControlPtr pParent )
{
	this->pParent = pParent;
}

ControlPtr CXControl::GetParent()
{
	return pParent;
}

void CXControl::AddChildControl( ControlPtr pControl )
{
	if(!pChildren)
	{
		pControl->SetParent( this->shared_from_this() );
		pChildren = pControl;
	}
	else
	{
		auto pTemp = pChildren;
		auto pNext = pTemp->GetNextControl();
		while(pNext)
		{
			pTemp = pNext;
			pNext = pNext->GetNextControl();
		}
		pTemp->SetNextControl( pControl );
		pControl->SetPrevControl( pTemp );
		pControl->SetParent( this->shared_from_this() );
	}
}

ControlPtr CXControl::GetChildren()
{
	return pChildren;
}

void CXControl::SetNextControl( ControlPtr pControl )
{
	this->pNext = pControl;
}

ControlPtr CXControl::GetNextControl()
{
	return pNext;
}

void CXControl::SetPrevControl( ControlPtr pControl )
{
	this->pPrev = pControl;
}

ControlPtr CXControl::GetPrevControl()
{
	return pPrev;
}

void CXControl::SetMovingControl( ControlPtr pControl )
{
	if ( GetParent() )
		GetParent()->SetMovingControl( pControl );
	
	pMoving = pControl;
}

bool CXControl::PointIntersect( float x, float y )
{
	makeAbsPos();

	if ( x >= vAbs.x && x <= vAbs.x + size.x )
	{
		if ( y >= vAbs.y && y <= vAbs.y + size.y )
			return true;
	}
	return false;
}

ControlPtr CXControl::PostToAll( uint msg, WPARAM wParam, LPARAM lParam, void * pData )
{
	return PostToAll( nullptr, msg, wParam, lParam, pData );
}

ControlPtr CXControl::PostToAll( ControlPtr pControl, uint msg, WPARAM wParam, LPARAM lParam, void * pData )
{
	ControlPtr temp = pControl;
	if(!temp)
		temp = GetChildren();
	while(temp)
	{
		auto next = temp->GetNextControl();
		if(temp->PostMsg( msg, wParam, lParam, pData ))
			return temp;
		temp = next;
	}
	return nullptr;
}

ControlPtr CXControl::PostToAllReverse( ControlPtr pControl, uint msg, WPARAM wParam, LPARAM lParam, void * pData )
{
	auto next = pControl->GetNextControl();
	if ( next )
		next->PostToAllReverse( next, msg, wParam, lParam, pData );
	pControl->PostMsg( msg, wParam, lParam, pData );
	return nullptr;
}

bool CXControl::PostMsg( uint msg, WPARAM wParam, LPARAM lParam, void * pData )
{
	switch ( msg )
	{
		case WM_SETRENDERER:
		{
			if ( pData )
			{
				SetRenderer( *(RenderPtr*)pData );
				PostToAll( msg, wParam, lParam, pData );
			}
			break;
		}
		case WM_SETHOT:
		{
			if ( pData )
			{
				OnSetHot( pData );
				PostToAll( msg, wParam, lParam, pData );
			}
			break;
		}
		case WM_SETFOCUSED:
		{
			if ( pData )
			{
				OnSetFocus( pData );
				PostToAll( msg, wParam, lParam, pData );
			}
			break;
		}
		case WM_RENDER:
		{
			if ( GetVisible() )
			{
				OnRender();
				if ( pChildren )
					PostToAll( pChildren, msg, wParam, lParam, pData );
			}
			break;
		}
		case WM_MOUSEWHEEL:
		{
			if ( pHot )
			{
				pHot->OnMouseWheel( wParam, lParam );
				return true;
			}
			break;
		}
		case WM_MOUSEMOVE:
		{
			if ( pMoving )
			{
				pMoving->OnMouseMove( (float)GET_X_LPARAM( lParam ), (float)GET_Y_LPARAM( lParam ) );
				return true;
			}
			if ( PointIntersect( (float)GET_X_LPARAM( lParam ), (float)GET_Y_LPARAM( lParam ) ) )
			{
				
				auto pControl = PostToAll( msg, wParam, lParam, pData );
				if ( !pControl )
					OnMouseMove( (float)GET_X_LPARAM( lParam ), (float)GET_Y_LPARAM( lParam ) );
				
				return true;
			}
		}
		case WM_LBUTTONUP:
		case WM_LBUTTONDOWN:
		{
			if ( PointIntersect( (float)GET_X_LPARAM( lParam ), (float)GET_Y_LPARAM( lParam ) ) )
			{
				auto pControl = PostToAll( msg, wParam, lParam, pData );
				if ( !pControl )
				{
					switch ( msg )
					{
						case WM_LBUTTONUP:
						{
							if ( pMoving )
							{
								pMoving->OnMouseUp( wParam, (float)GET_X_LPARAM( lParam ), (float)GET_Y_LPARAM( lParam ) );
								return true;
							}
							OnMouseUp( wParam, (float)GET_X_LPARAM( lParam ), (float)GET_Y_LPARAM( lParam ) );
							return true;
						}
						case WM_LBUTTONDOWN:
						{
							OnMouseDown( wParam, (float)GET_X_LPARAM( lParam ), (float)GET_Y_LPARAM( lParam ) );
							return true;
						}
						case WM_MOUSEHWHEEL:
						{
							OnMouseWheel( wParam, lParam );
							return true;
						}
					}
				}
			}
			break;
		}
		case WM_KEYDOWN:
		case WM_KEYUP:
		case WM_CHAR:
		{
			if ( pFocused )
			{
				switch ( msg )
				{
					case WM_KEYDOWN:
					{
						pFocused->OnKeyDown( wParam, lParam );
						break;
					}
					case WM_KEYUP:
					{
						pFocused->OnKeyUp( wParam, lParam );
						break;
					}
					case WM_CHAR:
					{
						pFocused->OnChar( wParam, lParam );
						break;
					}
				}
			}
			
			break;
		}
	}
	return false;
}

void CXControl::OnSetHot( void * pData )
{
	if ( pData )
	{
		void* pControl = *(void**)pData;
		this->isHot = false;
		if ( pControl == (void*)this )
		{
			this->isHot = true;
			if ( pHot )
				pHot->OnLoseHot( &shared_from_this() );
		}
		
		this->pHot = *(ControlPtr*)pData;
	}
}

void CXControl::OnLoseHot( void * pData )
{
	this->isHot = false;
	this->pHot = *( ControlPtr* )pData;
}

void CXControl::OnSetFocus( void * pData )
{
	if ( pData )
	{
		void* pControl = *(void**)pData;
		this->isFocused = false;
		if ( pControl == ( void* )this )
		{
			this->isFocused = true;
		}

		this->pFocused = *(ControlPtr*)pData;
	}
}
