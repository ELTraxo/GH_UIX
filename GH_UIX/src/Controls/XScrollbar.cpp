#include "stdafx.h"
#include "XScrollbar.h"



CXScrollbar::CXScrollbar( RenderPtr pRender )
	:
	CXControl(pRender)
{

	this->btnTopLeft = MakeButtonPtr(pRender);
	this->btnBottomRight = MakeButtonPtr( pRender );
	this->btnThumb = MakeButtonPtr(pRender);
	this->iMin = 0;
	this->iMax = 10;
	this->iValue = 0;
	this->bDrag = false;
	this->orientation = EScrollOrientation::VERTICAL;
}


CXScrollbar::~CXScrollbar()
{
}

ButtonPtr CXScrollbar::GetThumb()
{
	return btnThumb;
}

ButtonPtr CXScrollbar::GetTopLeftButton()
{
	return btnTopLeft;
}

ButtonPtr CXScrollbar::GetBottomRightButton()
{
	return btnBottomRight;
}

void CXScrollbar::SetSize( vec2f size )
{
	this->size = size;
	this->btnTopLeft->SetSize( { size.x, size.x } );
	this->btnBottomRight->SetSize( { size.x, size.x } );
	if ( iMax == 0 )
		this->btnThumb->SetSize( { size.x, 0.0f } );
	else
	{
		auto thumbHeight = size.y - ( btnTopLeft->GetSize().y * 2 );
		thumbHeight /= iMax + 1;
		this->btnThumb->SetSize( { size.x, thumbHeight } );
	}
}

void CXScrollbar::SetColor( Color color )
{
	this->bgColor = color;
	this->btnTopLeft->SetColor( color );
	this->btnBottomRight->SetColor( color );
	this->btnThumb->SetColor( color );
}

void CXScrollbar::SetBorderColor( Color color )
{
	this->borderColor = color;
	this->btnTopLeft->SetBorderColor( color );
	this->btnBottomRight->SetBorderColor( color );
	this->btnThumb->SetBorderColor( color );
}

bool CXScrollbar::IsDragging()
{
	return bDrag;
}

void CXScrollbar::SetMinMax( int min, int max )
{
	this->iMin = min;
	this->iMax = max;
}

int CXScrollbar::GetMin()
{
	return iMin;
}

int CXScrollbar::GetMax()
{
	return iMax;
}

vec2i CXScrollbar::GetMinMax()
{
	return vec2i(iMin, iMax);
}

void CXScrollbar::SetValue( int value )
{
	this->iValue = value;
}

int CXScrollbar::GetValue()
{
	return iValue;
}

void CXScrollbar::OnRender()
{
	if ( GetVisible() )
	{
		makeAbsPos();
		if ( orientation == EScrollOrientation::VERTICAL )
		{
			pRender->DrawRect( vAbs, size, bgColor );
			pRender->DrawBox( vAbs, size, 1.0f, borderColor );

			btnTopLeft->SetPos( { vAbs.x, vAbs.y } );
			btnTopLeft->OnRender();

			btnBottomRight->SetPos( { vAbs.x, vAbs.y + size.y - btnTopLeft->GetSize().y } );
			btnBottomRight->OnRender();

			CalculateThumbPos();
			btnThumb->OnRender();
		}
		else
		{

		}
	}
}

void CXScrollbar::OnMouseDown( uint button, float x, float y )
{
	if ( btnTopLeft->PointIntersect( x, y ) )
	{
		iValue--;
		if ( iValue < 0 )
			iValue = 0;
		return;
	}
	else if ( btnBottomRight->PointIntersect( x, y ) )
	{
		iValue++;
		if ( iValue > iMax )
			iValue = iMax;
		return;
	}
	else if ( btnThumb->PointIntersect( x, y ) )
	{
		bDrag = true;
	}
	else
	{
		CalculateValue( x, y );
	}
}

void CXScrollbar::OnMouseUp( uint button, float x, float y )
{
		bDrag = false;
}

void CXScrollbar::OnMouseMove( float x, float y )
{
	if ( bDrag )
	{
		if ( orientation == EScrollOrientation::VERTICAL )
		{
			CalculateValue( x, y );
		}
		else
		{

		}
	}
}

void CXScrollbar::OnMouseWheel( WPARAM wParam, LPARAM lParam )
{
	int delta = GET_WHEEL_DELTA_WPARAM( wParam );
	SetValue( GetValue() - (int)( delta / 120.0f ) );
	if ( iValue < iMin )
		iValue = iMin;
	if ( iValue > iMax )
		iValue = iMax;
}

void CXScrollbar::OnKeyDown( WPARAM key, LPARAM extended )
{
}

void CXScrollbar::OnKeyUp( WPARAM key, LPARAM extended )
{
}

void CXScrollbar::CalculateValue( float x, float y )
{
	makeAbsPos();
	int value = 0;
	float thumbHeight = btnThumb->GetSize().y;
	float delta = 0, delta2 = 0;
	for ( ; value < iMax; value++ )
	{
		delta = ( vAbs.y + btnTopLeft->GetSize().y + thumbHeight * value );
		delta2 = ( vAbs.y + btnTopLeft->GetSize().y + ( thumbHeight * value ) + thumbHeight );
		if ( y >= delta && y <= delta2 )
			break;
	}
	iValue = value;
}

void CXScrollbar::CalculateThumbPos()
{
	makeAbsPos();
	auto thumbHeight = size.y - ( btnTopLeft->GetSize().y * 2 );
	thumbHeight /= iMax + 1;
	btnThumb->SetSize( { size.x, thumbHeight } );
	btnThumb->SetPos( { vAbs.x, vAbs.y + btnTopLeft->GetSize().y + ( thumbHeight * iValue ) } );

}
