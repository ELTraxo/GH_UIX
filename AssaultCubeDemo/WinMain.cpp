#include "includes.h"
#include "Menu.h"



int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow )
{
	auto uix = UIX::Create( hInstance, false );
	auto pMenuWindow = uix->CreateStandaloneWindow( 15, { 300,200 } );
	auto pOverlay = uix->CreateOverlayWindow( PROCNAME );
	
	if ( pOverlay && pMenuWindow)
	{
		Menu menu( pMenuWindow );
		menu.Create();
		auto pWindow = menu.GetWindowPtr();
		auto pRender = pOverlay->GetRenderer();

		hax::Initialize( pOverlay );

		G.WindowWidth = pOverlay->GetWidth();
		G.WindowHeight = pOverlay->GetHeight();		

		//main loop
		MSG m;
		POINT p{ 0 };
		
		while ( true )
		{
			if ( GetAsyncKeyState( VK_DELETE ) & 1 /*bToggleMenu*/ )
			{
				menu.Toggle();
			}

			if ( GetAsyncKeyState( VK_END ) & 1 )
			{
				PostQuitMessage( 0 );
				break;
			}

			if ( PeekMessage( &m, NULL, 0, 0, PM_REMOVE ) && m.message != WM_QUIT )
			{
				TranslateMessage( &m );
				DispatchMessage( &m );
			}
			if ( m.message == WM_QUIT )
				break;
			
			hax::Run();
			uix->RenderFrame();
		}

		delete pMem;
	}
	else
		return -1;

	return 0;
}