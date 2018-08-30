#include "stdafx.h"
#include "XStateControl.h"

CXStateControl::CXStateControl( RenderPtr pRender )
	:
	CXControl(pRender)
{
	pLabel = MakeLabelPtr( pRender );
	bState = false;
	padding = 5.0f;
	sizeState = 10.0f;
	size.y = 10.0f;
}

CXStateControl::~CXStateControl()
{
}

void CXStateControl::SetText(const tstring & sText )
{
	pLabel->SetText( sText );
	size.x = padding + sizeState.x + pLabel->GetFont()->GetStringWidth( sText );
}

tstring CXStateControl::GetText()
{
	return pLabel->GetText();
}

void CXStateControl::SetStateSize( const vec2f & size )
{
	this->sizeState = size;
	this->size.x = sizeState.x + pLabel->GetWidth() + padding;
	this->size.y = sizeState.y;
}

vec2f CXStateControl::GetStateSize()
{
	return sizeState;
}

void CXStateControl::SetState( bool bState )
{
	this->bState = bState;
}

bool CXStateControl::GetState()
{
	return bState;
}

void CXStateControl::OnMouseMove( float x, float y )
{
	SetHot( shared_from_this() );
}

void CXStateControl::OnMouseDown( uint button, float x, float y )
{
	SetFocused( shared_from_this() );
	bState = !bState;
}

void CXStateControl::OnKeyDown( WPARAM key, WPARAM extended )
{
	if ( isFocused )
	{
		if ( key == VK_SPACE )
			bState = !bState;
	}
}

CXCheckbox::CXCheckbox( RenderPtr pRender )
	:
	CXStateControl(pRender)
{
}

CXCheckbox::~CXCheckbox()
{
}

void CXCheckbox::OnRender()
{
	makeAbsPos();
	pRender->DrawRect( vAbs, sizeState, bgColor );
	pRender->DrawBox( vAbs, sizeState, 1.0f, borderColor );

	if ( bState )
	{
		pRender->DrawRect(vAbs + 3.0f, sizeState + (-4.0f), borderColor);
	}

	pLabel->SetPos( { vAbs.x + sizeState.x + 1.0f, vAbs.y } );
	auto r = GetRectAbs();
	r.left += (int)(sizeState.x + padding);
	r.top += 1;
	r.bottom += 1;
	pLabel->SetRectAbs( r );
	pLabel->SetFormat( DT_LEFT | DT_VCENTER | DT_NOCLIP );
	pLabel->OnRender();
}

CXRadio::CXRadio( RenderPtr pRender )
	:
	CXStateControl(pRender)
{

}

CXRadio::~CXRadio()
{
}

void CXRadio::SetFirstRadio( RadioPtr pRadio )
{
	pFirstRadio = pRadio;
}

RadioPtr CXRadio::GetFirstRadio()
{
	return pFirstRadio;
}

void CXRadio::SetNextRadio( RadioPtr pRadio )
{
	pNextRadio = pRadio;
}

RadioPtr CXRadio::GetNextRadio()
{
	return pNextRadio;
}

void CXRadio::SetPrevRadio( RadioPtr pRadio )
{
	pPrevRadio = pRadio;
}

RadioPtr CXRadio::GetPrevRadio()
{
	return pPrevRadio;
}

void CXRadio::SetSelected( RadioPtr pRadio )
{
	pSelected = pRadio;
}

RadioPtr CXRadio::GetSelected()
{
	return pSelected;
}

void CXRadio::AddRadio( RadioPtr pRadio )
{
	if ( !pFirstRadio )
		pFirstRadio = std::dynamic_pointer_cast<Radio>( shared_from_this() );

	if ( !GetNextRadio() )
	{
		SetNextRadio( pRadio );
		pRadio->SetPrevRadio( std::dynamic_pointer_cast<Radio>( shared_from_this() ) );
		pRadio->SetFirstRadio( pFirstRadio );
	}
	else
	{
		pRadio->SetFirstRadio( pFirstRadio );
		GetNextRadio()->AddRadio( pRadio );
	}


	//if ( pFirstRadio )
	//{
	//	auto next = pFirstRadio->GetNextRadio();
	//	while ( next )
	//	{
	//		auto temp = next->GetNextRadio();
	//		if ( !temp )
	//			break;
	//		next = temp;
	//	}
	//	next->SetNextRadio( pRadio );
	//	pRadio->SetPrevRadio( next );
	//	pRadio->SetFirstRadio( pRadio );
	//}
	//else
	//{
	//	pFirstRadio = std::dynamic_pointer_cast<Radio>( shared_from_this() );
	//	pFirstRadio->SetNextRadio( pRadio );
	//	pRadio->SetPrevRadio( pFirstRadio );
	//	pRadio->SetFirstRadio( pFirstRadio );
	//}
}


void CXRadio::OnRender()
{
	makeAbsPos();
	pRender->DrawCircle( vAbs + ( sizeState.x / 2 ), ( sizeState.x / 2 ), 12, borderColor );
	
	if(bState)
		pRender->DrawDot( vAbs + ( sizeState.x / 2 ), ( sizeState.x / 2 ) - 2.0f, 5, borderColor );
	auto r = GetRectAbs();
	r.left += (int)(sizeState.x + padding);
	pLabel->SetRectAbs( r );
	pLabel->SetFormat( DT_LEFT | DT_VCENTER );
	pLabel->OnRender();
}

void CXRadio::OnMouseDown( uint button, float x, float y )
{

	/*if ( pFirstRadio )
		pFirstRadio->OnSelect( shared_from_this() );
	else
		bState = !bState;*/
	pFirstRadio->OnSelect( shared_from_this() );
}

void CXRadio::OnSelect( ControlPtr pRadio )
{
	if ( pRadio.get() == this )
		bState = true;
	else
		bState = false;
	pSelected = std::dynamic_pointer_cast<Radio>( pRadio );
	if(GetNextRadio())
		GetNextRadio()->OnSelect( pRadio );
}
