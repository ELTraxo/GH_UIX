#pragma once
#include "game.h"
class ESP
{
	RenderPtr pRender;
	std::vector<PlayerEnt>* pEntities;
public:
	ESP(){}
	ESP(RenderPtr pRender, std::vector<PlayerEnt>* pEntities);
	~ESP();
	void Run();
private:
	bool WorldToScreen( const vec3f & pos, vec3f & screen, float matrix[ 16 ], int windowWidth, int windowHeight );
};

