#pragma once
#include "Texture.h"

using SpritePtrDX9 = LPD3DXSPRITE;

class CSprite
{
	DevicePtr pDevice;
	SpritePtrDX9 pSprite;
public:
	CSprite( DevicePtr pDevice );
	~CSprite();
	SpritePtrDX9 GetSprite();
	void Draw( TexturePtr pTexture );
};

using Sprite = CSprite;
using SpritePtr = std::shared_ptr<Sprite>;
#define MakeSpritePtr(pDevice) \
std::make_shared<Sprite>(pDevice);