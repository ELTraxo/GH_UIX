#pragma once
#include "XControl.h"
#include "XLabel.h"

class CXStateControl :	public CXControl
{
protected:
	LabelPtr pLabel;
	vec2f sizeState;
	float padding;
	bool bState;
public:
	CXStateControl(RenderPtr pRender);
	~CXStateControl();

	virtual void SetText( const tstring & sText );
	virtual tstring GetText();
	virtual void SetStateSize( const vec2f& size );
	virtual vec2f GetStateSize();
	virtual void SetState( bool bState );
	virtual bool GetState();
	virtual void OnMouseMove( float x, float y );
	virtual void OnMouseDown( uint button, float x, float y );
	virtual void OnKeyDown( WPARAM key, WPARAM extended );

};


#define MakeCheckboxPtr(pRender) std::make_shared<Checkbox>(pRender)

class CXCheckbox : public CXStateControl
{
public:
	CXCheckbox( RenderPtr pRender );
	~CXCheckbox();
	void OnRender();
};


#define MakeRadioPtr(pRender) std::make_shared<Radio>(pRender)

class CXRadio : public CXStateControl
{
	RadioPtr pFirstRadio;
	RadioPtr pNextRadio;
	RadioPtr pPrevRadio;
	RadioPtr pSelected;

public:
	CXRadio( RenderPtr pRender );
	~CXRadio();

	void SetFirstRadio( RadioPtr pRadio );
	RadioPtr GetFirstRadio();
	void SetNextRadio(RadioPtr pRadio);
	RadioPtr GetNextRadio();
	void SetPrevRadio(RadioPtr pRadio);
	RadioPtr GetPrevRadio();
	void SetSelected( RadioPtr pRadio );
	RadioPtr GetSelected();
	void AddRadio( RadioPtr pRadio );

	void OnRender();
	void OnMouseDown( uint button, float x, float y );
	void OnSelect( ControlPtr pRadio );
};

