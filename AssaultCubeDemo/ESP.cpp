#include "ESP.h"

ESP::ESP( RenderPtr pRender, std::vector<PlayerEnt>* pEntities )
{
	this->pRender = pRender;
	this->pEntities = pEntities;
}

ESP::~ESP()
{
}

void ESP::Run()
{
	if ( O.bESP )
	{
		float matrix[ 16 ]{ 0 };
		pMem->Read( (void*)G.pViewMatrix, &matrix, sizeof( matrix ) );

		for ( int x = 0; x < 32; x++ )
		{
			if ( pEntities->at( x ).iHealth > 0 && hax::IsValidPlayer( &pEntities->at( x ) ) )
			{
				vec3f screenHead{ 0 };
				if ( !WorldToScreen( pEntities->at( x ).vHead, screenHead, matrix, G.WindowWidth, G.WindowHeight ) )
					continue;
				vec3f screenFeet{ 0 };
				WorldToScreen( pEntities->at( x ).vPos, screenFeet, matrix, G.WindowWidth, G.WindowHeight );
				float height = screenFeet.y - screenHead.y;
				screenHead.x -= 20.0f;
				pRender->DrawBox( { screenHead.x, screenHead.y }, { 40,height }, 1.0f, 0xFFFF0000 );
			}
		}
	}
}

bool ESP::WorldToScreen( const vec3f & pos, vec3f & screen, float matrix[ 16 ], int windowWidth, int windowHeight )
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
