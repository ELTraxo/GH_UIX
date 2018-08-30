#include "UIX.h"

int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow )
{
	auto uix = UIX::Create( hInstance, false );
	auto pWindow = uix->CreateStandaloneWindow( { 5,50 }, { 400,300 } );
	auto pWindow2 = uix->CreateStandaloneWindow( { 415,50 }, { 400,300 } );

	if ( pWindow )
	{
		pWindow->AddLabel( { 5,20 }, L"We all the way litty...", 0xFFFFFFFF );
		auto pGroup = pWindow->AddGroupbox( { 5,40 }, { 190, 120 }, L"Stuffz right?" );
		pGroup->AddCheckbox( { 5, 20 }, L"Option 1" );
		pGroup->AddCheckbox( { 5, 40 }, L"Option 2" );
		pGroup->AddCheckbox( { 5, 60 }, L"Option 3" );
		pGroup->AddCheckbox( { 5, 80 }, L"Option 4" );

		auto pRadio = pGroup->AddRadio( { 90, 20 }, L"Radio 1" );
		pRadio->AddRadio( pGroup->AddRadio( { 90, 40 }, L"Radio 2" ) );
		pRadio->AddRadio( pGroup->AddRadio( { 90, 60 }, L"Radio 3" ) );
		pRadio->AddRadio( pGroup->AddRadio( { 90, 80 }, L"Radio 4" ) );
		
		pGroup->AddButton( { 5, 100 }, { 180, 20 }, L"Big Button", 0xFF202020, 0xFFFFFFFF );

		//main loop
		MSG m;
		while ( true )
		{
			while ( PeekMessage( &m, NULL, 0, 0, PM_REMOVE ) && m.message != WM_QUIT )
			{
				TranslateMessage( &m );
				DispatchMessage( &m );
			}
			if ( m.message == WM_QUIT )
				break;

			uix->RenderFrame();
		}
	}
	else
		return -1;
	return 0;
}