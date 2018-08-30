#include "stdafx.h"
#include "XGroupbox.h"
#include "XLabel.h"

CXGroupbox::CXGroupbox( RenderPtr pRender )
	:
	CXControlContainer(pRender)
{
	pLabel = MakeLabelPtr( pRender );
	labelEdgeOffset = 10.0f;
	labelPadding = 5.0f;
}


CXGroupbox::~CXGroupbox()
{
}

void CXGroupbox::SetLabelPosition( ELabelPosition labelPosition )
{
	this->labelPosition = labelPosition;
}

ELabelPosition CXGroupbox::GetLabelPosition()
{
	return labelPosition;
}

void CXGroupbox::SetText( const tstring & sText )
{
	pLabel->SetText( sText );
}

tstring CXGroupbox::GetText()
{
	return pLabel->GetText();
}

void CXGroupbox::SetTextColor( Color color )
{
	pLabel->SetColor( color );
}

Color CXGroupbox::GetTextColor()
{
	return pLabel->GetColor();
}

void CXGroupbox::SetLabelPadding( float padding )
{
	this->labelPadding = padding;
}

float CXGroupbox::GetLabelPadding()
{
	return labelPadding;
}

void CXGroupbox::SetEdgeOffset( float offset )
{
	this->labelEdgeOffset = offset;
}

float CXGroupbox::GetEdgeOffset()
{
	return labelEdgeOffset;
}

void CXGroupbox::OnRender()
{
	makeAbsPos();
	auto fontPos = vAbs;
	vAbs.y += ( abs(pFont->GetHeight()) / 2 );
	pRender->DrawRect( vAbs, size, bgColor );
	pRender->DrawLine( vAbs, { vAbs.x + labelEdgeOffset, vAbs.y }, borderColor );
	pRender->DrawLine( vAbs, { vAbs.x, vAbs.y + size.y }, borderColor );
	pRender->DrawLine( { vAbs.x + size.x, vAbs.y }, { vAbs.x + size.x, vAbs.y + size.y }, borderColor );
	pRender->DrawLine( { vAbs.x, vAbs.y + size.y }, { vAbs.x + size.x, vAbs.y + size.y }, borderColor );
	pRender->DrawLine( { vAbs.x + labelEdgeOffset + ( labelPadding * 2 ) + pFont->GetStringWidth( pLabel->GetText() ), vAbs.y }, { vAbs.x + size.x, vAbs.y }, borderColor );
	float negYOffset = (float)abs( (double)pLabel->GetRect().bottom ) / 2;
	pLabel->SetPos( { vAbs.x + labelEdgeOffset + labelPadding, fontPos.y /*vAbs.y -  negYOffset*/} );
	pLabel->OnRender();
}