#pragma once
#include "UIX.h"
#include "options.h"
#include "game.h"


#define PROCNAME _T("ac_client.exe")

extern MemEx * pMem;
class PlayerEnt;
class Aimbot;
class ESP;
namespace hax
{
	extern uintptr_t LocalPlayerBase;
	extern PlayerEnt LocalPlayer;
	extern std::vector<PlayerEnt> vEntities;
	extern NativeWindowPtr pOverlay;

	extern Aimbot aimbot;
	extern ESP esp;
	void Initialize( NativeWindowPtr pOverlay );
	void InfAmmo();
	bool IsValidPlayer( PlayerEnt* pPlayer );
	void UpdateEntities();
	void Run();
};

#include "Aimbot.h"
#include "ESP.h"