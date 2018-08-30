#pragma once
#include "Renderable.h"
#include "Font.h"

class CText	: public CRenderable
{
	FontPtr pFont;
	tstring sText;
	vec2f pos;
	DWORD format;
	Color color;
	bool bUseRect;
	RECT rect;
	SpritePtr pSprite;

public:
	CText( FontPtr pFont, tstring text );
	~CText();

	void SetText( tstring text );
	tstring GetText();
	void SetPos( const vec2f & pos );
	vec2f GetPos();
	void SetFormat( const DWORD format );
	DWORD GetFormat();
	void SetColor( const Color color );
	Color GetColor() const;
	void SetRect( const RECT& rect, bool bUseRect=false );
	RECT GetRect() const;
	void SetSprite( SpritePtr pSprite );
	SpritePtr GetSprite();


	bool Render();
};

using Text = CText;
using TextPtr = std::shared_ptr<Text>;
#define MakeTextPtr(pFont, text) \
std::make_shared<Text>(pFont, text);