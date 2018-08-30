#pragma once
#include "Primitive.h"
#include "Sprite.h"
#include "Text.h"

using Renderables = std::vector<RenderablePtr>;

class CRenderList
{
	Renderables renderables;
public:
	CRenderList();
	~CRenderList();
	Renderables& GetList();
	void Clear();
	
	void AddRenderable( PrimitivePtr pPrim );
	void AddRenderable( TexturePtr pTexture );
	void AddRenderable( TextPtr pFont );
};

using RenderList = CRenderList;