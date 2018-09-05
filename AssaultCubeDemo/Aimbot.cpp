#include "Aimbot.h"

Aimbot::Aimbot( PlayerEnt * pLocalPlayer, std::vector<PlayerEnt>* pEntities )
{
	this->pLocalPlayer = pLocalPlayer;
	this->pEntities = pEntities;
	this->bUseClosest = true;
}

Aimbot::~Aimbot()
{
}

void Aimbot::Run()
{
	if ( O.bAimbot )
	{
		SelectTarget();
		if ( GetAsyncKeyState( VK_RBUTTON ) && pTarget )
		{
			auto angles = CalcAngle( pLocalPlayer->vPos, pTarget->vPos );
			pMem->Write<vec2f>( (void*)( hax::LocalPlayerBase + G.EO.v2View ), &angles, sizeof( angles ) );
		}
	}
}

void Aimbot::SelectTarget()
{
	if ( bUseClosest )
		GetClosest();
	/*else
		GetTargetFOV();*/
}

void Aimbot::GetClosest()
{
	PlayerEnt* pClosest = nullptr;
	float shortestDist = 0.0f;
	// find closest target
	for ( int x = 0; x < 32; x++ )
	{
		if ( pEntities->at( x ).iHealth > 0 && hax::IsValidPlayer( &pEntities->at( x ) )/*.vTable == (void*)EntityVTable*/ )
		{
			if ( !pClosest )
			{
				pClosest = &pEntities->at( x );
				//shortestDist = vEntities[ x ].vPos.DistanceTo( pLocalPlayer.vPos );
				shortestDist = pLocalPlayer->vPos.DistanceTo( pEntities->at( x ).vPos );
			}
			else
			{
				auto dist = pEntities->at( x ).vPos.DistanceTo( pLocalPlayer->vPos );
				if ( dist < shortestDist )
				{
					shortestDist = dist;
					pClosest = &pEntities->at( x );
				}
			}
		}
	}
	pTarget = pClosest;
}

vec2f Aimbot::CalcAngle( vec3f src, vec3f dst )
{
	vec2f angles;
	angles.x = ( -(float)atan2( dst.x - src.x, dst.y - src.y ) ) / D3DX_PI * 180.0f + 180.0f;
	angles.y = ( asinf( ( dst.z - src.z ) / src.DistanceTo( dst ) ) ) * 180.0f / D3DX_PI;
	return angles;
}
