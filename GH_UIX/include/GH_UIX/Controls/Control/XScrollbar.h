#pragma once
#include "XControl.h"
#include "XButton.h"

enum class EScrollOrientation
{
	VERTICAL,
	HORIZONTAL
};

class CXScrollbar :	public CXControl
{
	ButtonPtr btnTopLeft;
	ButtonPtr btnBottomRight;
	ButtonPtr btnThumb;

	int iMin;
	int iMax;
	int iValue;

	bool bDrag;

	EScrollOrientation orientation;

public:
	CXScrollbar( RenderPtr pRender );
	~CXScrollbar();
	
	ButtonPtr GetThumb();
	ButtonPtr GetTopLeftButton();
	ButtonPtr GetBottomRightButton();

	void SetSize( vec2f size );
	void SetColor( Color color );
	void SetBorderColor( Color color );
	bool IsDragging();


	void SetMinMax( int min, int max );
	int GetMin();
	int GetMax();
	vec2i GetMinMax();
	void SetValue( int value );
	int GetValue();

	void OnRender();
	void OnMouseDown( uint button, float x, float y );
	void OnMouseUp( uint button, float x, float y );
	void OnMouseMove( float x, float y );
	void OnMouseWheel( WPARAM wParam, LPARAM lParam );
	void OnKeyDown( WPARAM key, LPARAM extended);
	void OnKeyUp( WPARAM key, LPARAM extended );
private:
	void CalculateValue( float x, float y );
	void CalculateThumbPos();
};

using Scrollbar = CXScrollbar;
using ScrollbarPtr = std::shared_ptr<Scrollbar>;
#define MakeScrollbarPtr(pRender) std::make_shared<Scrollbar>(pRender)