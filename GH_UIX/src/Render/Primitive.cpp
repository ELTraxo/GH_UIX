#include "stdafx.h"
#include "Primitive.h"



//CPrimitive::CPrimitive()
//{
//}

CPrimitive::CPrimitive( DevicePtr pDevice, EPrimType primType, Vertex * vertices, uint uVertCount )
{
	this->pDevice = pDevice;
	this->renderType = PRIMITIVE;
	this->ptType = primType;
	vb.resize( uVertCount );
	memcpy_s( vb.data(), vb.size() * sizeof(Vertex), vertices, uVertCount * sizeof(Vertex) );
}



CPrimitive::~CPrimitive()
{
	vb.clear();
}

void CPrimitive::Render()
{
	pDevice->DrawPrimitiveUP( GetPrimitiveType(), GetPrimCount(), vb.data(), sizeof( Vertex ) );
}

D3DPRIMITIVETYPE CPrimitive::GetPrimitiveType()
{
	switch(ptType)
	{
		case EPrimType::TF:
			return D3DPT_TRIANGLEFAN;
		case EPrimType::TL:
			return D3DPT_TRIANGLELIST;
		case EPrimType::LS:
			return D3DPT_LINESTRIP;
		case EPrimType::LL:
			return D3DPT_LINELIST;
	}

	ErrorMsgBox( _T( "Unhandled primitive type...." ) );
	return D3DPRIMITIVETYPE(0); // should cause an error if this happens?
}

uint CPrimitive::GetPrimCount()
{
	switch(ptType)
	{
		case EPrimType::TF: 
			return (uint)vb.size() - 2;
		case EPrimType::TL:
			return (uint)vb.size() / 3;
		case EPrimType::LL:
			return (uint)vb.size() / 2;
		case EPrimType::LS:
			return (uint)vb.size() - 1;
	}
	return uint(0);
}
