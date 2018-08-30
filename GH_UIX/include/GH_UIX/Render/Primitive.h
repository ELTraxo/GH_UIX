#pragma once
#include "Renderable.h"
#include "TypesDX9.h"

enum class EPrimType
{
	TF,	// triangle fan
	TL,	// triangle list
	LS, // line strip
	LL	// line list
};

class CPrimitive : public CRenderable
{
	EPrimType ptType;
	VertexBuffer vb;
public:
	CPrimitive() = delete;
	CPrimitive( DevicePtr pDevice, EPrimType primType, Vertex * vertices, uint uVertCount );
	~CPrimitive();
	
	void Render();

private:
	D3DPRIMITIVETYPE GetPrimitiveType();
	uint GetPrimCount();
};

using Primitive = CPrimitive;
using PrimitivePtr = std::shared_ptr<Primitive>;
#define MakePrimPtr(pDevice, primType, verts, vertCount) \
std::make_shared<Primitive>(pDevice, primType, verts, vertCount)