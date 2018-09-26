#include "hax.h"
#include <math.h>

Options O;
MemEx* pMem = nullptr;

uintptr_t hax::LocalPlayerBase;
PlayerEnt hax::LocalPlayer;
std::vector<PlayerEnt> hax::vEntities( 32 );
NativeWindowPtr hax::pOverlay = nullptr;
Aimbot hax::aimbot;
ESP hax::esp;

void hax::Initialize( NativeWindowPtr pOverlay )
{
	pMem = new MemEx( PROCNAME );
	pMem->Open();

	G.pClientBase = GetModuleBase( pMem->GetPID(), PROCNAME );
	G.pLocalPlayer = G.pClientBase + G.pPlayerOffset;
	G.pViewMatrix = G.pClientBase + G.pViewMatrixOffset;
	G.pEntities = G.pLocalPlayer + 4;

	hax::pOverlay = pOverlay;
	aimbot = Aimbot( &LocalPlayer, &vEntities );
	esp = ESP( pOverlay->GetRenderer(), &vEntities );
}

void hax::InfAmmo()
{
	if ( O.bInfAmmo )
	{
		char nops[] = { 0x90, 0x90 };
		pMem->Write( (void*)0x004637E9, nops, 2 );
	}
	else
	{
		char bytes[] = { 0xFF, 0x0E };
		pMem->Write( (void*)0x004637E9, bytes, 2 );
	}
}

bool hax::IsValidPlayer( PlayerEnt * pPlayer )
{
	return ( pPlayer->vTable == LocalPlayer.vTable + 0x28 ) || ( pPlayer->vTable == LocalPlayer.vTable );
}

void hax::UpdateEntities()
{
	pMem->Read( (void*)G.pLocalPlayer, &LocalPlayerBase, sizeof( uintptr_t ) );
	pMem->Read( (void*)LocalPlayerBase, &LocalPlayer, sizeof( PlayerEnt ) );

	uintptr_t pEntityList = 0;
	pMem->Read( (void*)G.pEntities, &pEntityList, sizeof( uintptr_t ) );
	for ( int x = 0; x < 32; x++ )
	{
		uintptr_t pEnt = 0;
		pMem->Read( (void*)( pEntityList + ( x * 4 ) ), &pEnt, sizeof( uintptr_t ) );
		if ( pEnt )
		{
			pMem->Read( (void*)( pEnt ), &vEntities[ x ], sizeof( PlayerEnt ) );
		}
		else
			vEntities[ x ].iHealth = 0;
	}
}

void hax::Run()
{
	hax::UpdateEntities();
	aimbot.Run();
	
	if( pOverlay->GetOverlayTarget() == GetForegroundWindow() )
		esp.Run();
}
