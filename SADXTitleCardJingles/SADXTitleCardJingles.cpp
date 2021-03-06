// SADXTitleCardJingles.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "..\sadx-mod-loader\SADXModLoader\include\SADXModLoader.h"

short cardDispTime;
int LoadTitleCardTexture_Wrapper(int minDispTime)
{
	cardDispTime = 0;
	int song;
	switch (CurrentLevel)
	{
	case LevelIDs_StationSquare:
	case 27:
	case 28:
		minDispTime = 348;
		song = MusicIDs_titl_ss;
		break;
	case LevelIDs_EggCarrierOutside:
	case 30:
	case 31:
	case LevelIDs_EggCarrierInside:
		minDispTime = 603;
		song = MusicIDs_titl_egg;
		break;
	case LevelIDs_MysticRuins:
		minDispTime = 484;
		song = MusicIDs_titl_mr1;
		break;
	case LevelIDs_Past:
		minDispTime = 543;
		song = MusicIDs_titl_mr2;
		break;
	default:
		return LoadTitleCardTexture(minDispTime);
	}
	int result = LoadTitleCardTexture(minDispTime);
	ObjectMaster *sm = InitializeSoundManager();
	PlayMusic((MusicIDs)song);
	sm->MainSub(sm);
	sm->MainSub(sm);
	return result;
}

int loc_47E187 = 0x47E187;
__declspec(naked) void DisplayTitleCard_r()
{
	__asm
	{
		mov cx, [cardDispTime]
		inc cx
		mov eax, [TitleCardDispTime]
		cmp cx, [eax]
		mov [cardDispTime], cx
		jmp loc_47E187
	}
}

VoidFunc(sub_415210, 0x415210);
void Thing()
{
	SoundManager_Delete2();
	sub_415210();
}

extern "C"
{
	__declspec(dllexport) void Init(const char *path, const HelperFunctions &helperFunctions)
	{
		WriteJump(j_LoadTitleCardTexture, LoadTitleCardTexture_Wrapper);
		WriteJump(DisplayTitleCard, DisplayTitleCard_r);
		WriteCall((void*)0x41749C, Thing);
		WriteCall((void*)0x415B9F, Thing);
	}

	__declspec(dllexport) ModInfo SADXModInfo = { ModLoaderVer };
}