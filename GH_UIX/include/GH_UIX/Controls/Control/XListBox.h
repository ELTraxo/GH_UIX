#pragma once
#include "XButton.h"
#include "XTextbox.h"
#include "XScrollbar.h"

class CXListBoxItem;
using ListBoxItem = CXListBoxItem;
using ListBoxItemPtr = std::shared_ptr<ListBoxItem>;
#define MakeListBoxItemPtr(pRender) std::make_shared<ListBoxItem>(pRender)

class CXListBoxItem : public CXControl
{
	bool bSelected;
	tstring caption;
	DWORD selectedColor;
	int index;
	int frameIndex;
public:
	CXListBoxItem( RenderPtr pRender );
	~CXListBoxItem();
	void SetIndex( int index ) { this->index = index; }
	int GetIndex() { return this->index; }
	void SetFrameIndex( int index ) { this->frameIndex = index; }
	void SetFrameIndicesRev( ListBoxItemPtr pControl, int start );
	int GetFrameIndex() { return this->frameIndex; }
	void SetSelect( bool state ) { bSelected = state; }
	void SetItemSize( float w, float h );
	void SetCaption( tstring caption ) { this->caption = caption; }
	tstring GetCaption() { return caption; }

	void OnRender();
	void OnMouseDown( uint button, float x, float y );
};

class CXListBox : public CXControl
{
	ListBoxItemPtr pItems;
	ListBoxItemPtr pSelected;
	ScrollbarPtr pScroll;
	bool bAllowMultiSelect;
	int iListFrame;
	int iItemsInFrame = 0;
	int iCount;
	float fItemHeight = 16.0f;
	int iSelected = 0;
	int ComputeListFrame();
public:
	CXListBox( RenderPtr pRender );
	~CXListBox();
	void SetSize( const vec2f& size );
	
	void SetColor( Color color );
	void SetBorderColor( Color color );

	bool ItemInFrame( ListBoxItemPtr pItem );
	ListBoxItemPtr AddNewItem( tstring caption );
	void RemoveListItem( ListBoxItemPtr pItem );
	ListBoxItemPtr GetItemAtPos( float x, float y );
	ListBoxItemPtr GetItemByIndex( int index );
	void ScrollTo( int value );
	void Clear();
	
	bool ScrollBarIntersect( float x, float y );
	ListBoxItemPtr GetSelected() { return pSelected; }
	
	float GetListWidth() { return GetWidth() - pScroll->GetWidth(); }
	void AddItemFrameCount() { iItemsInFrame++; }
	int GetItemFrameCount() { return iItemsInFrame; }
	int GetItemFrameMax() { return iListFrame; }
	
	void OnItemSelect( ListBoxItemPtr pSelected, uint button, float x, float y );
	
	void OnRender();
	void OnMouseDown( uint button, float x, float y );
	void OnMouseUp( uint button, float x, float y );
	void OnMouseMove( float x, float y );
	void OnMouseWheel( WPARAM wParam, LPARAM lParam );
	void OnKeyDown( WPARAM key, LPARAM extended );
	//void OnKeyUp( WPARAM key, LPARAM extended );
};


#define MakeListBoxPtr(pRender) std::make_shared<ListBox>(pRender)