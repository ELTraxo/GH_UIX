#pragma once
#include "includes.h"
// "ac_client.exe"+0010F4F8

struct Game
{
	uintptr_t pClientBase = 0;
	uintptr_t pPlayerOffset = 0x0010F4F4;
	uintptr_t pLocalPlayer = 0;
	uintptr_t pEntities = 0;
	uintptr_t pViewMatrixOffset = 0x00101AE8;
	uintptr_t pViewMatrix = 0;

	int WindowWidth = 0;
	int WindowHeight = 0;

	// player shit
	struct EntityOffsets
	{
		uintptr_t v3Head = 0x4;
		uintptr_t v3Pos = 0x34;
		uintptr_t v2View = 0x40;
		uintptr_t iHealth = 0xF8;
		uintptr_t iArmor = 0xFC;
		uintptr_t szName = 0x224;
	}EO;
};

extern Game G;

class WeaponEnt
{
public:
	void* vTable; //0x0000 
	char pad_0x0004[ 0x8 ]; //0x0004
	char * pszWeaponName; //0x000C 
	int* pReserveAmmo; //0x0010 
	int* pAmmo; //0x0014 
	int* pDelay; //0x0018 
	__int32 iDynRecoil; //0x001C 
	__int32 iDynReload; //0x0020 
	char pad_0x0024[ 0xC ]; //0x0024
}; //Size=0x0030

class PlayerEnt
{
public:
	uintptr_t vTable; //0x0000 
	vec3f vHead; //0x0004 
	char pad_0x0010[ 0x24 ]; //0x0010
	vec3f vPos; //0x0034 
	vec2f vView; //0x0040 
	char pad_0x0048[ 0xC ]; //0x0048
	__int32 iGravForce; //0x0054 
	char pad_0x0058[ 0x20 ]; //0x0058
	float N00000031; //0x0078 
	char pad_0x007C[ 0x4 ]; //0x007C
	__int8 i8WS_Speed; //0x0080 
	__int8 i8AD_Speed; //0x0081 
	char pad_0x0082[ 0x76 ]; //0x0082
	__int32 iHealth; //0x00F8 
	__int32 iArmor; //0x00FC 
	char pad_0x0100[ 0x14 ]; //0x0100
	__int32 iPistolReserve; //0x0114 
	char pad_0x0118[ 0x48 ]; //0x0118
	__int32 iKnifeDelay; //0x0160 
	__int32 iPistolDelay; //0x0164 
	__int32 iCarbineDelay; //0x0168 
	char pad_0x016C[ 0xB8 ]; //0x016C
	char szName[ 16 ]; //0x0224 
	char pad_0x0234[ 0x134 ]; //0x0234
	WeaponEnt* pGrenades; //0x0368 
	char pad_0x036C[ 0x4 ]; //0x036C
	WeaponEnt* pPrevWeap; //0x0370 
	WeaponEnt* pCurrWeap; //0x0374 
	WeaponEnt* pCurrWeapon; //0x0378 
	char pad_0x037C[ 0x88 ]; //0x037C
}; //Size=0x0404