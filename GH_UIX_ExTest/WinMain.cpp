#include "UIX.h"

int bc( void* p )
{
	ErrorMsgBox( (TCHAR*)p );
	return 666;
}

int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow )
{
	auto uix = UIX::Create( hInstance, false );
	auto pW0 = uix->CreateNativeWindow( { 5, 50 }, { 800,600 } );

	if ( uix->InitializeRenderer() )
	{

		auto pCanvas = pW0->GetCanvas();
		auto pRender = pW0->GetRenderer();



		auto pWindow = MakeWindowPtr( pRender );
		pCanvas->AddChildControl( pWindow );
		pWindow->SetPos( 25 );
		pWindow->SetSize( { 600,400 } );
		//pWindow->SetColor( 0xFFFF0000 );

		pWindow->AddLabel( { 5,185 }, L"Label", 0xFFFFFFFF );
		auto pB = pWindow->AddButton( { 5,200 }, { 100, 20 }, L"Dicks!", 0xFF000000, 0xFFFFFFFF );
		pB->SetCallbackData( L"Dicks" );
		pB->SetButtonCallback( bc );
		pWindow->AddListbox( { 5, 225 }, { 200,100 }, 0xFF202020, 0xFFFFFFFF );
		auto p = pWindow->AddDropdown( { 215, 225 }, { 200, 100 }, 0xFF000000, 0xFFFFFFFF );
		p->AddNewItem( L"Item 1" );
		p->AddNewItem( L"Item 2" );
		pWindow->AddTextbox( { 5, 150 }, { 100, 20 }, 0xFF000000, 0xFFFFFFFF );
		pWindow->AddCheckbox( { 5, 175 }, L"Checkbox" );
		pWindow->AddRadio( { 185, 185 }, L"Radio button" );
		auto pG = pWindow->AddGroupbox( { 300,70 }, { 200,100 }, L"Groupbox" );
		pG->AddLabel( { 5, 15 }, L"Text in groupbox", 0xFFFF00FF );
		auto pT = pWindow->AddTabControl( { 5, 20 }, { 200, 100 } );
		auto pC = pT->AddTab( L"Tab1" );
		pC->AddLabel( 10, L"Label in tab control", 0xFFFF0000 );
		pT->AddTab( L"Tab2" );

		auto pSlide = pWindow->AddSliderControl( { 250, 20 }, { 150,20 }, { 0.0f, 1.0f }, 0.5f, 0xFF404040, 0xFFFFFFFF );
		pSlide->SetThumbColor( 0xFF808080 );
		pSlide->SetThumbBorderColor( 0 );

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