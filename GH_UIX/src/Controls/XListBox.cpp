#include "stdafx.h"
#include "XListBox.h"

// listbox item
CXListBoxItem::CXListBoxItem( RenderPtr pRender )
	:
	CXControl( pRender )
{
	bSelected = false;
	caption = L"";
	selectedColor = 0xFFFFFFFF;
	index = 0;
	frameIndex = 0;
}


CXListBoxItem::~CXListBoxItem()
{
}

void CXListBoxItem::SetFrameIndicesRev( ListBoxItemPtr pControl, int start )
{
	do
	{
		pControl->SetFrameIndex( start );
		pControl = std::dynamic_pointer_cast<ListBoxItem>(pControl->GetPrevControl());
		start--;
	} while ( start >= 0 );
}

void CXListBoxItem::SetItemSize( float w, float h )
{
	size = { w, h };
}

void CXListBoxItem::OnRender()
{
	vec2f abs = { 0.0f, 0.0f };
	GetAbsPos( abs );

	auto parentList = std::dynamic_pointer_cast<ListBox>(GetParent());
	if ( parentList->ItemInFrame( std::dynamic_pointer_cast<ListBoxItem>( shared_from_this() ) ) )
	{
		DWORD currColor = ( bSelected ) ? selectedColor : bgColor;
		pRender->DrawRect( abs, size, currColor );
		auto r = GetRectAbs();
		r.left += 2;
		pRender->DrawString( pFont, caption, 0, DT_LEFT | DT_VCENTER, ( bSelected ) ? bgColor : selectedColor, r, true );
		//parentList->AddItemFrameCount();
	}
}

void CXListBoxItem::OnMouseDown( uint button, float x, float y )
{
	SetSelect( true );
}

// list box


int CXListBox::ComputeListFrame()
{
	if ( pItems )
	{
		int frame = (int)GetHeight() / (int)pItems->GetHeight();
		if ( iCount > frame )
			pScroll->SetMinMax( 0, iCount - frame );
		else
			pScroll->SetMinMax( 0, 1 );
		return frame;
	}
	else
	{
		pScroll->SetMinMax( 0, 1 );
		return 0;
	}
}

CXListBox::CXListBox( RenderPtr pRender )
	:
	CXControl( pRender )
{
	bAllowMultiSelect = false;
	pItems = nullptr;
	pSelected = nullptr;
	pScroll = MakeScrollbarPtr( pRender );
	pScroll->SetSize( 10.0f );
	iListFrame = 0;
	iCount = 0;
	bgColor = 0xFF202020;
}


CXListBox::~CXListBox()
{
}

void CXListBox::SetSize( const vec2f& size )
{
	CXControl::SetSize( size );
	pScroll->SetSize( { pScroll->GetSize().x, size.y } );
}

void CXListBox::SetColor( Color color )
{
	this->bgColor = color;
	this->pScroll->SetColor( color );
}

void CXListBox::SetBorderColor( Color color )
{
	borderColor = color;
	this->pScroll->SetBorderColor( color );
}

bool CXListBox::ItemInFrame( ListBoxItemPtr pItem )
{
	int scrollVal = pScroll->GetValue();
	int range = iListFrame;

	vec2f abs = { 0.0f, 0.0f };
	GetAbsPos( abs );
	vec2f pos = { 0.0f, 0.0f };
	pItem->GetAbsPos( pos );

	if ( pos.y >= abs.y && pos.y <= abs.y + GetHeight() )
	{
		if ( pos.y + pItem->GetHeight() >= abs.y && pos.y + pItem->GetHeight() <= abs.y + GetHeight() )
		{
			return true;
		}
	}
	return false;
}

