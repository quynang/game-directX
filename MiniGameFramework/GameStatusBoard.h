#pragma once
#include <string>
#include <vector>
#include "Simon.h"

#define TEX_STATUS_BAR_WIDTH	260
class CGameStatusBoard
{
	static CGameStatusBoard* __instance;
	ID3DXFont* font;
	RECT rectRowOne;
	RECT rectRowTwo;
	RECT rectRowThree;
	LPDIRECT3DDEVICE9 d3ddv;
	wstring inforRowOne;
	wstring inforRowTwo;
	wstring inforRowThree;
	LPSPRITE statusBoardSprite;
	LPSPRITE hpSprite1;
	LPSPRITE hpSprite2;
	LPSPRITE hpSprite3;
	LPD3DXSPRITE spriteHandler;
	int score = 0;
	int item;
	int heart = 5;
	int stage = 1;
	int hpRemain = 16;
	CGameStatusBoard();
	~CGameStatusBoard();
public:
	static CGameStatusBoard* GetInstance();
	void Update(int timeRemain, int hp, int stage);
	void IncreaseScore(int value) { score += value; }
	void IncreaseNumHeart(int value) { heart += value; }
	void Render();
};

