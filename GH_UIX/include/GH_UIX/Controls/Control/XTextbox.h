#pragma once
#include "XControl.h"

class CXTextBox : public CXControl
{
	tstring sText;
	tstring sDisplay;
	float fTextWidth = 0;

	bool bCaretVisible = false;
	int iCaretIndex = 0;
	int iCaretIndexDisplay = 0;
	int iDisplayStart = 0;
	int iDisplayFinish = 0;
	vec2f vCaretPos = { 0.0f, 0.0f };
	
	DWORD textColor;
public:
	CXTextBox( RenderPtr pRender );
	~CXTextBox();
	tstring GetText();
	void SetText( tstring text );
	int GetCharAtPos( float x, float y );
	bool CursorIntersectChar( float x, float y );
	int GetCaretPos();
	void SetCaretPos( int pos );
	bool InsertText( tstring text );
	int RemoveText( int count );
	
	void OnRender();
	void OnMouseMove( float x, float y );
	void OnMouseDown( uint button, float x, float y );
	void OnMouseUp( uint button, float x, float y );
	void OnChar( WPARAM key, LPARAM extended );
	void OnKeyDown( WPARAM key, LPARAM extended );
	void OnKeyUp( WPARAM key, LPARAM extended );
	void OnSysKey( WPARAM key, LPARAM extended );

private:
	void MoveCaretLeftByOne();
	void MoveCaretRightByOne();
	vec2f CalculateDisplaySize( int start, int finish );
};


#define MakeTextboxPtr(pRender) std::make_shared<Textbox>(pRender)