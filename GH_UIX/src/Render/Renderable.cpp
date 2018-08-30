#include "stdafx.h"
#include "Renderable.h"


//
//CRenderable::CRenderable()
//{
//}


CRenderable::~CRenderable()
{
}

ERenderableType CRenderable::GetType()
{
	return renderType;
}
