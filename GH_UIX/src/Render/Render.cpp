#include "stdafx.h"
#include "Render.h"

LPDIRECT3D9 CRender::pD3d = nullptr;
LPDIRECT3DSWAPCHAIN9 CRender::pSwapchain = nullptr;
DevicePtr CRender::pDeviceDX9 = nullptr;

CRender::CRender( DevicePtr pDevice )
{
	this->pDevice = pDevice;
	this->hWnd = NULL;
	this->pStateBlock = nullptr;
	this->pSprite = std::make_shared<Sprite>( pDevice );
	CFontManager::Initialize( pDevice );
}

CRender::~CRender()
{
	safe_release( pStateBlock );
}

DevicePtr CRender::GetDevice()
{
	return pDevice;
}

void CRender::DrawTriangle( vec2f p1, vec2f p2, vec2f p3, Color color )
{
	Vertex vec[] = {
		{ p1.x, p1.y, 1.0f, 1.0f, color },
		{ p2.x, p2.y, 1.0f, 1.0f, color },
		{ p3.x, p3.y, 1.0f, 1.0f, color }
	};

	renderList.AddRenderable( std::make_shared<Primitive>( pDevice, EPrimType::TF, vec, (uint)( vert_count( vec ) ) ) );
}

void CRender::DrawRect( vec2f pos, vec2f size, Color color )
{
	Vertex vec[] = {
		{ pos.x,			pos.y,			1.0f, 1.0f, color },
		{ pos.x + size.x,	pos.y,			1.0f, 1.0f, color },
		{ pos.x + size.x,	pos.y + size.y, 1.0f, 1.0f, color },
		
		{ pos.x,			pos.y + size.y, 1.0f, 1.0f, color },
		{ pos.x,			pos.y,			1.0f, 1.0f, color }
	};

	renderList.AddRenderable( std::make_shared<Primitive>( pDevice, EPrimType::TF, vec, (uint)(vert_count( vec )) ) );
}

void CRender::DrawBox( vec2f pos, vec2f size, float width, Color color )
{
	DrawRect( pos, { size.x, width }, color );
	DrawRect( pos, { width, size.y }, color );
	
	DrawRect( { pos.x, pos.y + size.y }, { size.x, width }, color );
	DrawRect( { pos.x + size.x, pos.y }, { width, size.y + width }, color );
}

void CRender::DrawDot( vec2f centerPos, float radius, const uint segments, Color color )
{
	float x = centerPos.x;
	float y = centerPos.y;

	float theta = ( D3DX_PI * 2 ) - 0.001f;
	float delta = theta / segments;
	float newTheta = 0;
	
	Vertex * vec = new Vertex[ (segments) + 2 ]{ 0 };
	vec[ 0 ] = { x, y, 1.0f, 1.0f, color };
	
	for(uint i = 1; i < segments + 1; i++)
	{
		vec[ i ] = { x + cosf( theta )*radius, y + sinf( theta )*radius, 1.0f, 1.0f, color };
		theta -= delta;
	}

	vec[ segments + 1 ] = vec[ 1 ];
	
	renderList.AddRenderable( MakePrimPtr( pDevice, EPrimType::TF, vec, segments + 2 ) );
	delete vec;
}

void CRender::DrawCircle( vec2f centerPos, float radius, uint segments, Color color )
{
	float x = centerPos.x;
	float y = centerPos.y;

	float theta = D3DX_PI * 2;
	float delta;
	Vertex * vec = new Vertex[ segments + 2 ]{ 0 };
	vec[ 0 ] = { x + cosf( theta )*radius, y + sinf( theta )*radius, 1.0f, 1.0f, color };

	for(int i = segments; i > 0; i--)
	{
		delta = theta / i;
		float newTheta = theta - delta;
		vec[ i ] = { x + cosf( newTheta )*radius, y + sinf( newTheta )*radius, 1.0f, 1.0f, color };
		theta = newTheta;
	}
	vec[ segments + 1 ] = { x + cosf( theta )*radius, y + sinf( theta )*radius, 1.0f, 1.0f, color };
	renderList.AddRenderable( MakePrimPtr( pDevice, EPrimType::LS, vec, (segments + 2) ) );
	delete vec;
}

