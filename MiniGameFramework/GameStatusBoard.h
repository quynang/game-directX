#pragma once
#include <string>
#include <vector>
#include "Simon.h"

#define TEX_STATUS_BAR_WIDTH	260
class CGameStatusBoard
{
	ID3DXFont* font;
	RECT rectRowOne;
	RECT rectRowTwo;
	RECT rectRowThree;
	LPDIRECT3DDEVICE9 d3ddv;
	wstring inforRowOne;
	wstring inforRowTwo;
	wstring inforRowThree;
	LPSPRITE sprite;
	LPD3DXSPRITE spriteHandler;
	int score;
	int time;
	int item;
	int energy;
	int life;
	int stage;
	float pos_x;
public:
	CGameStatusBoard();
	~CGameStatusBoard();
	void Update(int timeRemain);
	void Render();
};

