#pragma once
#include "Renderable.h"
#include "Sprite.h"

using FontPtrDX9 = LPD3DXFONT;

class CFont : public std::enable_shared_from_this<CFont>
{
	DevicePtr pDevice;
	FontPtrDX9 pFont;
	tstring sFace;
	int height;
	int width;
	int weight;
	bool isItalic;

public:
	CFont( DevicePtr pDevice, tstring sFontFace );
	~CFont();

	DevicePtr GetDevice();
	FontPtrDX9 GetFont();

	tstring GetFace();
	void SetHeight( int height );
	int GetHeight();
	void SetWidth( int width );
	int GetWidth();
	void SetWeight( int weight );
	int GetWeight();
	void SetItalic( bool isItalic );
	bool GetItalic();

	RECT GetStringRect( tstring str );
	uint GetStringWidth( tstring str );

	bool Create();

	void Draw( tstring str, vec2f pos, DWORD format, Color color );
	void Draw( tstring str, vec2f pos, DWORD format, LPRECT pRect, Color color );
	void Draw( tstring str, vec2f pos, DWORD format, LPRECT pRect, Color color, SpritePtr pSprite );
	
};

using Font = CFont;
using FontPtr = std::shared_ptr<Font>;
#define MakeFontPtr(pDevice, sFontFace) \
std::make_shared<Font>(pDevice, sFontFace)

using FontPtrMap = std::map<uint, FontPtr>;
using FontIDMap = std::map<tstring, uint>;

class CFontManager
{
	static bool bInitialized;
	static FontPtrMap fonts;
	static bool GetSystemFont( DevicePtr pDevice );
public:
	static void Initialize( DevicePtr pDevice );
	static FontPtr GetFontPtrByID( uint id );
};