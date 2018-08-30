#pragma once
#include "XControl.h"


class CXControlContainer : public CXControl
{
public:
	CXControlContainer( RenderPtr pRender );
	~CXControlContainer();

	//template <class XControl>
	//void AddControl( vec2f size, vec2f pos, Color bgColor, Color borderColo );

	virtual LabelPtr AddLabel( vec2f pos, tstring text, Color textColor );
	virtual ButtonPtr AddButton( vec2f pos, vec2f size, tstring text, Color bgColor, Color borderColor );
	virtual ListBoxPtr AddListbox( vec2f pos, vec2f size, Color bgColor, Color borderColor );
	virtual DropdownPtr AddDropdown( vec2f pos, vec2f size, Color bgColor, Color borderColor );
	virtual TextboxPtr AddTextbox( vec2f pos, vec2f size, Color bgColor, Color borderColor );
	virtual CheckboxPtr AddCheckbox( vec2f pos, tstring text );
	virtual RadioPtr AddRadio( vec2f pos, tstring text );
	virtual GroupboxPtr AddGroupbox( vec2f pos, vec2f size, tstring text );
	virtual TabControlPtr AddTabControl( vec2f pos, vec2f size );
	virtual SliderPtr AddSliderControl( vec2f pos, vec2f size, vec2f vMinMax, float value, Color bgColor, Color borderColor );
};

