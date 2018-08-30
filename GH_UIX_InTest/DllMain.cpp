#include "UIX.h"

DWORD WINAPI HaxThread( LPVOID pParam );

BOOL WINAPI DllMain( HINSTANCE hInstance, DWORD dwReason, LPVOID lpReversed )
{
	switch ( dwReason )
	{
		case DLL_PROCESS_ATTACH:
			CreateThread( 0, 0, HaxThread, hInstance, 0, 0 );
			break;
	}
	return TRUE;
}

DWORD WINAPI HaxThread( LPVOID pParam )
{
	HWND hwnd = FindWindow( L"UIXCLASS", NULL );
	auto pUix = UIX::Create( (HINSTANCE)pParam, true );
	pUix->HiJackWndProc();
	// device ptr in uix.exe: 0xcd1b10
	DevicePtr pDevice = *(DevicePtr*)0x291b54;
	// use some sort of hooking method to get d3d device..
	if ( pUix->InitializeRenderer( pDevice ) )
	{
		auto pCanvas = pUix->CreateCanvas();
		pCanvas->MakeWindow();
	}

	//// hook EndScene
	auto vTable = *(void***)pDevice;
	//ogEndScene = ( fnEndScene )*(void**)( &vTable[ 42 ] );
	//*(void**)( &vTable[ 42 ] ) = hEndScene;

	while ( !GetAsyncKeyState( VK_END ) )
	{
		//*(void**)( &vTable[ 42 ] ) = hEndScene;
	}
	ExitProcess( 0 );
	return 0;
}