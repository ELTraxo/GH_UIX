#pragma once
#include "XControlContainer.h"
#include "XButton.h"

class CXTabCanvas;
using TabCanvas = CXTabCanvas;
using TabCanvasPtr = std::shared_ptr<TabCanvas>;
#define MakeTabCanvasPtr(pRender) std::make_shared<TabCanvas>(pRender);
class CXTabCanvas : public CXControlContainer
{
	
	int iIndex;
public:
	CXTabCanvas( RenderPtr pRender );
	~CXTabCanvas();
	void SetIndex( int index );
	int GetIndex();

	void OnRender();
};

class CXTabButton;
using TabButton = CXTabButton;
using TabButtonPtr = std::shared_ptr<TabButton>;
#define MakeTabButtonPtr(pRender) std::make_shared<TabButton>(pRender);

class CXTabButton : public CXButton
{
	TabCanvasPtr pCanvas;
	bool bSelected;
	TabButtonPtr pSelected;
	Color ActiveColor;
	
	//TabButtonPtr pNextTabButton;
	//TabButtonPtr pPrevTabButton;
	
public:
	CXTabButton( RenderPtr pRender );
	~CXTabButton();
	void SetPos( const vec2f & pos );
	void SetCanvas( TabCanvasPtr pCanvas );
	TabCanvasPtr GetCanvas();
	void SetSelected( ControlPtr pSelected );
	void SetSelected( bool bSelected );
	bool IsActive();
	void OnRender();
	void OnMouseDown( uint button, float x, float y );
};

class CXTabControl : public CXControl
{
	TabCanvasPtr pCanvas;
	TabButtonPtr pTabs;
	TabButtonPtr pActiveTab;
	int tabCount;
	vec2f tabSize;
	int iCurrentTab;
public:
	CXTabControl( RenderPtr pRender );
	~CXTabControl();

	void SetSize( const vec2f& size );

	TabCanvasPtr AddTab( tstring tabText );

	void OnRender();
	void OnMouseMove( float x, float y );
	void OnMouseDown( uint button, float x, float y );
	void OnMouseUp( uint button, float x, float y );

};


#define MakeTabControlPtr(pRender) std::make_shared<TabControl>(pRender);