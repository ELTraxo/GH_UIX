#include "stdafx.h"
#include "XTextbox.h"

CXTextBox::CXTextBox( RenderPtr pRender )
	:
	CXControl( pRender )
{
	size.x = 100.0f;
	size.y = 18.0f;
	bgColor = 0xFF000000;
	borderColor = 0xFFFFFFFF;
	textColor = 0xFFFFFFFF;

}

CXTextBox::~CXTextBox()
{
}

tstring CXTextBox::GetText()
{
	return sText;
}

void CXTextBox::SetText( tstring text )
{
	sText = text;
	float width = (float)pFont->GetStringWidth( text );
	if ( width <= size.x )
	{
		sDisplay = text;
		fTextWidth = width;
		iDisplayFinish = (int)sDisplay.length();
		SetCaretPos( (int)sDisplay.length() );
	}
	else
	{
		auto v = CalculateDisplaySize( 0, (int)sText.length() - 1 );
		iDisplayStart = (int)v.x;
		iDisplayFinish = (int)v.y;
		sDisplay = sText.substr( iDisplayStart, (uint)v.y );
		iCaretIndex = (int)sText.length();
		iCaretIndexDisplay = (int)sDisplay.length();
		vCaretPos.x = fTextWidth = (float)pFont->GetStringWidth( sDisplay );
	}
}

int CXTextBox::GetCharAtPos( float x, float y )
{
	float pos = 0, left = 0, right = 0;
	vec2f abs = { 0.0f, 0.0f };
	GetAbsPos( abs );
	left = abs.x;

	while ( pos < sText.length() )
	{
		auto tmp = sText.substr( (uint)pos, 1 );
		right = (float)pFont->GetStringWidth( tmp );
		if ( x >= left - ( right - right / 4 ) &&
			x <= left + right - ( right / 4 ) )
			break;
		pos++;
		left += right;
	}
	return (int)pos;
}

bool CXTextBox::CursorIntersectChar( float x, float y )
{
	vec2f pos = { 0,0 };
	GetAbsPos( pos );
	if ( x > pos.x + pFont->GetStringWidth( sText ) )
		SetCaretPos( (int)sText.length() );

	if ( x >= pos.x && x <= pos.x + fTextWidth )
		if ( y >= pos.y && y <= pos.y + GetHeight() )
			return true;
	return false;
}

int CXTextBox::GetCaretPos()
{
	return iCaretIndex;
}

void CXTextBox::SetCaretPos( int pos )
{
	if ( pos >= 0 && pos <= (int)sDisplay.length() )
	{
		iCaretIndexDisplay = pos;
		iCaretIndex = pos + iDisplayStart;
		auto temp = sDisplay.substr( 0, iCaretIndexDisplay );
		vCaretPos.x = (float)pFont->GetStringWidth( temp );
	}
}

bool CXTextBox::InsertText( tstring text )
{
	auto tmp = text;
	if ( ( fTextWidth + pFont->GetStringWidth( tmp ) ) <= GetWidth() )
	{
		sText.insert( iCaretIndex, text );
		if ( pFont->GetStringWidth( sText ) > GetWidth() )
		{
			auto v = CalculateDisplaySize( 0, (int)sText.length() - 1 );
			iDisplayFinish = (int)iCaretIndex;
			sDisplay = sText.substr( (size_t)iDisplayStart, (size_t)v.y );
			fTextWidth = /*vCaretPos.x = */(float)pFont->GetStringWidth( sDisplay );
			MoveCaretRightByOne();
			return true;
		}
		else
			sDisplay.insert( iCaretIndexDisplay, text );		
		fTextWidth = (float)pFont->GetStringWidth( sDisplay );
		MoveCaretRightByOne();
		//SetCaretPos( GetCaretPos() + text.length() );
		//iDisplayFinish++;
		//iCaretIndex++;
		return true;
	}
	else
	{
		if ( iCaretIndex < (int)sText.length() )
		{
			sText.insert( iCaretIndex, text );
			auto indices = CalculateDisplaySize( 0, (int)sText.length() - 1 );
			//iDisplayFinish = (int)( iCaretIndex );
			sDisplay = sText.substr( iDisplayStart, (uint)indices.y);
		}
		else
		{
			sText.append( text );
			auto indices = CalculateDisplaySize( 0, (int)sText.length() - 1);
			iDisplayFinish = (int)( iCaretIndex );
			sDisplay = sText.substr( (uint)indices.x, (uint)iDisplayFinish - iDisplayStart );
			//iCaretIndex++;
			//iDisplayStart++;
			//iDisplayFinish++;
		}

		fTextWidth = (float)pFont->GetStringWidth( sDisplay );

		MoveCaretRightByOne();
		return true;
	}
	return false;
}

