#pragma once
#include "XLabel.h"

using ButtonCallback = int(*)( void* );

class CXButton : public CXControl
{
	LabelPtr pLabel;
	float borderWidth;
	bool bDepressed;
	TexturePtr pUnpressedTexture;
	TexturePtr pDepressedTexture;
	ButtonCallback pCallback;
	void* pDataBC;
	int iCallbackResult;
public:
	CXButton( RenderPtr pRender );
	~CXButton();

	LabelPtr GetLabel();

	void SetUnpressedTexture( TexturePtr pTexture );
	TexturePtr GetUnpressedTexture( TexturePtr pTexture );
	void SetDepressedTexture( TexturePtr pTexture );
	TexturePtr GetDepressedTexture( TexturePtr pTexture );

	void SetCallbackData( void* pData );
	void SetButtonCallback( ButtonCallback pCallback );
	int GetCallbackResult();

	void SetText( const tstring & sText );
	tstring GetText();
	void SetBorderWidth( float width );
	float GetBorderWidth();

	void OnRender();
	void OnMouseMove( float x, float y );
	void OnMouseDown( uint button, float x, float y );
	void OnMouseUp( uint button, float x, float y );
	void OnKeyDown( WPARAM key, LPARAM extended );
	void OnKeyUp( WPARAM key, LPARAM extended );

};


#define MakeButtonPtr(pRender) std::make_shared<Button>(pRender);