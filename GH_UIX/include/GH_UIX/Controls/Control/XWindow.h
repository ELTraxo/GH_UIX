#pragma once
#include "XControlContainer.h"
#include "XLabel.h"

class CXWindow : public CXControlContainer
{
	LabelPtr pLabel;
	bool bDragging;
	vec2f sizeTitlebar;
	vec2f mousePos;

public:
	CXWindow( RenderPtr pRender );
	~CXWindow();
	void SetTitlebarHeight( float height );
	float GetTitlebarHeight();
	void SetSize( const vec2f& size );

	bool IsMoving();
	vec2f GetMouseDownPos();
	void OnRender();
	void OnMouseMove( float x, float y );
	void OnMouseDown( uint button, float x, float y );
	void OnMouseUp( uint button, float x, float y );
private:
	bool TitlebarIntersect( float x, float y );
};

#define MakeWindowPtr(pRender) \
std::make_shared<Window>(pRender)
