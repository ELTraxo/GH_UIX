#include "stdafx.h"
#include "Sprite.h"



CSprite::CSprite( DevicePtr pDevice )
{
	this->pDevice = pDevice;
	pSprite = nullptr;
	D3DXCreateSprite( pDevice, &pSprite );
}


CSprite::~CSprite()
{
	safe_release( pSprite );
}

SpritePtrDX9 CSprite::GetSprite()
{
	return pSprite;
}

void CSprite::Draw( TexturePtr pTexture )
{
	auto pos = pTexture->GetPos();
	auto size = pTexture->GetSize();

	vec3f p3 = { pos.x, pos.y, 1.0f };
	vec2f c2 = { pos.x + (size.x / 2), pos.y + (size.y / 2) };

	D3DXMATRIX mTransform;
	pSprite->Begin( 0 );

	D3DXMatrixIdentity( &mTransform );
	
	D3DXMatrixTransformation2D(
		&mTransform,
		&c2.ToDX9Vector(), 0,
		&pTexture->GetScale().ToDX9Vector(),
		&c2.ToDX9Vector(),
		pTexture->GetRotation(),
		0 );

	pSprite->SetTransform( &mTransform );

	pSprite->Draw( pTexture->GetTexture(), 0, 0, &p3.ToDX9Vector(), 0xFFFFFFFF );
	pSprite->End();
}
