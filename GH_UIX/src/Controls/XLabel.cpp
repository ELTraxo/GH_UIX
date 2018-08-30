#include "stdafx.h"
#include "XLabel.h"



CXLabel::CXLabel( RenderPtr pRender )
	:
	CXControl( pRender )
{
	this->dwFormat = DT_LEFT | DT_NOCLIP;
	this->bgColor = 0xFFFFFFFF;
}


CXLabel::~CXLabel()
{
}

void CXLabel::SetText( const tstring & sText )
{
	this->sText = sText;
}

tstring CXLabel::GetText()
{
	return sText;
}

void CXLabel::SetFormat( DWORD dwFormat )
{
	this->dwFormat = dwFormat;
}

DWORD CXLabel::GetFormat()
{
	return dwFormat;
}

RECT CXLabel::GetRect()
{
	return pFont->GetStringRect( sText );
}

void CXLabel::OnRender()
{
	makeAbsPos();
	if(bUseRect)
		pRender->DrawString( this->pFont, this->sText, vAbs, dwFormat, this->bgColor, rect, true );
	else
		pRender->DrawString( this->pFont, this->sText, vAbs, dwFormat, this->bgColor );
}
