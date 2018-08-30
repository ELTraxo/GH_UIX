#pragma once
#include "TypesUIX.h"
#include "Render/Render.h"

#define WM_RENDER WM_USER + 0
#define WM_SETRENDERER WM_USER + 1
#define WM_SETHOT WM_USER + 2
#define WM_SETFOCUSED WM_USER + 3

class CXControl;
using Control = CXControl;
using ControlPtr = std::shared_ptr<CXControl>;
#define MakeControlPtr(pRender) \
std::make_shared<CXControl>(pRender)

class CXControl : public std::enable_shared_from_this<CXControl>
{
protected:
	RenderPtr pRender;
	FontPtr pFont;
	TexturePtr pTexture;
	TexturePtr pHotTexture;

	vec2f pos;
	vec2f size;
	Color bgColor;
	Color borderColor;
	float borderWidth;
	bool isVisible;
	bool bUseRect;
	RECT rect;
	bool isHot;
	ControlPtr pHot;
	bool isFocused;
	ControlPtr pFocused;
	ControlPtr pParent;
	ControlPtr pChildren;
	ControlPtr pNext;
	ControlPtr pPrev;
	ControlPtr pMoving;
public:
	CXControl( RenderPtr pRender );
	~CXControl();

	virtual void SetRenderer( RenderPtr pRender );
	virtual RenderPtr GetRenderer();
	virtual void SetFont( FontPtr pFont );
	virtual FontPtr GetFont();
	virtual void SetTexture( TexturePtr pTexture );
	virtual TexturePtr GetTexture();
	virtual void SetHotTexture( TexturePtr pTexture );
	virtual TexturePtr GetHotTexture();

	virtual vec2f GetAbsPos( vec2f & pos );
	virtual void SetPos( const vec2f & pos );
	virtual vec2f GetPos();
	virtual void SetSize( const vec2f & size );
	virtual vec2f GetSize();
	virtual float GetWidth();
	virtual float GetHeight();
	virtual vec2f GetCenter();
	virtual void SetColor( Color color );
	virtual Color GetColor();
	virtual void SetBorderColor( Color color );
	virtual Color GetBorderColor();
	virtual void SetVisible( bool isVisible );
	virtual bool GetVisible();
	virtual void SetHot( ControlPtr pControl );
	virtual bool GetHot(ControlPtr & pControl);
	virtual void SetFocused( ControlPtr pControl );
	virtual bool GetFocused( ControlPtr & pControl );

	virtual void SetRectAbs( const RECT& rect, bool bUseRect=true );
	virtual RECT GetRectAbs();

	virtual void SetParent( ControlPtr pParent );
	virtual ControlPtr GetParent();
	virtual void AddChildControl( ControlPtr pControl );
	virtual ControlPtr GetChildren();
	virtual void SetNextControl( ControlPtr pControl );
	virtual ControlPtr GetNextControl();
	virtual void SetPrevControl( ControlPtr pControl );
	virtual ControlPtr GetPrevControl();
	virtual void SetMovingControl( ControlPtr pControl );
	//ControlPtr GetControlPtr();

	virtual bool PointIntersect( float x, float y );

	virtual ControlPtr PostToAll( uint msg, WPARAM wParam, LPARAM lParam, void* pData );
	virtual ControlPtr PostToAll( ControlPtr pControl, uint msg, WPARAM wParam, LPARAM lParam, void* pData );
	virtual ControlPtr PostToAllReverse( ControlPtr pControl, uint msg, WPARAM wParam, LPARAM lParam, void* pData );
	virtual bool PostMsg( uint msg, WPARAM wParam, LPARAM lParam, void* pData );

	virtual void OnRender() {}
	virtual void OnMouseMove( float x, float y ) {}
	virtual void OnMouseDown( uint button, float x, float y ) {}
	virtual void OnMouseUp( uint button, float x, float y ) {}
	virtual void OnMouseWheel( WPARAM wParam, LPARAM lParam ) {}
	virtual void OnKeyDown( WPARAM key, LPARAM extended ) {}
	virtual void OnKeyUp( WPARAM key, LPARAM extended ) {}
	virtual void OnSysKey( WPARAM key, LPARAM extended ) {}
	virtual void OnChar( WPARAM key, LPARAM extended ) {}
	virtual void OnSetHot( void* pData );
	virtual void OnLoseHot( void* pData );
	virtual void OnSetFocus( void* pData );
};

#define makeAbsPos() \
vec2f vAbs; \
GetAbsPos(vAbs)

class CXLabel;
using Label = CXLabel;
using LabelPtr = std::shared_ptr<CXLabel>;
class CXButton;
using Button = CXButton;
using ButtonPtr = std::shared_ptr<Button>;
class CXListBox;
using ListBox = CXListBox;
using ListBoxPtr = std::shared_ptr<ListBox>;
class CXDropdown;
using Dropdown = CXDropdown;
using DropdownPtr = std::shared_ptr<Dropdown>;
class CXTextBox;
using Textbox = CXTextBox;
using TextboxPtr = std::shared_ptr<Textbox>;
class CXCheckbox;
using Checkbox = CXCheckbox;
using CheckboxPtr = std::shared_ptr<Checkbox>;
class CXRadio;
using Radio = CXRadio;
using RadioPtr = std::shared_ptr<Radio>;
class CXGroupbox;
using Groupbox = CXGroupbox;
using GroupboxPtr = std::shared_ptr<Groupbox>;
class CXTabControl;
using TabControl = CXTabControl;
using TabControlPtr = std::shared_ptr<TabControl>;
class CXSlider;
using Slider = CXSlider;
using SliderPtr = std::shared_ptr<Slider>;
class CXCanvas;
using Canvas = CXCanvas;
using CanvasPtr = std::shared_ptr<Canvas>;