#pragma optimize("", on)
int CXTextBox::RemoveText( int count )
{
	bool bNotAtZero = ( GetCaretPos() > 0 ) ? true : false;

	if ( count > 0 )
	{
		if ( iCaretIndex >= (int)sText.length() )
			return (int)fTextWidth;
		sText.erase( iCaretIndex, count );

		iDisplayFinish--;
		auto v = CalculateDisplaySize( 0, (int)sText.length() - 1 );

		iDisplayFinish = (int)(v.y - count);
		sDisplay = sText.substr( (size_t)iDisplayStart, (size_t)v.y );
		fTextWidth = (float)pFont->GetStringWidth( sDisplay );
		return (int)fTextWidth;
	}
	else
	{		
		if ( bNotAtZero )
		{
			MoveCaretLeftByOne();
			sText.erase( iCaretIndex, abs( count ) );
			auto v = CalculateDisplaySize( 0, (int)sText.length() - 1 );

			//iDisplayFinish = (int)(v.y - 1);
			sDisplay = sText.substr( (size_t)iDisplayStart, (size_t)v.y);
			fTextWidth = (float)pFont->GetStringWidth( sDisplay );
			return (int)fTextWidth;
		}
	}
	return 0;
}
#pragma optimize("", off)

void CXTextBox::OnRender()
{
	vec2f abs = { 0,0 };
	GetAbsPos( abs );
	pRender->DrawRect( abs, size, bgColor );
	pRender->DrawBox( abs, size, 1.0f, borderColor );

	auto r = GetRectAbs();
	r.left += 1;
	r.right -= 1;

	pRender->DrawString( pFont, sDisplay, abs, DT_LEFT | DT_VCENTER, textColor, r, true );

	if ( isFocused )
	{
		if ( bCaretVisible )
		{
			vec2f linePos[ 2 ];
			linePos[ 0 ].x = abs.x + vCaretPos.x + 1.0f;
			linePos[ 0 ].y = abs.y + 2.0f;
			linePos[ 1 ].x = abs.x + vCaretPos.x + 1.0f;
			linePos[ 1 ].y = abs.y + GetHeight() - 2.0f;
			pRender->DrawLine( linePos[ 0 ], linePos[ 1 ], textColor );
			bCaretVisible = true;
		}
		else
			bCaretVisible = true;
	}
}


void CXTextBox::OnMouseMove( float x, float y )
{
	SetHot( shared_from_this() );
}

void CXTextBox::OnMouseDown( uint button, float x, float y )
{
	SetFocused( shared_from_this() );
	if ( CursorIntersectChar( x, y ) )
		SetCaretPos( GetCharAtPos( x, y ) );
}

void CXTextBox::OnMouseUp( uint button, float x, float y )
{
}

void CXTextBox::OnChar( WPARAM key, LPARAM extended )
{
	if ( key == VK_BACK )
		return;
	TCHAR* wKey = (TCHAR*)&key;
	InsertText( wKey );
}

