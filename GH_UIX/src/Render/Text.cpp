#include "stdafx.h"
#include "Text.h"

CText::CText( FontPtr pFont, tstring text )
{
	this->renderType = TEXT;
	this->pDevice = pFont->GetDevice();
	this->pFont = pFont;
	
	this->sText = text;
	pos = 0;
	format = DT_LEFT;
	color = 0xFF000000;
	bUseRect = false;
	rect = { 0 };
	pSprite = nullptr;
}

CText::~CText()
{
}

void CText::SetText( tstring text )
{
	this->sText = text;
	//if ( pFont )
	//	pFont->GetFont()->PreloadText( text.c_str(), -1 );
}

tstring CText::GetText()
{
	return sText;
}

void CText::SetPos( const vec2f & pos )
{
	this->pos = pos;
}

vec2f CText::GetPos()
{
	return pos;
}

void CText::SetFormat( const DWORD format )
{
	this->format = format;
}

DWORD CText::GetFormat()
{
	return format;
}

void CText::SetColor( const Color color )
{
	this->color = color;
}

Color CText::GetColor() const
{
	return color;
}

void CText::SetRect( const RECT & rect, bool bUseRect )
{
	this->bUseRect = bUseRect;
	this->rect.left = rect.left;
	this->rect.right = rect.right;
	this->rect.top = rect.top;
	this->rect.bottom = rect.bottom;
}

RECT CText::GetRect() const
{
	return rect;
}

void CText::SetSprite( SpritePtr pSprite )
{
	this->pSprite = pSprite;
}

SpritePtr CText::GetSprite()
{
	return pSprite;
}

bool CText::Render()
{
	if(pFont)
	{
		if(pFont->GetFont())
		{
			auto pFontDX9 = pFont->GetFont();
			if(!bUseRect)
			{
				pFontDX9->DrawText( nullptr,
									sText.c_str(), 
									-1, 
									&rect, 
									DT_CALCRECT | format, 
									0x00FFFFFF );
			
				uint strWidth = 0;
				if ( format & DT_CENTER )
					strWidth = pFont->GetStringWidth( sText );

				rect.left += (int)pos.x - (int)(strWidth / 2);
				rect.right += (int)pos.x + (int)(strWidth / 2);
				rect.top += (int)pos.y;
				rect.bottom += (int)pos.y;
			}

			pFontDX9->DrawText( (pSprite) ? pSprite->GetSprite() : nullptr,
								sText.c_str(),
								-1,
								&rect,
								format,
								color );
		}
		else
		{
			tstring error = _T( "The font object attached to the following string \n\
								has not beed initialized properly:\n" );
			error += sText;
			ErrorMsgBox( error );
			return false;
		}
	}
	else
	{
		tstring error = _T( "No font has been assigned to the following text:\n" );
		error += sText;
		ErrorMsgBox( error );
		return false;
	}
	return true;
}
