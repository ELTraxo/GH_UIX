#include "stdafx.h"
#include "XSlider.h"


CXSlider::CXSlider( RenderPtr pRender )
	:
	CXControl( pRender )
{
	pThumb = MakeButtonPtr( pRender );
	pThumb->SetColor( 0xFF404040 );
	pThumb->SetBorderColor( 0xFFA0A0A0 );
	thumbWidth = 15.0f;
	pLabel = MakeLabelPtr( pRender );
	pLabel->SetFormat( DT_CENTER | DT_VCENTER | DT_NOCLIP );
	pLabel->SetText( _T( "0.0" ) );
	bMovingSlider = false;
}

CXSlider::~CXSlider()
{
}

void CXSlider::SetSize( vec2f size )
{
	this->size = size;
	SetThumbSize( { thumbWidth, size.y - 1.0f } );
}

void CXSlider::SetThumbWidth( float width )
{
	this->thumbWidth = width;
}

float CXSlider::GetThumbWidth()
{
	return thumbWidth;
}

void CXSlider::SetThumbSize( vec2f size )
{
	this->thumbSize = size;
	pThumb->SetSize( size );
}

void CXSlider::SetThumbColor( Color color )
{
	pThumb->SetColor( color );
}

Color CXSlider::GetThumbColor()
{
	return pThumb->GetColor();
}

void CXSlider::SetThumbBorderColor( Color color )
{
	pThumb->SetBorderColor( color );
}

Color CXSlider::GetThumbBorderColor()
{
	return pThumb->GetBorderColor();
}

void CXSlider::SetMinMax( float min, float max )
{
	SetMinMax( { min, max } );
}

void CXSlider::SetMinMax( vec2f minmax )
{
	this->vMinMax = minmax;
}

vec2f CXSlider::GetMinMax()
{
	return vMinMax;
}

void CXSlider::SetValue( float value )
{
	this->fValue = value;
	UpdateThumbPosition();
	tstring buf( 16, 0 );
	swprintf_s( &buf[ 0 ], 16, _T( "%.2f" ), value);
	pLabel->SetText( buf );
}

float CXSlider::GetValue()
{
	return fValue;
}

void CXSlider::OnRender()
{
	makeAbsPos();
	pRender->DrawRect( vAbs, size, bgColor );
	pThumb->SetPos( { vAbs.x + xOffset, vAbs.y + 1.0f } );
	pThumb->OnRender();
	pRender->DrawBox( vAbs, size, 1.0f, borderColor );


	auto r = GetRectAbs();
	r.top += 1;
	pLabel->SetRectAbs( r );
	pLabel->OnRender();
}

void CXSlider::OnMouseMove( float x, float y )
{
	auto center = pThumb->GetCenter();
	if ( bMovingSlider )
		UpdateValueFromPoint( x, y );
}

void CXSlider::OnMouseDown( uint button, float x, float y )
{
	if ( pThumb->PointIntersect( x, y ) )
	{
		SetMovingControl( shared_from_this() );
		bMovingSlider = true;
	}
	UpdateValueFromPoint( x, y );
}

void CXSlider::OnMouseUp( uint button, float x, float y )
{
	if ( bMovingSlider )
	{
		bMovingSlider = false;
		SetMovingControl( nullptr );
	}
}

void CXSlider::UpdateThumbPosition()
{
	// get width of control
	auto w = GetWidth() - thumbWidth;
	//w += thumbWidth * 2;
	// subtract max from min
	auto d = vMinMax.y - vMinMax.x;
	//divide width by diff
	d = fValue / d;
	// multiple by value (maybe)
	w *= d;

	xOffset = w/* - ( thumbWidth / 2)*/;
}

void CXSlider::UpdateValueFromPoint( float x, float y )
{
	makeAbsPos();
	
	auto w = GetWidth() - thumbWidth;
	auto v = (x - vAbs.x) - ( thumbWidth / 2 );
	v /= w;
	if ( v < vMinMax.x )
		v = vMinMax.x;
	if ( v > vMinMax.y )
		v = vMinMax.y;
	SetValue( v );
}
