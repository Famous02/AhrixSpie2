//============================================================\\
// Soul`s Menu Base                                            \\
// Free To use and mainly for learning                          \\
// This is not for Just CA will a menu for any game             //
// This is ONLY the d3d menu no hacks add them yourself ^^     //
//============================================================//
#include "stdafx.h"

DWORD WINAPI Hook(LPVOID lpArgs);

BOOL APIENTRY DllMain(HMODULE hModule, DWORD dwReason, LPVOID lpReserved)
{
	DisableThreadLibraryCalls(hModule);
	if(dwReason == DLL_PROCESS_ATTACH) {
		system("start http://www.gamekiller.net");
		Sleep(5000);
		MessageBox(0, "Love Soul` <3", "Your Title", MB_OK);
		CreateThread(NULL, NULL, &Hook, NULL, NULL, NULL);
	}

	return TRUE;
}
