#pragma once
#include "TypesUIX.h"
#include "TypesDX9.h"


enum ERenderableType
{
	PRIMITIVE,
	TEXTURE,
	TEXT
};

class CRenderable
{
protected:
	DevicePtr pDevice;
	ERenderableType renderType;
public:
	//CRenderable();
	virtual ~CRenderable();
	virtual ERenderableType GetType();
};

using RenderablePtr = std::shared_ptr<CRenderable>;