#pragma once
#include "XButton.h"
#include "XLabel.h"
class CXSlider :
	public CXControl
{
	LabelPtr pLabel;
	ButtonPtr pThumb;
	float thumbWidth;
	vec2f thumbSize;
	bool bMovingSlider;
	vec2f vMinMax;
	float fValue;
	float xOffset;
public:
	CXSlider( RenderPtr pRender );
	~CXSlider();

	void SetSize( vec2f size );
	void SetThumbWidth( float width );
	float GetThumbWidth();
	void SetThumbSize( vec2f size );
	void SetThumbColor( Color color );
	Color GetThumbColor();
	void SetThumbBorderColor( Color color );
	Color GetThumbBorderColor();

	void SetMinMax( float min, float max );
	void SetMinMax( vec2f minmax );
	vec2f GetMinMax();

	void SetValue( float value );
	float GetValue();

	void OnRender();
	void OnMouseMove( float x, float y );
	void OnMouseDown( uint button, float x, float y );
	void OnMouseUp( uint button, float x, float y );

private:
	void UpdateThumbPosition();
	void UpdateValueFromPoint( float x, float y );
};

#define MakeSliderPtr(pRender) \
std::make_shared<Slider>(pRender)