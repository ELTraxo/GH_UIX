#pragma once
#include "XListBox.h"
class CXDropdown : public CXControl
{
	TextboxPtr pTextbox;
	ButtonPtr pButton;
	ListBoxPtr pList;

	vec2f sizeTextbox;
	vec2f sizeButton;
	vec2f sizeList;
	vec2f heights; // x = height w/ list hidden

	bool bShowList;
public:
	CXDropdown( RenderPtr pRender );
	~CXDropdown();

	void SetSize( const vec2f & size );
	void SetTextboxSize( const vec2f & size );
	void SetButtonSize( const vec2f & size );
	void SetListHeight( const float height);

	void AddNewItem( tstring sText );

	void OnRender();
	void OnMouseMove( float x, float y );
	void OnMouseDown( uint button, float x, float y );
	void OnMouseUp( uint button, float x, float y );
	void OnMouseWheel( WPARAM wParam, LPARAM lParam );
	void OnKeyDown( WPARAM key, LPARAM extended );
	void OnKeyUp( WPARAM key, LPARAM extended );
	void OnChar( WPARAM key, LPARAM extended );
};


#define MakeDropdownPtr(pRender) std::make_shared<Dropdown>(pRender)