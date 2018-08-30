#pragma once
#include "XControlContainer.h"

enum class ELabelPosition
{
	TL, // top-left
	TR, // top-right
	BL, // you get it
	BR
};

class CXGroupbox : public CXControlContainer
{
	LabelPtr pLabel;
	ELabelPosition labelPosition;
	float labelPadding;
	float labelEdgeOffset;
public:
	CXGroupbox( RenderPtr pRender );
	~CXGroupbox();

	void SetLabelPosition( ELabelPosition labelPosition );
	ELabelPosition GetLabelPosition();
	void SetText( const tstring & sText );
	tstring GetText();
	void SetTextColor( Color color );
	Color GetTextColor();
	void SetLabelPadding( float padding );
	float GetLabelPadding();
	void SetEdgeOffset( float offset );
	float GetEdgeOffset();

	void OnRender();
};

using Groupbox = CXGroupbox;
using GroupboxPtr = std::shared_ptr<Groupbox>;
#define MakeGroupboxPtr(pRender) std::make_shared<Groupbox>(pRender)
