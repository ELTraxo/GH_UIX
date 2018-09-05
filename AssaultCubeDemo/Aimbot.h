#pragma once
#include "game.h"

class Aimbot
{
	PlayerEnt* pLocalPlayer;
	std::vector<PlayerEnt>* pEntities;
	PlayerEnt* pTarget;
	bool bUseClosest;
public:
	Aimbot() {}
	Aimbot( PlayerEnt* pLocalPlayer, std::vector<PlayerEnt>* pEntities );
	~Aimbot();
	void Run();

private:
	void SelectTarget();
	void GetClosest();
	vec2f CalcAngle( vec3f src, vec3f dst );

};

