//============================================================\\
// Soul`s Menu Base                                            \\
// Free To use and mainly for learning                          \\
// This is not for Just CA will a menu for any game             //
// This is ONLY the d3d menu no hacks add them yourself ^^     //
//============================================================//
#include "stdafx.h"
#include "SoulMenu.h"
#include "Hook.h"


//================Defines Go Here================\\
//#define definename          DefineCode
//===================End Defines==================\\

//Menu
CHAR MenuTitle[25] = { "Your Menu Name" }; // Title name hack
CHAR Timestruct[25] = { "hh':'mm':'ss tt" };
CHAR TimeString[25];
INT MenuSelection;
BOOL Menu = TRUE;
BOOL bFont;

//Hack Variables
INT f1, f2;



INT quantdehacks = 2;



HRESULT WINAPI hkReset(LPDIRECT3DDEVICE9 pDevice, D3DPRESENT_PARAMETERS *a)
{
	Directx_Font->OnLostDevice();

	HRESULT hTorna = oReset(pDevice, a);

	if(SUCCEEDED(hTorna))
		Directx_Font->OnResetDevice();

	return hTorna;
}

HRESULT WINAPI hkPresent(LPDIRECT3DDEVICE9 pDevice, CONST RECT *a, CONST RECT *b, HWND c, CONST RGNDATA *d)
{
	if(Directx_Font) {
		Directx_Font->Release();
		Directx_Font = NULL;
		bFont = FALSE;
	}

	if(!bFont) {
		D3DXCreateFont(pDevice, 14, 0, FW_NORMAL, 1, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, ANTIALIASED_QUALITY, DEFAULT_PITCH | FF_DONTCARE, "Arial", &Directx_Font);
		bFont = TRUE;
	}

	if(GetAsyncKeyState(VK_INSERT)&1) Menu = !Menu;	

	if(Menu && Directx_Font) {
		pDevice->SetRenderState(D3DRS_ZENABLE, D3DZB_FALSE);
		GetTimeFormat(NULL, NULL, NULL, NULL, Timestruct, 15);
		/////////////////////////////////////////////////////////////////////////////////////////
		////////////////////WHITE BACKGROUND/////////////////////////////////////////////////////
		DrawRect(pDevice, 0, 0, 1000 , 1000,White); // DELETE THIS TO REMOVE THE WHITE BACKGROUND
		/////////////////////////////////////////////////////////////////////////////////////////
		/////////////////////////////////////////////////////////////////////////////////////////
		DrawRect(pDevice, 20, 25, 35 , 162,SoulBlue);
	    DrawRect(pDevice, 22, 27, 31 , 158,Black);
		DrawText(pDevice, 30, 35, White, MenuTitle);
		sprintf_s(TimeString, "%s", Timestruct);
		DrawText(pDevice, 120, 35, White, TimeString);		
		DrawRect(pDevice, 20, 70, 55 , 162,SoulBlue);
			DrawRect(pDevice, 22, 72, 51 , 158,Black);
			
		DrawRect(pDevice, -5, 450, 30 , 1000, SoulBlue);
		DrawRect(pDevice, -5, 452, 26 , 1000, Black);
		
		DrawText(pDevice, 30, 80, White, "CrossHair");
		if(f1==0) DrawText(pDevice, 150, 80, Red, "[Off]");
		if(f1==1) DrawText(pDevice, 150, 80, Green, "[On]");
	

	DrawText(pDevice, 30, 100, White, "Credits");
		if(f2==0) DrawText(pDevice, 150, 100, Red, "[Off]");
		if(f2==1) DrawText(pDevice, 150, 100, Green, "[On]");	


		
		if(GetAsyncKeyState(VK_UP)&1) {
			MenuSelection--;
			if(MenuSelection < 0) MenuSelection = quantdehacks - 1;
		}

		if(GetAsyncKeyState(VK_DOWN)&1) {
			MenuSelection++;
			if(MenuSelection > quantdehacks - 1) MenuSelection = 0;
		}

		if(GetAsyncKeyState(VK_RIGHT)&1) {
			switch(MenuSelection) {
				case 0:
					f1++; if(f1 > 1) f1 = 1; break;
				case 1:
					f2++; if(f2 > 1) f2 = 1; break;
				
				
				default:
					break;
			}
		}

		if(GetAsyncKeyState(VK_LEFT)&1) {
			switch(MenuSelection) {
				case 0:
					f1--; if(f1 < 0) f1 = 0; break;
				case 1:
					f2--; if(f2 < 0) f2 = 0; break;
				
				default:
					break;
			}
		}

		for(INT x = 0; x < quantdehacks + 1; x++) {
			if(MenuSelection == x) 
				CurrentOption(pDevice, 25, 80 + 20 * x, 15, 150, Cyan);
		}
		
		//VVVV Hack Descriptions here VVVV

		if(MenuSelection == 0){
				DrawText(pDevice, 4, 455, White, "Displays a CrossHair in the center of the screen");
		}
			if(MenuSelection == 1){
				DrawText(pDevice, 4, 455, White, "Shows the Credits for this hack");
		}
	


	}
	//ADD HACKS
    if(f1==1) CrossHair(pDevice, Red);

	if(f2){
		DrawRect(pDevice, 190, 25, 84 , 162,SoulBlue);
		DrawRect(pDevice, 192, 27, 80 , 158,Black);
			//No there not aligned i got lazy XD
	DrawText(pDevice, 225, 30, SoulBlue, "~!Cool Person List!~");
			DrawText(pDevice, 247, 42, White, "Soul`");
			DrawText(pDevice, 254, 52, White, "Netro");
			DrawText(pDevice, 241, 62, White, "Boomdocks");
			DrawText(pDevice, 246, 72, White, "JustiMaN");
			DrawText(pDevice, 251, 82, White, "Aeir");
			DrawText(pDevice, 245, 92, White, "Deadcode");

			DrawRect(pDevice, 190, 115, 45 , 162,SoulBlue);
			DrawRect(pDevice, 192, 117, 41 , 158,Black);
			
	DrawText(pDevice, 245, 120, SoulBlue, "~!Credits!~");
			DrawText(pDevice, 247, 132, White, "Soul`");
			DrawText(pDevice, 241, 142, White, "Aeir");}

	return oPresent(pDevice, a, b, c, d);
}

DWORD WINAPI Hook(LPVOID lpArgs)
{
	DWORD dwD3D9 = 0;

	while(!dwD3D9) {
		Sleep(100);
		dwD3D9 = (DWORD)GetModuleHandle("d3d9.dll");
	}

	DWORD dwVTable[1] = {0};
	CreateDevice(dwVTable);

	oReset   = (tReset)  Salta((PBYTE) dwVTable[0], (PBYTE) &hkReset, 5);
	oPresent = (tPresent)Salta((PBYTE) dwVTable[1], (PBYTE) &hkPresent, 5);
	
	return FALSE;
}
