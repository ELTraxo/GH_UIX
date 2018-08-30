#include "stdafx.h"
#include "RenderList.h"



CRenderList::CRenderList()
{
}


CRenderList::~CRenderList()
{
	Clear();
}

Renderables & CRenderList::GetList()
{
	return renderables;
}

void CRenderList::Clear()
{
	renderables.clear();
}

void CRenderList::AddRenderable( PrimitivePtr pPrim )
{
	renderables.push_back( pPrim );
}

void CRenderList::AddRenderable( TexturePtr pTexture )
{
	renderables.push_back( pTexture );
}

void CRenderList::AddRenderable( TextPtr pFont )
{
	renderables.push_back( pFont );
}
