#include "stdafx.h"
#include "Font.h"

CFont::CFont( DevicePtr pDevice, tstring sFontFace )
{
	this->pDevice = pDevice;
	this->sFace = sFontFace;
	this->height = 0;
	this->width = 0;
	this->weight = 0;
	this->isItalic = 0;
	this->pFont = nullptr;
}

CFont::~CFont()
{
}

DevicePtr CFont::GetDevice()
{
	return pDevice;
}

FontPtrDX9 CFont::GetFont()
{
	return pFont;
}

tstring CFont::GetFace()
{
	return sFace;
}

void CFont::SetHeight( int height )
{
	this->height = height;
}

int CFont::GetHeight()
{
	return height;
}

void CFont::SetWidth( int width )
{
	this->width = width;
}

int CFont::GetWidth()
{
	return width;
}

void CFont::SetWeight( int weight )
{
	this->weight = weight;
}

int CFont::GetWeight()
{
	return weight;
}

void CFont::SetItalic( bool isItalic )
{
	this->isItalic = isItalic;
}

bool CFont::GetItalic()
{
	return isItalic;
}

RECT CFont::GetStringRect( tstring str )
{
	RECT r{ 0 };
	pFont->DrawText( NULL, str.c_str(), -1, &r, DT_CALCRECT, 0x00FFFFFF );
	return r;
}

uint CFont::GetStringWidth( tstring str )
{
	__int3264 i = 0;

	do
	{
		i = str.find( _T( " " ), i );
		if(i >= 0 )
			str.replace( i, 1, _T( "i" ) );
	} while ( i >= 0 );
	RECT r{ 0 };
	pFont->DrawText( NULL, str.c_str(), -1, &r, DT_CALCRECT, 0x00FFFFFF );
	return uint(r.right);
}

bool CFont::Create()
{
	HRESULT result = D3DXCreateFont( this->pDevice,
									 this->height,
									 this->width,
									 this->weight,
									 0,
									 this->isItalic,
									 DEFAULT_CHARSET,
									 0,
									 ANTIALIASED_QUALITY,
									 DEFAULT_PITCH | FF_DONTCARE,
									 this->sFace.c_str(),
									 &this->pFont );

	if(result != S_OK)
	{
		tstring error = _T( "Failed to create font \"" );
		error += sFace;
		error += _T("\"...");
		ErrorMsgBox( error );
		return false;
	}
	return true;
}

void CFont::Draw( tstring str, vec2f pos, DWORD format, Color color )
{
	if(pFont)
	{
		RECT r{ 0 };
		pFont->DrawText( NULL, str.c_str(), -1, &r, DT_CALCRECT | format, 0x00FFFFFF );

		r.left += (int)pos.x;
		r.right += (int)pos.x;
		r.top += (int)pos.y;
		r.bottom += (int)pos.y;

		Draw( str, pos, format, &r, color );
	}
}

void CFont::Draw( tstring str, vec2f pos, DWORD format, LPRECT pRect, Color color )
{
	Draw( str, pos, format, pRect, color, nullptr );
}

void CFont::Draw( tstring str, vec2f pos, DWORD format, LPRECT pRect, Color color, SpritePtr pSprite )
{
	if(pFont)
		pFont->DrawText( 
		(pSprite) ? pSprite->GetSprite() : nullptr, 
			str.c_str(), 
			-1, 
			pRect, 
			format, 
			color );
}

bool CFontManager::bInitialized = false;
FontPtrMap CFontManager::fonts;
bool CFontManager::GetSystemFont( DevicePtr pDevice )
{
	NONCLIENTMETRICS ncm{ 0 };
	ncm.cbSize = sizeof( ncm );
	
	if(!SystemParametersInfo( SPI_GETNONCLIENTMETRICS, sizeof( ncm ), &ncm, 0 ))
	{
		LastErrorMsgBox( _T( "Failed to grab the system font...\n" ) );
		return false;
	}

	LOGFONT lf{ 0 };
	lf = ncm.lfCaptionFont;
	
	auto pFont = MakeFontPtr( pDevice, lf.lfFaceName );
	pFont->SetHeight( lf.lfHeight );
	pFont->SetWeight( lf.lfWeight );
	pFont->Create();
	CFontManager::fonts[ 0 ] = pFont;
	return true;
}

void CFontManager::Initialize( DevicePtr pDevice )
{
	if(!bInitialized)
	{
		bInitialized = true;
		CFontManager::GetSystemFont( pDevice );
	}
}

FontPtr CFontManager::GetFontPtrByID( uint id )
{
	return fonts[id];
}
