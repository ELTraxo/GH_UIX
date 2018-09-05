#include "Menu.h"

void OptionCallback( ControlPtr pControl, void* pData )
{
	uintptr_t index = (uintptr_t)pData;

	switch ( index )
	{
		case 0:
		{
			O.bInfAmmo = std::dynamic_pointer_cast<Checkbox>( pControl )->GetState();
			hax::InfAmmo();
			break;
		}
		case 1:
		{
			O.bAimbot = std::dynamic_pointer_cast<Checkbox>( pControl )->GetState();
			break;
		}
		case 2:
		{
			O.bESP = std::dynamic_pointer_cast<Checkbox>( pControl )->GetState();
			break;
		}
	}

}



Menu::Menu( NativeWindowPtr pOverlay )
{
	this->pOverlay = pOverlay;
	this->pMenu = nullptr;
}

Menu::~Menu()
{
}

void Menu::Create()
{
	if ( !pOverlay )
		return;

	pMenu = pOverlay->GetCanvas()->MakeWindow();
	//pMenu->SetSize( { 300,200 } );
	//pMenu->SetPos( 100 );
	//pMenu->SetColor( 0xAA000000 );

	auto pCheck = pMenu->AddCheckbox( { 5,20 }, _T( "Inf Ammo" ) );
	pCheck->SetEventCallback( XCallbackEvent::LBUTTONDOWN, OptionCallback, 0 );
	pCheck = pMenu->AddCheckbox( { 5,35 }, _T( "Aimbot" ) );
	pCheck->SetEventCallback( XCallbackEvent::LBUTTONDOWN, OptionCallback, 1 );
	pCheck = pMenu->AddCheckbox( { 5,50 }, _T( "ESP" ) );
	pCheck->SetEventCallback( XCallbackEvent::LBUTTONDOWN, OptionCallback, 2 );
	//pMenu->AddCheckbox( { 5,40 }, _T( "God Mode" ) );
}

WindowPtr Menu::GetWindowPtr()
{
	return this->pMenu;
}

void Menu::Toggle()
{
	RECT r{ 0 };
	GetWindowRect( pOverlay->GetHWND(), &r );

	POINT p{ 0 }; 
	p.x = r.right - ( pOverlay->GetWidth() / 2 );
	p.y = r.bottom - ( pOverlay->GetHeight() / 2);

	pMenu->SetVisible( !pMenu->GetVisible() );
	if ( pMenu->GetVisible() )
	{
		SetForegroundWindow( pOverlay->GetHWND() );
		SetCapture( pOverlay->GetHWND() );
		//SetCursorPos( p.x, p.y );
	}
	else
	{
		SetCursorPos( p.x, p.y );
		SetForegroundWindow( pOverlay->GetOverlayTarget() );
		ReleaseCapture();
		//SetFocus( pOverlay->GetOverlayTarget() );
	}
}