void CRender::DrawLine( vec2f p1, vec2f p2, Color color )
{
	Vertex vec[] =
	{
		{ p1.x, p1.y, 1.0f, 1.0f, color },
		{ p2.x, p2.y, 1.0f, 1.0f, color }
	};
	renderList.AddRenderable( MakePrimPtr( pDevice, EPrimType::LL, vec, (uint)( vert_count( vec ) ) ) );
}

void CRender::DrawTexture( TexturePtr pTexture )
{
	renderList.AddRenderable( pTexture );
}

void CRender::DrawString( FontPtr pFont, tstring sStr, vec2f pos, Color color )
{
	DrawString( pFont, sStr, pos, 0, color );
}

void CRender::DrawString( FontPtr pFont, tstring sStr, vec2f pos, DWORD format, Color color )
{
	DrawString( pFont, sStr, pos, format, color, RECT{0} );
}

void CRender::DrawString( FontPtr pFont, tstring sStr, vec2f pos, DWORD format, Color color, const RECT& rect, bool bUseRect )
{
	auto pText = MakeTextPtr( pFont, sStr );
	pText->SetPos( pos );
	pText->SetColor( color );
	pText->SetFormat( format );
	pText->SetRect( rect, bUseRect );
	renderList.AddRenderable( pText );
}

void CRender::DrawString( TextPtr pText )
{
	renderList.AddRenderable( pText );
}

void CRender::Render()
{
	PreRender();
	auto rl = renderList.GetList();

	for(auto r : rl)
	{
		auto primType = r->GetType();
		if (primType == PRIMITIVE)
		{
			auto pPrim = reinterpret_cast<Primitive*>(r.get());
			pPrim->Render();
		}
		else if (primType == TEXTURE)
		{
			TexturePtr pTexture = std::dynamic_pointer_cast<Texture>(r);
			pSprite->Draw( pTexture );
		}
		else
		{
			TextPtr pText = std::dynamic_pointer_cast<Text>(r);
			pText->Render();
		}
	}
	PostRender();
}

void CRender::PreRender()
{
	if(!pStateBlock)
		pDevice->CreateStateBlock( D3DSBT_ALL, &pStateBlock );

	pStateBlock->Capture();

	pDevice->SetFVF( UIXFVF );
	pDevice->SetRenderState( D3DRS_ZENABLE, D3DZB_FALSE );
	pDevice->SetRenderState( D3DRS_ALPHABLENDENABLE, TRUE );
	pDevice->SetRenderState( D3DRS_BLENDOP, D3DBLENDOP_ADD );
	pDevice->SetRenderState( D3DRS_SRCBLEND, D3DBLEND_SRCALPHA );
	pDevice->SetRenderState( D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA );	
	pDevice->SetRenderState( D3DRS_CULLMODE, D3DCULL_NONE );
}

void CRender::PostRender()
{
	pStateBlock->Apply();
	renderList.Clear();
}

DevicePtr CRender::CreateDeviceDX9( HWND hWnd )
{
	if ( !pDeviceDX9 )
	{
		pD3d = Direct3DCreate9( D3D_SDK_VERSION );
		D3DPRESENT_PARAMETERS pp{ 0 };
		pp.Windowed = TRUE;
		pp.SwapEffect = D3DSWAPEFFECT_DISCARD;
		pp.hDeviceWindow = hWnd;

		pD3d->CreateDevice(
			D3DADAPTER_DEFAULT,
			D3DDEVTYPE_HAL,
			hWnd,
			D3DCREATE_SOFTWARE_VERTEXPROCESSING,
			&pp,
			&pDeviceDX9
		);

		if ( !pDeviceDX9 )
		{
			ErrorMsgBox( _T( "Failed to create IDirect3DDevice9..." ) );
			return nullptr;
		}
	}
	return pDeviceDX9;
}



void CRender::Cleanup()
{
	safe_release( pDeviceDX9 );
	safe_release( pD3d );
}
