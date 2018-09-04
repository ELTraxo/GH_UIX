#include "includes.h"
#include "Menu.h"

#define PROCNAME _T("ac_client.exe")

Options O;
MemEx* pMem = nullptr;

int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow )
{
	auto uix = UIX::Create( hInstance, false );
	auto pOverlay = uix->CreateOverlayWindow( PROCNAME );

	if ( pOverlay )
	{
		pMem = new MemEx( PROCNAME );
		pMem->Open();

		G.pClientBase = GetModuleBase( pMem->GetPID(), PROCNAME );
		G.pLocalPlayer = G.pClientBase + G.pPlayerOffset;
		G.pViewMatrix = G.pClientBase + G.pViewMatrixOffset;
		G.pEntities = G.pLocalPlayer + 4;
		G.WindowWidth = pOverlay->GetWidth();
		G.WindowHeight = pOverlay->GetHeight();

		auto pRender = pOverlay->GetRenderer();
		Menu menu( pOverlay );
		menu.Create();
		auto pWindow = menu.GetWindowPtr();

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
			
			pOverlay->GetCanvas()->PostMsg( WM_RENDER, 0, 0, 0 );
			hax::UpdateEntities();
			hax::Aimbot();
			hax::ESP(pRender);
			uix->RenderFrame();
		}

		delete pMem;
	}
	else
		return -1;

	return 0;
}