#include "hax.h"
#include <math.h>

uintptr_t hax::LocalPlayerPtr;
PlayerEnt hax::LocalPlayer;
std::vector<PlayerEnt> hax::vEntities( 32 );

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
	return (pPlayer->vTable == LocalPlayer.vTable + 0x28 );
}

void hax::UpdateEntities()
{
	pMem->Read( (void*)G.pLocalPlayer, &LocalPlayerPtr, sizeof( uintptr_t ) );
	pMem->Read( (void*)LocalPlayerPtr, &LocalPlayer, sizeof( PlayerEnt ) );

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
	}
}

void hax::Aimbot()
{
	//uintptr_t pPlayer = 0;
	//PlayerEnt pLocalPlayer{ 0 };
	//pMem->Read( (void*)G.pLocalPlayer, &pPlayer, sizeof( uintptr_t ) );
	//pMem->Read( (void*)pPlayer, &pLocalPlayer, sizeof( PlayerEnt ) );
	//uintptr_t EntityVTable = (uintptr_t)pLocalPlayer.vTable + 0x28;
	float shortestDist = 0;
	PlayerEnt* pClosest = nullptr;
	if ( O.bAimbot )
	{
		// find closest target
		for ( int x = 0; x < 32; x++ )
		{
			if ( vEntities[ x ].iHealth > 0 && IsValidPlayer(&vEntities[x])/*.vTable == (void*)EntityVTable*/ )
			{
				if ( !pClosest )
				{
					pClosest = &vEntities[ x ];
					//shortestDist = vEntities[ x ].vPos.DistanceTo( pLocalPlayer.vPos );
					shortestDist = LocalPlayer.vPos.DistanceTo( vEntities[ x ].vPos );
				}
				else
				{
					auto dist = vEntities[ x ].vPos.DistanceTo( LocalPlayer.vPos );
					if ( dist < shortestDist )
					{
						shortestDist = dist;
						pClosest = &vEntities[ x ];
					}
				}
			}
		}
		
		if ( GetAsyncKeyState( VK_RBUTTON ) && pClosest)
		{
			auto angles = CalcAngle( LocalPlayer.vPos, pClosest->vPos );
			pMem->Write<vec2f>( (void*)( LocalPlayerPtr + G.EO.v2View ), &angles, sizeof( angles ) );
		}
	}
}

vec2f hax::CalcAngle( vec3f src, vec3f dst )
{
	vec2f angles;
	angles.x = ( -(float)atan2( dst.x - src.x, dst.y - src.y ) ) / D3DX_PI * 180.0f + 180.0f;
	angles.y = ( atan2( dst.z - src.z, src.DistanceTo( dst ) ) ) * 180.0f / D3DX_PI;
	return angles;
}

bool WorldToScreen( const vec3f & pos, vec3f & screen, float matrix[ 16 ], int windowWidth, int windowHeight )
{
	//Matrix-vector Product, multiplying world(eye) coordinates by projection matrix = clipCoords
	vec4f clipCoords;
	clipCoords.x = pos.x*matrix[ 0 ] + pos.y*matrix[ 4 ] + pos.z*matrix[ 8 ] + matrix[ 12 ];
	clipCoords.y = pos.x*matrix[ 1 ] + pos.y*matrix[ 5 ] + pos.z*matrix[ 9 ] + matrix[ 13 ];
	clipCoords.z = pos.x*matrix[ 2 ] + pos.y*matrix[ 6 ] + pos.z*matrix[ 10 ] + matrix[ 14 ];
	clipCoords.w = pos.x*matrix[ 3 ] + pos.y*matrix[ 7 ] + pos.z*matrix[ 11 ] + matrix[ 15 ];

	if ( clipCoords.w < 0.1f )
		return false;

	//perspective division, dividing by clip.W = Normalized Device Coordinates
	vec3f NDC;
	NDC.x = clipCoords.x / clipCoords.w;
	NDC.y = clipCoords.y / clipCoords.w;
	NDC.z = clipCoords.z / clipCoords.w;

	//Transform to window coordinates
	screen.x = ( windowWidth / 2 * NDC.x ) + ( NDC.x + windowWidth / 2 );
	screen.y = -( windowHeight / 2 * NDC.y ) + ( NDC.y + windowHeight / 2 );
	return true;
}

void hax::ESP(RenderPtr pRender)
{
	if ( O.bESP )
	{
		uintptr_t pPlayer = 0;
		PlayerEnt pLocalPlayer{ 0 };
		pMem->Read( (void*)G.pLocalPlayer, &pPlayer, sizeof( uintptr_t ) );
		pMem->Read( (void*)pPlayer, &pLocalPlayer, sizeof( PlayerEnt ) );
		uintptr_t EntityVTable = (uintptr_t)pLocalPlayer.vTable + 0x28;
		
		float matrix[ 16 ]{ 0 };
		pMem->Read( (void*)G.pViewMatrix, &matrix, sizeof( matrix ) );

		for ( int x = 0; x < 32; x++ )
		{
			if ( vEntities[ x ].iHealth > 0 && vEntities[ x ].vTable == EntityVTable )
			{
				vec3f screenHead{ 0 };
				WorldToScreen( vEntities[ x ].vHead, screenHead, matrix, G.WindowWidth, G.WindowHeight );
				vec3f screenFeet{ 0 };
				WorldToScreen( vEntities[ x ].vPos, screenFeet, matrix, G.WindowWidth, G.WindowHeight );
				float height = screenFeet.y - screenHead.y;
				screenHead.x -= 20.0f;
				pRender->DrawBox( { screenHead.x, screenHead.y }, { 40,height }, 1.0f, 0xFFFF0000 );
			}
		}
	}
}
