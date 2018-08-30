#pragma once
#include "Renderable.h"
#include "TypesDX9.h"


using TexturePtrDX9 = LPDIRECT3DTEXTURE9;

class CTexture;
using Texture = CTexture;
using TexturePtr = std::shared_ptr<CTexture>;

#define MakeTexturePtr(pDevice) \
std::make_shared<Texture>(pDevice)

#define MakeTexturePtrCopy(pDevice, pTexture) \
std::make_shared<Texture>(pDevice, pTexture)

class CTexture : public CRenderable,
	public std::enable_shared_from_this<CTexture>
{
	vec2f pos;
	vec2f size;
	vec2f scale;
	float rotation;
	TexturePtrDX9 pTexture;
public:
	CTexture( DevicePtr pDevice );
	CTexture( DevicePtr pDevice, TexturePtr pTexture );
	~CTexture();

	bool CreateFromFile( tstring sFilePath );
	TexturePtrDX9 GetTexture();

	void SetPosX( float x );
	void SetPosY( float y );
	void SetPos( float x, float y );
	void SetPos( vec2f pos );
	vec2f GetPos();

	void SetSize( vec2f size );
	vec2f GetSize();

	void SetScale( float x, float y );
	void SetScale( vec2f scale );
	vec2f GetScale();

	void SetRotation( float angle );
	float GetRotation();
};


