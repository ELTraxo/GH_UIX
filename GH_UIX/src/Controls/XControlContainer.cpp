#include "stdafx.h"
#include "XControlContainer.h"
#include "XButton.h"
#include "XDropdown.h"
#include "XListBox.h"
#include "XGroupbox.h"
#include "XTabControl.h"
#include "XStateControl.h"
#include "XSlider.h"

CXControlContainer::CXControlContainer( RenderPtr pRender )
	:
	CXControl(pRender)
{
}

CXControlContainer::~CXControlContainer()
{
}

LabelPtr CXControlContainer::AddLabel( vec2f pos, tstring text, Color textColor )
{
	auto pLabel = MakeLabelPtr( pRender );
	pLabel->SetPos( pos );
	pLabel->SetColor( textColor );
	pLabel->SetText( text );
	this->AddChildControl( pLabel );
	return pLabel;
}

ButtonPtr CXControlContainer::AddButton( vec2f pos, vec2f size, tstring text, Color bgColor, Color borderColor )
{
	auto pButton = MakeButtonPtr( pRender );
	pButton->SetPos( pos );
	pButton->SetSize( size );
	pButton->SetText( text );
	pButton->SetColor( bgColor );
	pButton->SetBorderColor( borderColor );
	this->AddChildControl( pButton );
	return pButton;
}

ListBoxPtr CXControlContainer::AddListbox( vec2f pos, vec2f size, Color bgColor, Color borderColor )
{
	auto pListbox = MakeListBoxPtr( pRender );
	pListbox->SetPos( pos );
	pListbox->SetSize( size );
	pListbox->SetColor( bgColor );
	pListbox->SetBorderColor( borderColor );
	this->AddChildControl( pListbox );
	return pListbox;
}

DropdownPtr CXControlContainer::AddDropdown( vec2f pos, vec2f size, Color bgColor, Color borderColor )
{
	auto pDrop = MakeDropdownPtr( pRender );
	pDrop->SetPos( pos );
	pDrop->SetSize( size );
	pDrop->SetColor( bgColor );
	pDrop->SetBorderColor( borderColor );
	this->AddChildControl( pDrop );
	return pDrop;
}

TextboxPtr CXControlContainer::AddTextbox( vec2f pos, vec2f size, Color bgColor, Color borderColor )
{
	auto pText = MakeTextboxPtr( pRender );
	pText->SetPos( pos );
	pText->SetSize( size );
	pText->SetColor( bgColor );
	pText->SetBorderColor( borderColor );
	this->AddChildControl( pText );
	return pText;
}

CheckboxPtr CXControlContainer::AddCheckbox( vec2f pos, tstring text )
{
	auto pCheck = MakeCheckboxPtr( pRender );
	pCheck->SetPos( pos );
	pCheck->SetText( text );
	this->AddChildControl( pCheck );
	return pCheck;
}

RadioPtr CXControlContainer::AddRadio( vec2f pos, tstring text )
{
	auto pRadio = MakeRadioPtr( pRender );
	pRadio->SetPos( pos );
	pRadio->SetText( text );
	this->AddChildControl( pRadio );
	return pRadio;
}

GroupboxPtr CXControlContainer::AddGroupbox( vec2f pos, vec2f size, tstring text )
{
	auto pGroup = MakeGroupboxPtr( pRender );
	pGroup->SetPos( pos );
	pGroup->SetSize( size );
	pGroup->SetText( text );
	this->AddChildControl( pGroup );
	return pGroup;
}

TabControlPtr CXControlContainer::AddTabControl( vec2f pos, vec2f size )
{
	auto pTab = MakeTabControlPtr( pRender );
	pTab->SetPos( pos );
	pTab->SetSize( size );
	this->AddChildControl( pTab );
	return pTab;
}

SliderPtr CXControlContainer::AddSliderControl( vec2f pos, vec2f size, vec2f vMinMax, float value, Color bgColor, Color borderColor )
{
	auto pSlider = MakeSliderPtr( pRender );
	pSlider->SetPos( pos );
	pSlider->SetSize( size );
	pSlider->SetMinMax( vMinMax );
	pSlider->SetValue( value );
	pSlider->SetColor( bgColor );
	pSlider->SetBorderColor( borderColor );
	AddChildControl( pSlider );
	return pSlider;
}
