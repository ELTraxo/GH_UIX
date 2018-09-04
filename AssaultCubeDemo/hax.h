#pragma once
#include "UIX.h"
#include "options.h"
#include "game.h"

extern MemEx * pMem;
class PlayerEnt;
namespace hax
{
	extern uintptr_t LocalPlayerPtr;
	extern PlayerEnt LocalPlayer;
	extern std::vector<PlayerEnt> vEntities;
	void InfAmmo();
	bool IsValidPlayer( PlayerEnt* pPlayer );
	void UpdateEntities();
	void Aimbot();
	vec2f CalcAngle( vec3f src, vec3f dst );
	void ESP(RenderPtr pRender);
};