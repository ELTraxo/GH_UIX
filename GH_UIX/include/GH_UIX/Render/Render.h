#pragma once
#include "RenderList.h"


class CRender
{
	HWND hWnd;
	DevicePtr pDevice;
	StateBlockPtr pStateBlock;
	RenderList renderList;
	SpritePtr pSprite;
public:
	CRender( DevicePtr pDevice );
	~CRender();
	DevicePtr GetDevice();


public: // draw functions
	void DrawTriangle( vec2f p1, vec2f p2, vec2f p3, Color color );
	void DrawRect( vec2f pos, vec2f size, Color color );
	void DrawBox( vec2f pos, vec2f size, float width, Color color );
	void DrawDot( vec2f centerPos, float radius, uint segments, Color color );
	void DrawCircle( vec2f centerPos, float radius, uint segments, Color color );
	void DrawLine( vec2f p1, vec2f p2, Color color );

	void DrawTexture( TexturePtr pTexture );

	void DrawString( FontPtr pFont, tstring sStr, vec2f pos, Color color );
	void DrawString( FontPtr pFont, tstring sStr, vec2f pos, DWORD format, Color color );
	void DrawString( FontPtr pFont, tstring sStr, vec2f pos, DWORD format, Color color, const RECT& rect, bool bUseRect=false );
	void DrawString( TextPtr pText );
	
	void Render();

private:
	void PreRender();
	void PostRender();



public: // d3d init & cleanup functions
	static LPDIRECT3D9 pD3d;
	static LPDIRECT3DSWAPCHAIN9 pSwapchain;
	static DevicePtr pDeviceDX9;
	static DevicePtr CreateDeviceDX9( HWND hWnd );

	static void Cleanup();
};

using Render = CRender;
using RenderPtr = std::shared_ptr<Render>;
#define MakeRendererPtr(pDevice) \
std::make_shared<Render>(pDevice)