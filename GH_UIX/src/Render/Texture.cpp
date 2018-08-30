#include "stdafx.h"
#include "Texture.h"

CTexture::CTexture( DevicePtr pDevice )
{
	this->renderType = TEXTURE;
	this->pDevice = pDevice;
	this->pos = 0;
	this->size = 0;
	this->rotation = 0;
	this->scale = 1.0f;
	pTexture = nullptr;
}

CTexture::CTexture( DevicePtr pDevice, TexturePtr pTexture )
{
	this->renderType = TEXTURE;
	this->pDevice = pDevice;
	this->pos = 0;
	this->size = pTexture->GetSize();
	this->rotation = 0;
	this->scale = 1.0f;
	this->pTexture = pTexture->GetTexture();
}

CTexture::~CTexture()
{
	safe_release( pTexture );
}

bool CTexture::CreateFromFile( tstring sFilePath )
{
	D3DXIMAGE_INFO di{ 0 };
	if ( D3DXGetImageInfoFromFile( sFilePath.c_str(), &di ) != D3D_OK )
	{
		tstring error = _T( "Failed to load image info...\n" );
		error += sFilePath;
		ErrorMsgBox( error );
		return false;
	}

	if ( size == 0.0f )
	{
		size.x = (float)di.Width;
		size.y = (float)di.Height;
	}
	else
	{
		di.Width = (int)size.x;
		di.Height = (int)size.y;
	}


	HRESULT result = D3DXCheckTextureRequirements( pDevice, &di.Width, &di.Height, 0, 0, &di.Format, D3DPOOL_DEFAULT );

	if ( result == S_OK )
	{
		result = D3DXCreateTextureFromFileEx( pDevice,
												sFilePath.c_str(),
												di.Width,
												di.Height,
												0,
												0,
												di.Format,
												D3DPOOL_DEFAULT,
												D3DX_DEFAULT,
												D3DX_DEFAULT,
												0,
												nullptr,
												nullptr,
												&pTexture );
	}
	else
	{
		TexturePtrDX9 pTemp = nullptr;
		result = D3DXCreateTextureFromFileEx( pDevice, 
												sFilePath.c_str(), 
												D3DX_DEFAULT, 
												D3DX_DEFAULT, 
												1, 
												D3DUSAGE_DYNAMIC, 
												di.Format, 
												D3DPOOL_DEFAULT, 
												D3DX_DEFAULT, 
												D3DX_DEFAULT, 
												0, 
												NULL, 
												NULL, 
												&pTemp );
		SurfacePtr pSource = nullptr;
		result = D3DXCreateTexture( pDevice, di.Width, di.Height, 1, D3DUSAGE_DYNAMIC, di.Format, D3DPOOL_DEFAULT, &pTexture );
		if ( result == D3D_OK )
		{
			SurfacePtr pDest = nullptr;
			pTemp->GetSurfaceLevel( 0, &pSource );
			pTexture->GetSurfaceLevel( 0, &pDest );
			result = D3DXLoadSurfaceFromSurface( pDest, NULL, NULL, pSource, NULL, NULL, D3DX_DEFAULT, 0 );
			safe_release( pSource );
			safe_release( pDest );
			safe_release( pTemp );
		}
	}
	
	if( result != D3D_OK)
	{
		tstring error = _T( "Failed to load image for texture...\n" );
		error += sFilePath;
		ErrorMsgBox( error );
		return false;
	}

	return true;
}

TexturePtrDX9 CTexture::GetTexture()
{
	return pTexture;
}

void CTexture::SetPosX( float x )
{
	this->pos.x = x;
}

void CTexture::SetPosY( float y )
{
	this->pos.y = y;
}

void CTexture::SetPos( float x, float y )
{
	SetPos( { x, y } );
}

void CTexture::SetPos( vec2f pos )
{
	this->pos = pos;
}

vec2f CTexture::GetPos()
{
	return pos;
}

void CTexture::SetSize( vec2f size )
{
	this->size = size;
}

vec2f CTexture::GetSize()
{
	return size;
}

void CTexture::SetScale( float x, float y )
{
	SetScale( { x, y } );
}

void CTexture::SetScale( vec2f scale )
{
	this->scale = scale;
}

vec2f CTexture::GetScale()
{
	return scale;
}

void CTexture::SetRotation( float angle )
{
	this->rotation = angle;
}

float CTexture::GetRotation()
{
	return rotation;
}
