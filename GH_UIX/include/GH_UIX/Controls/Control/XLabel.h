#pragma once
#include "XControl.h"

class CXLabel :	public CXControl
{
	tstring sText;
	DWORD dwFormat;
public:
	CXLabel( RenderPtr pRender );
	~CXLabel();

	void SetText(const tstring& sText);
	tstring GetText();
	void SetFormat( DWORD dwFormat );
	DWORD GetFormat();
	RECT GetRect();
	void OnRender();
};


#define MakeLabelPtr(pRender) \
std::make_shared<CXLabel>(pRender)