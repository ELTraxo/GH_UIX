#include "stdafx.h"
#include "XButton.h"

CXButton::CXButton( RenderPtr pRender )
	:
	CXControl( pRender )
{
	this->pLabel = MakeLabelPtr( pRender );
	this->pLabel->SetFormat( DT_CENTER | DT_VCENTER );
	this->bDepressed = false;
	this->pCallback = nullptr;
	this->pDataBC = nullptr;
	this->iCallbackResult = 0;
}
	
CXButton::~CXButton()
{
}

LabelPtr CXButton::GetLabel()
{
	return pLabel;
}

void CXButton::SetUnpressedTexture( TexturePtr pTexture )
{
	this->pUnpressedTexture = pTexture;
	if ( !this->pTexture )
		this->pTexture = pTexture;
}

TexturePtr CXButton::GetUnpressedTexture( TexturePtr pTexture )
{
	return pUnpressedTexture;
}

void CXButton::SetDepressedTexture( TexturePtr pTexture )
{
	this->pDepressedTexture = pTexture;
}

TexturePtr CXButton::GetDepressedTexture( TexturePtr pTexture )
{
	return pDepressedTexture;
}

void CXButton::SetCallbackData( void * pData )
{
	this->pDataBC = pData;
}

void CXButton::SetButtonCallback( ButtonCallback pCallback )
{
	this->pCallback = pCallback;
}

int CXButton::GetCallbackResult()
{
	return iCallbackResult;
}

void CXButton::SetText( const tstring & sText )
{
	this->pLabel->SetText( sText );
}

tstring CXButton::GetText()
{
	return pLabel->GetText();
}

void CXButton::SetBorderWidth( float width )
{
	this->borderWidth = width;
}

float CXButton::GetBorderWidth()
{
	return borderWidth;
}

void CXButton::OnRender()
{
	makeAbsPos();

	if ( !pTexture )
	{
		pRender->DrawRect( vAbs, size, bgColor );
		pRender->DrawBox( vAbs, size, 1.0f, borderColor );
	}
	else
	{
		if ( !bDepressed )
			pTexture = pUnpressedTexture;
		else
			pTexture = pDepressedTexture;

		if ( !bDepressed && isHot )
			pTexture = pHotTexture;

		pTexture->SetPos( vAbs );
		SetSize( pTexture->GetSize() );
		pRender->DrawTexture(pTexture);
	}

	pLabel->SetRectAbs( this->GetRectAbs() );
	pLabel->OnRender();
}

void CXButton::OnMouseMove( float x, float y )
{
	SetHot( shared_from_this() );
}

void CXButton::OnMouseDown( uint button, float x, float y )
{
	this->bDepressed = true;
	if ( pCallback )
		iCallbackResult = pCallback( pDataBC );
}

void CXButton::OnMouseUp( uint button, float x, float y )
{
	this->bDepressed = false;
}

void CXButton::OnKeyDown( WPARAM key, LPARAM extended )
{
}

void CXButton::OnKeyUp( WPARAM key, LPARAM extended )
{
}