ListBoxItemPtr CXListBox::AddNewItem( tstring caption )
{
	auto item = MakeListBoxItemPtr( pRender );
	item->SetIndex( iCount );

	if ( iCount < iListFrame )
		item->SetFrameIndex( iCount );
	else
		item->SetFrameIndex( -1 );

	if ( item )
	{
		item->SetParent( shared_from_this() );
		if ( !pItems )
		{
			pItems = item;
			item->SetPos( { 1.0f } );
		}
		else
		{
			auto temp = pItems;
			float height = 0;
			while ( temp->GetNextControl() )
			{
				height = temp->GetHeight();
				temp = std::dynamic_pointer_cast<CXListBoxItem>(temp->GetNextControl());
			}
			temp->SetNextControl( item );
			item->SetPrevControl( temp );
			item->SetPos( { 1.0f, temp->GetHeight() * iCount/*height + temp->GetHeight()*/ } );
		}

		item->SetItemSize( GetWidth() - pScroll->GetWidth(), fItemHeight );
		item->SetCaption( caption );
		iCount++;
		iListFrame = ComputeListFrame();
		ScrollTo( 0 );
		return item;
	}
	return nullptr;
}

void CXListBox::RemoveListItem( ListBoxItemPtr pItem )
{
	auto pPrev = std::dynamic_pointer_cast<ListBoxItem>( pItem->GetPrevControl() );
	auto pNext = std::dynamic_pointer_cast<ListBoxItem>( pItem->GetNextControl() );

	pPrev->SetNextControl( pNext );
	pNext->SetPrevControl( pPrev );

	pItem = nullptr;
}

ListBoxItemPtr CXListBox::GetItemAtPos( float x, float y )
{
	int i = 0;
	vec2f abs = { 0.0f, 0.0f };
	GetAbsPos( abs );

	auto currItem = pItems;

	while ( currItem )
	{
		if ( currItem->GetVisible() )
		{
			if ( x >= abs.x && x <= abs.x + ( GetWidth() - pScroll->GetWidth() ) )
			{
				if ( y >= abs.y + currItem->GetPos().y && y <= abs.y + currItem->GetPos().y + currItem->GetHeight() )
				{
					return currItem;
				}
			}
		}

		currItem = std::dynamic_pointer_cast<ListBoxItem>(currItem->GetNextControl());
	}

	return nullptr;
}

ListBoxItemPtr CXListBox::GetItemByIndex( int index )
{
	int i = 0;
	auto currItem = pItems;
	while ( currItem )
	{
		if ( i == index )
			return currItem;
		i++;
		currItem = std::dynamic_pointer_cast<ListBoxItem>(currItem->GetNextControl());
	}
	return nullptr;
}

void CXListBox::ScrollTo( int value )
{
	// can it scroll?
	if ( iCount > iListFrame )
	{
		if ( value + iListFrame <= iCount )
		{
			// Get first item
			auto currItem = pItems;
			int i = 0;
			float fAccumY = 0.0f;

			while ( currItem )
			{
				//currItem->SetSelect( false );


				if ( i >= value && i < value + iListFrame )
				{
					currItem->SetVisible( true );
					currItem->SetPos( { 0, fAccumY } );
					fAccumY += currItem->GetHeight();
				}
				else
					currItem->SetVisible( false );

				currItem = std::dynamic_pointer_cast<ListBoxItem>(currItem->GetNextControl());
				i++;
			}
		}
	}
}

void CXListBox::Clear()
{
	if ( pItems )
	{
		auto pNext = pItems->GetNextControl();
		while ( pNext )
		{
			auto temp = pNext->GetNextControl();
			pNext->SetPrevControl( nullptr );
			pNext->SetNextControl( nullptr );
			pNext.reset();
			pNext = nullptr;
			pNext = temp;
		}
	}
	pItems = nullptr;
}

bool CXListBox::ScrollBarIntersect( float x, float y )
{
	vec2f abs = { 0.0f, 0.0f };
	pScroll->GetAbsPos( abs );

	if ( x >= abs.x && x <= abs.x + pScroll->GetWidth() )
		if ( y >= abs.y && y <= abs.y + pScroll->GetHeight() )
			return true;
	return false;
}