void CXTextBox::OnKeyDown( WPARAM key, LPARAM extended )
{
	switch ( key )
	{
		case VK_BACK:
		{
			RemoveText( -1 );
			break;
		}
		case VK_DELETE:
		{
			RemoveText( 1 );
			break;
		}
		case VK_LEFT:
		{
			//SetCaretPos( GetCaretPos() - 1 );
			MoveCaretLeftByOne();
			break;
		}
		case VK_RIGHT:
		{
			//SetCaretPos( GetCaretPos() + 1 );
			MoveCaretRightByOne();
			break;
		}

		default:
		{

			//char* pKey = (char*)&key;
			//wchar_t wKey[ 5 ] = { 0 };
			//mbstowcs_s( nullptr, wKey, 5, pKey, strlen( pKey ) );

			break;
		}
	}
}

void CXTextBox::OnKeyUp( WPARAM key, LPARAM extended )
{
}

void CXTextBox::OnSysKey( WPARAM key, LPARAM extended )
{
}



void CXTextBox::MoveCaretLeftByOne()
{
	if ( iCaretIndex > 0 )
	{
		if ( iDisplayStart > 0 && iCaretIndexDisplay == 0 )
		{
			iDisplayStart--;
			auto v = CalculateDisplaySize( 0, iDisplayFinish );
			iDisplayFinish--;
			//iDisplayFinish = (int)(v.x + v.y);
			//sDisplay = sText.substr( iDisplayStart, (iDisplayFinish - iDisplayStart) + 1 );
			sDisplay = sText.substr( (size_t)iDisplayStart, (size_t)v.y );
		}

		iCaretIndex--;
		iCaretIndexDisplay--;
		if ( iCaretIndexDisplay < 0 )
			iCaretIndexDisplay = 0;
		vCaretPos.x = fTextWidth = (float)pFont->GetStringWidth( sDisplay.substr( 0, iCaretIndexDisplay ) );
	}
}

void CXTextBox::MoveCaretRightByOne()
{
	auto textLen = sText.length();
	auto displayLen = sDisplay.length();

	if ( iCaretIndex < (int)textLen )
	{
		if ( iCaretIndex >= iDisplayFinish)
		{
			if ( iCaretIndex < (int)textLen + 1 && iCaretIndexDisplay >= (int)displayLen)
			{
				iDisplayStart++;
				auto v = CalculateDisplaySize( 0, iCaretIndex );
				iDisplayFinish = iCaretIndex;
				sDisplay = sText.substr( (size_t)iDisplayStart, (size_t)v.y );
			}
			//else
			//	iDisplayFinish++;
		}

		iCaretIndex++;
		iCaretIndexDisplay++;
		auto width = pFont->GetStringWidth( sDisplay.substr( 0, iCaretIndexDisplay ) );
		if ( iCaretIndexDisplay > (int)sDisplay.length() )
			iCaretIndexDisplay = (int)sDisplay.length();
		if ( width > (uint)GetWidth() )
		{
			auto v = CalculateDisplaySize( 0, (int)textLen );
			iDisplayStart = (int)v.x;
			iDisplayFinish = (int)(v.x + v.y);
			sDisplay = sText.substr( (int)v.x, (int)v.y );
		}
		else
			vCaretPos.x = fTextWidth = (float)width;
	}
	else
	{
//		iCaretIndex = textLen;
		//iCaretIndexDisplay = displayLen;
		//vCaretPos.x = fTextWidth = (float)pFont->GetStringWidth( sDisplay.substr( 0, iCaretIndexDisplay ) );
	}
}

vec2f CXTextBox::CalculateDisplaySize( int start, int finish )
{	
	int iCount = 1;
	int index = finish;
	
	tstring temp;
	float width = 0;

	int caret = iCaretIndexDisplay;

	if ( index > (int)sText.length() )
		index = (int)sText.length();


	do
	{
		if ( index < 0 )
			index = 0;
		temp = sText.substr( index, iCount );
		index--;
		iCount++;
		width = (float)pFont->GetStringWidth( temp );
		if ( index < 0 )
			break;
	} while ( width < GetWidth() - 2.0f);

	index++;
	iCount--;
	return vec2f((float)index, (float)iCount);
}

