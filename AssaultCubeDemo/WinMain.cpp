#include "includes.h"
#include "Menu.h"

HWND hWndTarget = NULL;
NativeWindowPtr pOver = nullptr;
LRESULT CALLBACK WPCallback( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam )
{
	if ( hWnd == hWndTarget )
	{
		if ( msg == WM_MOVING )
		{
			SetWindowPos( pOver->GetHWND(), NULL, GET_X_LPARAM( lParam ), GET_Y_LPARAM( lParam ), 0, 0, SWP_NOSIZE );
		}
	}
	return TRUE;
}

LRESULT CALLBACK GMCallback( WPARAM pParam, MSG * pMsg )
{
	if ( pMsg->hwnd == hWndTarget )
	{
		if ( pMsg->message == WM_MOVING )
		{
			SetWindowPos( pOver->GetHWND(), NULL, GET_X_LPARAM( pMsg->lParam ), GET_Y_LPARAM( pMsg->lParam ), 0, 0, SWP_NOSIZE );
		}
	}
	return TRUE;
}

LRESULT CALLBACK CBTCallback( int nCode, WPARAM wParam, LPARAM lParam )
{
	if ( nCode == HCBT_MOVESIZE )
	{
		if ( (HWND)wParam == hWndTarget )
		{
			ErrorMsgBox( L"Whatever" );
			return 0;
		}
	}
	return TRUE;
}

int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow )
{
	auto uix = UIX::Create( hInstance, false );
	auto pMenuWindow = uix->CreateStandaloneWindow( 15, { 300,200 } );
	pMenuWindow->SetIsOverlay( true );

	auto pOverlay = uix->CreateOverlayWindow( PROCNAME );
	hWndTarget = pOverlay->GetOverlayTarget();
	pOver = pOverlay;

	//HMODULE hMod = LoadLibrary( _T( "GHooks_Win32.dll" ) );
	////
	//HOOKPROC pProc = (HOOKPROC)GetProcAddress( hMod, "WndProcHook" );
	//auto SetWndProcCallback = (_SetWndProcHookCallback)GetProcAddress( hMod, "SetWndProcHookCallback" );
	//SetWndProcCallback( WPCallback );
	//auto hhkWndProc = SetWindowsHookEx( WH_CALLWNDPROC, pProc, hMod, NULL );
	//
	//HOOKPROC pMsgProc = (HOOKPROC)GetProcAddress( hMod, "GetMessageHook" );
	//auto SetGetMessageCallback = (_SetGetMessageCallback)GetProcAddress( hMod, "SetGetMessageHookCallback" );
	//SetGetMessageCallback( GMCallback );
	//auto hhkGetMessage = SetWindowsHookEx( WH_GETMESSAGE, pMsgProc, hMod, NULL );
	//
	////auto WinEventProc = (WINEVENTPROC)GetProcAddress( hMod, "WinEventHook" );
	////auto hWinEventHook = SetWinEventHook( EVENT_SYSTEM_MOVESIZESTART, EVENT_SYSTEM_MOVESIZEEND, NULL, WinEventHook, NULL, NULL, WINEVENT_OUTOFCONTEXT );
	//HOOKPROC pCBT = (HOOKPROC)GetProcAddress( hMod, "CBTHook" );
	//auto SetCBTCallback = (_SetCBTHookCallback)GetProcAddress( hMod, "SetCBTHookCallback" );
	//SetCBTCallback( CBTCallback );
	//auto hhk = SetWindowsHookEx( WH_CBT, pCBT, hMod, NULL );

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
			uix->UpdateOverlayRect( pOver, uix->GetOverlayRect( pOver->GetOverlayTarget() ) );
			uix->RenderFrame();
		}

		delete pMem;
	}
	else
		return -1;

	//UnhookWinEvent( hWinEventHook );
	//UnhookWindowsHookEx( hhkGetMessage );
	//UnhookWindowsHookEx( hhkWndProc );
	//UnhookWindowsHookEx( hhk );

	return 0;
}