void CXListBox::OnItemSelect( ListBoxItemPtr pSelected, uint button, float x, float y )
{
	if ( this->pSelected )
		this->pSelected->SetSelect( false );
	this->pSelected = pSelected;
	pSelected->SetSelect( true );
}

void CXListBox::OnRender()
{
	vec2f abs = { 0.0f,0.0f };
	GetAbsPos( abs );
	if ( GetVisible() )
	{
		pRender->DrawRect( abs, size, bgColor );
		pRender->DrawBox( abs, size, 1.0f, borderColor );

		if ( pItems )
		{
			iItemsInFrame = 0;
			PostToAll( pItems, WM_RENDER, 0, 0, 0 );
		}
		if ( pScroll )
		{
			pScroll->SetPos( { abs.x + ( GetWidth() - pScroll->GetWidth() ), abs.y } );
			pScroll->OnRender();
		}
	}
}

void CXListBox::OnMouseDown( uint button, float x, float y )
{
	if ( !isFocused )
		SetFocused( shared_from_this() );
	if ( ScrollBarIntersect( x, y ) )
	{
		pScroll->OnMouseDown( button, x, y );
		return;
	}
	ListBoxItemPtr pSelect = nullptr;
	pSelect = GetItemAtPos( x, y );
	if ( pSelect )
	{
		if ( pSelect->GetIndex() < GetItemFrameMax() )
			iSelected = pSelect->GetIndex();
		else
			iSelected = pSelect->GetIndex() - pScroll->GetValue();
		if ( pSelect )
			OnItemSelect( pSelect, button, x, y );
	}
}

void CXListBox::OnMouseUp( uint button, float x, float y )
{
	if ( pScroll->IsDragging() || ScrollBarIntersect( x, y ) )
	{
		pScroll->OnMouseUp( button, x, y );
		ScrollTo( pScroll->GetValue() );
	}
}

void CXListBox::OnMouseMove( float x, float y )
{
	SetHot( shared_from_this() );
	if ( ScrollBarIntersect( x, y ) || pScroll->IsDragging() )
	{
		pScroll->OnMouseMove( x, y );
		if ( pScroll->IsDragging() )
			ScrollTo( pScroll->GetValue() );
		//ScrollTo( pScroll->GetValue() );
	}
}

void CXListBox::OnMouseWheel( WPARAM wParam, LPARAM lParam )
{
	pScroll->OnMouseWheel( wParam, lParam );
	ScrollTo( pScroll->GetValue() );
}

void CXListBox::OnKeyDown( WPARAM key, LPARAM extended )
{
	if ( pSelected )
		switch ( key )
		{
			case VK_DOWN:
			{
				if ( pSelected->GetNextControl() )
				{
					pSelected->SetSelect( false );
					auto next = std::dynamic_pointer_cast<ListBoxItem>( pSelected->GetNextControl() );
					next->SetSelect( true );
					pSelected = next;
					iSelected = pSelected->GetFrameIndex();
					if ( iSelected < 0 )
					{
						pSelected->SetFrameIndicesRev( pSelected, GetItemFrameMax() - 1 );
						iSelected = GetItemFrameMax() - 1;
					}
					if ( pSelected->GetIndex() >= iListFrame )
					{
						pScroll->SetValue( pScroll->GetValue() + 1/*pSelected->GetIndex() - (GetItemFrameMax() - 1)*/ );
						ScrollTo( pScroll->GetValue() );
					}
				}
				break;
			}
			case VK_UP:
			{
				if ( pSelected->GetPrevControl() )
				{
					pSelected->SetSelect( false );
					auto prev = std::dynamic_pointer_cast<ListBoxItem>( pSelected->GetPrevControl() );
					prev->SetSelect( true );
					pSelected = prev;

					if ( iSelected == 0 )
					{
						{
							pScroll->SetValue( pScroll->GetValue() - 1 );
							ScrollTo( pScroll->GetValue() );
						}
						iSelected++;
					}
					iSelected--;
				}
				break;
			}
		}
}
